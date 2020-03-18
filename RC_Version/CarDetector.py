# coding: utf-8

from __future__ import division, print_function

import tensorflow as tf
import numpy as np
import cv2
import math

from utils.misc_utils import parse_anchors, read_class_names
from utils.nms_utils import gpu_nms
from utils.data_aug import letterbox_resize

from model import yolov3


class CarDetector:
    def __init__(self):
        self.MODEL_NAME = './model/best_model_Epoch_28_step_1565_mAP_0.9963_loss_0.4472_lr_0.0001'
        self.new_size = [416, 416]
        self.anchors = parse_anchors('model/yolo_anchors.txt')
        self.classes = read_class_names('model/coco.names')
        self.num_class = len(self.classes)
        self.height_ori, self.width_ori = 0,0
        self.letterbox_resize = True

        self.lastN = 5
        self.lastNDistances = []
        self.lastNAngles = []
        self.exponentialMovingAverageDist = 0
        self.exponentialMovingAverageAngle = 0
        self.alpha = 0.5

        self.sess = tf.Session()


        self.input_data = tf.placeholder(tf.float32, [1, self.new_size[1], self.new_size[0], 3], name='input_data')
        self.yolo_model = yolov3(self.num_class, self.anchors)

        with tf.variable_scope('yolov3'):
            pred_feature_maps = self.yolo_model.forward(self.input_data, False)
        self.pred_boxes, self.pred_confs, self.pred_probs = self.yolo_model.predict(pred_feature_maps)

        self.pred_scores = self.pred_confs * self.pred_probs

        self.boxes, self.scores, self.labels = gpu_nms(self.pred_boxes, self.pred_scores, self.num_class, max_boxes=200, score_thresh=0.3,
                                        nms_thresh=0.45)

        self.saver = tf.train.Saver()
        self.saver.restore(self.sess, self.MODEL_NAME)


    def getDistanceAndAngle(self, box,width_ori,height_ori):
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
        # print(tvecs)
        angle = math.degrees(math.atan2(tvecs[0][0], tvecs[2][0]))
        distance = math.sqrt(tvecs[0][0] ** 2 + tvecs[1][0] ** 2 + tvecs[2][0] ** 2)
        # print(angle)

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

    def GetBoundingBox(self,input_image,half):
        img_ori = cv2.imread(input_image)
        if half: # Grab left half of the image
            height, width = img_ori.shape[:2]
            start_row, start_col = int(0), int(0)
            end_row, end_col = int(height), int(width//2)
            img_ori = img_ori[start_row:end_row, start_col:end_col]

        self.height_ori, self.width_ori = img_ori.shape[:2]
        if self.letterbox_resize:
            img, resize_ratio, dw, dh = letterbox_resize(img_ori, self.new_size[0], self.new_size[1])
        else:
            height_ori, width_ori = img_ori.shape[:2]
            img = cv2.resize(img_ori, tuple(self.new_size))
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        img = np.asarray(img, np.float32)
        img = img[np.newaxis, :] / 255.

        boxes_, scores_, labels_ = self.sess.run([self.boxes, self.scores, self.labels], feed_dict={self.input_data: img})

        # rescale the coordinates to the original image
        if self.letterbox_resize:
            boxes_[:, [0, 2]] = (boxes_[:, [0, 2]] - dw) / resize_ratio
            boxes_[:, [1, 3]] = (boxes_[:, [1, 3]] - dh) / resize_ratio
        else:
            boxes_[:, [0, 2]] *= (width_ori / float(self.new_size[0]))
            boxes_[:, [1, 3]] *= (height_ori / float(self.new_size[1]))

        print("box coords:")
        print(boxes_)
        print('*' * 30)
        print("scores:")
        print(scores_)
        print('*' * 30)
        print("labels:")
        print(labels_)

        return boxes_, scores_

    def Extrapolate(self):
        if len(self.lastNDistances) >= 2:
            predicted_distance = 2 * self.lastNDistances[-1] - self.lastNDistances[-2]  # simple extrapolation
            predicted_angle = 2 * self.lastNAngles[-1] - self.lastNAngles[-2]  # simple extrapolation

            predicted_angle = self.LimitAngles(predicted_angle)
            alpha = self.alpha if len(self.lastNDistances) > 1 else 1
            self.exponentialMovingAverageDist = alpha * predicted_distance + (
                                                                                  1 - self.alpha) * self.exponentialMovingAverageDist
            self.exponentialMovingAverageAngle = alpha * predicted_angle + (
                                                                                1 - self.alpha) * self.exponentialMovingAverageAngle

            self.lastNDistances.append(predicted_distance)
            self.lastNAngles.append(predicted_angle)
            return self.exponentialMovingAverageDist, self.exponentialMovingAverageAngle
        else:
            return 0,0

    def LimitAngles(self,angle):
        return min(max(angle,-175),175)

    def KeepLastN(self):
        if len(self.lastNDistances) > self.lastN:
            self.lastNDistances = self.lastNDistances[1:]
            self.lastNAngles = self.lastNAngles[1:]


    def Run(self,img_name,half=True):
        boxes, scores = self.GetBoundingBox(img_name,half)
        if len(boxes) != 0:
            dist, angle = self.getDistanceAndAngle(boxes[np.argmax(scores)], self.width_ori, self.height_ori)
            self.lastNDistances.append(dist)
            self.lastNAngles.append(angle)
            alpha = self.alpha if len(self.lastNDistances) > 1 else 1
            self.exponentialMovingAverageDist = alpha * dist + (1 - alpha) * self.exponentialMovingAverageDist
            self.exponentialMovingAverageAngle = alpha * angle + (1 - alpha) * self.exponentialMovingAverageAngle

        else:
            dist, angle = self.Extrapolate()
        self.KeepLastN()
        angle = self.LimitAngles(angle)
        return dist, angle