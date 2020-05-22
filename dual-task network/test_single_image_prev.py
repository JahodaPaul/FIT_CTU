# coding: utf-8

from __future__ import division, print_function

import tensorflow as tf
import numpy as np
import argparse
import cv2
import math
import os

from utils.misc_utils import parse_anchors, read_class_names
from utils.nms_utils import gpu_nms
from utils.plot_utils import get_color_table, plot_one_box
from utils.data_aug import letterbox_resize

from model import yolov3

parser = argparse.ArgumentParser(description="YOLO-V3 test single image test procedure.")
parser.add_argument("input_image", type=str,
                    help="The path of the input image.")
parser.add_argument("--anchor_path", type=str, default="./data/yolo_anchors.txt",
                    help="The path of the anchor txt file.")
parser.add_argument("--new_size", nargs='*', type=int, default=[320, 320], #prev 416
                    help="Resize the input image with `new_size`, size format: [width, height]")
parser.add_argument("--letterbox_resize", type=lambda x: (str(x).lower() == 'true'), default=True,
                    help="Whether to use the letterbox resize.")
parser.add_argument("--class_name_path", type=str, default="./data/coco.names",
                    help="The path of the class names.")
parser.add_argument("--restore_path", type=str, default="./data/darknet_weights/yolov3.ckpt",
                    help="The path of the weights to restore.")

args = parser.parse_args()

args.anchors = parse_anchors(args.anchor_path)
args.classes = read_class_names(args.class_name_path)
args.num_class = len(args.classes)

def getDistanceAndAngle(box,width_ori,height_ori):
    VIEW_WIDTH = width_ori
    VIEW_HEIGHT = height_ori
    VIEW_FOV = 85
    calibration = np.identity(3)
    calibration[0, 2] = VIEW_WIDTH / 2.0
    calibration[1, 2] = VIEW_HEIGHT / 2.0
    calibration[0, 0] = calibration[1, 1] = VIEW_WIDTH / (2.0 * np.tan(VIEW_FOV * np.pi / 360.0))

    distortion = np.zeros((4, 1))

    objectPoints = np.random.random((5, 3, 1))
    imagePoints = np.random.random((5, 2, 1))
    x0, y0, x1, y1 = box
    imagePoints[0][0][0] = (x0 + x1) / 2;imagePoints[0][1][0] = (y1 + y0) / 2
    imagePoints[0 + 1][0][0] = x1;imagePoints[0 + 1][1][0] = y1
    imagePoints[1 + 1][0][0] = x0;imagePoints[1 + 1][1][0] = y1
    imagePoints[2 + 1][0][0] = x1;imagePoints[2 + 1][1][0] = y0
    imagePoints[3 + 1][0][0] = x0;imagePoints[3 + 1][1][0] = y0

    objectPoints[0][1][0] = 0;objectPoints[0][2][0] = 0;objectPoints[0][0][0] = 0
    objectPoints[0 + 1][1][0] = 0.13;objectPoints[0 + 1][2][0] = -0.09;objectPoints[0 + 1][0][0] = 0
    objectPoints[1 + 1][1][0] = -0.13;objectPoints[1 + 1][2][0] = -0.09;objectPoints[1 + 1][0][0] = 0
    objectPoints[2 + 1][1][0] = 0.13;objectPoints[2 + 1][2][0] = 0.09;objectPoints[2 + 1][0][0] = 0
    objectPoints[3 + 1][1][0] = -0.13;objectPoints[3 + 1][2][0] = 0.09;objectPoints[3 + 1][0][0] = 0

    objectPoints = np.array(objectPoints, dtype=float)
    objectPoints = np.reshape(objectPoints, (5, 3, 1))
    imagePoints = np.array(imagePoints, dtype=float)
    imagePoints = np.reshape(imagePoints, (5, 2, 1))

    ret, rvecs, tvecs = cv2.solvePnP(objectPoints, imagePoints, calibration, distortion)
    print(tvecs)
    angle = math.degrees(math.atan2(tvecs[0][0], tvecs[2][0]))
    distance = math.sqrt(tvecs[0][0] ** 2 + tvecs[1][0] ** 2 + tvecs[2][0] ** 2)
    print(angle)

    prvniStrana = 0.1
    # korekce
    triangleAngle = 0
    if angle >= 0:
        triangleAngle = 90.0 - angle
    elif angle < 0:
        triangleAngle = 90.0 + (-1 * angle)

    # Cosinova veta na spocteni 3. strany trojuhelnika
    predicted_distance = math.sqrt(
        prvniStrana ** 2 + distance ** 2 - 2 * prvniStrana * distance * math.cos(math.radians(triangleAngle)))

    tmpAngle = math.degrees(math.acos(
        (prvniStrana ** 2 + predicted_distance ** 2 - distance ** 2) / (2 * prvniStrana * predicted_distance)))

    if angle >= 0:
        angle = 90.0 - (180 - tmpAngle)
    else:
        angle = -1 * (90.0 - (tmpAngle))

    print('distance:', distance)
    print('angle:', angle)
    return distance,angle

if not os.path.exists('results'):
    os.mkdir('results')

def drawMap(img, indexes):
    img, resize_ratio, dw, dh = letterbox_resize(img, args.new_size[0], args.new_size[1])
    size_w = 320/13
    size_h = (320-2*dh)/13

    for i in range(len(indexes)):
        indexes[i] = indexes[i]//3
        x0 = int((indexes[i] * size_w) % 320)
        x1 = int(x0 + size_w)
        y0 = int(320-dh-size_h-indexes[i]//13 * size_h)
        y1 = int(y0 + size_h)
        print(indexes[i], x0, x1, y0, y1)
        plot_one_box(img, [x0, y0, x1, y1],
                     label=args.classes[1] + ', {:.2f}%'.format(1 * 100),
                     color=color_table[1])

    cv2.imwrite(os.path.join('resultsSegm', 'test.png'), img)


with tf.Session() as sess:
    input_data = tf.placeholder(tf.float32, [1, args.new_size[1], args.new_size[0], 3], name='input_data')
    yolo_model = yolov3(args.num_class, args.anchors)

    with tf.variable_scope('yolov3'):
         pred_feature_maps = yolo_model.forward(input_data, False)
    pred_boxes, pred_confs, pred_probs = yolo_model.predict(pred_feature_maps)

    pred_scores = pred_confs * pred_probs

    boxes, scores, labels = gpu_nms(pred_boxes, pred_scores, args.num_class, max_boxes=200, score_thresh=0.3,
                                   nms_thresh=0.45)

    saver = tf.train.Saver()
    saver.restore(sess, args.restore_path)

    files = [args.input_image]
    if os.path.isdir(args.input_image):
        tmpFiles = os.listdir(args.input_image)
        files = []
        for f in tmpFiles:
            files.append(os.path.join(args.input_image,f))
    for input_image in files:
        color_table = get_color_table(args.num_class)

        img_ori = cv2.imread(input_image)
        height_ori, width_ori = img_ori.shape[:2]
        if args.letterbox_resize:
            img, resize_ratio, dw, dh = letterbox_resize(img_ori, args.new_size[0], args.new_size[1])
        else:
            height_ori, width_ori = img_ori.shape[:2]
            img = cv2.resize(img_ori, tuple(args.new_size))
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        img = np.asarray(img, np.float32)
        img = img[np.newaxis, :] / 255.




        # print(pred_confs, pred_probs)

        # saver = tf.train.Saver()
        # saver.restore(sess, args.restore_path)
        boxes_, scores_, labels_, pred_probs_ = sess.run([boxes, scores, labels,pred_probs], feed_dict={input_data: img})

        print('Feature map:')
        tmp = pred_probs_[0][:13*13]
        resList = []
        for i in range(len(tmp)):
            if tmp[i][1] > 0.9:
                resList.append(i)
        drawMap(img_ori,resList)
        # boxes_, scores_, labels_ = sess.run([boxes, scores, labels], feed_dict={input_data: img})

        # rescale the coordinates to the original image
        if args.letterbox_resize:
            boxes_[:, [0, 2]] = (boxes_[:, [0, 2]] - dw) / resize_ratio
            boxes_[:, [1, 3]] = (boxes_[:, [1, 3]] - dh) / resize_ratio
        else:
            boxes_[:, [0, 2]] *= (width_ori/float(args.new_size[0]))
            boxes_[:, [1, 3]] *= (height_ori/float(args.new_size[1]))

        print("box coords:")
        print(boxes_)
        print('*' * 30)
        print("scores:")
        print(scores_)
        print('*' * 30)
        print("labels:")
        print(labels_)
        
        maxVal = 0
        maxIndex = -1
        if len(boxes_) != 0:
            # find car
            for i in range(len(labels_)):
                if labels_[i] == 0:
                    if scores_[i] > maxVal:
                        maxVal = scores_[i]
                        maxIndex = i

            if maxIndex != -1:
                dist, angle = getDistanceAndAngle(boxes_[maxIndex],width_ori,height_ori)
                x0, y0, x1, y1 = boxes_[maxIndex]
                plot_one_box(img_ori, [x0, y0, x1, y1], label=args.classes[labels_[maxIndex]] + ', {:.2f}%'.format(scores_[maxIndex] * 100), color=color_table[labels_[maxIndex]],distance=dist,angle=angle)
        res_name = input_image.split('/')[-1]

        #cv2.imwrite(os.path.join('results',res_name), img_ori)

        for i in range(len(boxes_)):
            if 0 != labels_[i]:
                x0, y0, x1, y1 = boxes_[i]
                plot_one_box(img_ori, [x0, y0, x1, y1], label=args.classes[labels_[i]] + ', {:.2f}%'.format(scores_[i] * 100), color=color_table[labels_[i]])
        # cv2.imshow('Detection result', img_ori)
        # cv2.imwrite('detection_result.jpg', img_ori)
        # cv2.waitKey(0)
        cv2.imwrite(os.path.join('resultsSegm',res_name), img_ori)
