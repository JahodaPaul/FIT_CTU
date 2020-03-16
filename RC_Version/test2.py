import tensorflow as tf
from model import yolov3
from utils.misc_utils import parse_anchors, read_class_names
from utils.nms_utils import gpu_nms
#from utils.data_aug import letterbox_resize

MODEL_NAME = './model/best_model_Epoch_28_step_1565_mAP_0.9963_loss_0.4472_lr_0.0001'
new_size = [416, 416]
anchors = parse_anchors('model/yolo_anchors.txt')
classes = read_class_names('model/coco.names')
num_class = len(classes)
height_ori, width_ori = 0, 0
#letterbox_resize = True

sess = tf.Session()

#with tf.Session() as sess:
input_data = tf.placeholder(tf.float32, [1, new_size[1], new_size[0], 3], name='input_data')
yolo_model = yolov3(num_class, anchors)

with tf.variable_scope('yolov3'):
    pred_feature_maps = yolo_model.forward(input_data, False)
pred_boxes, pred_confs, pred_probs = yolo_model.predict(pred_feature_maps)

pred_scores = pred_confs * pred_probs

boxes, scores, labels = gpu_nms(pred_boxes, pred_scores, num_class, max_boxes=200, score_thresh=0.3,
                                nms_thresh=0.45)

saver = tf.train.Saver()
saver.restore(sess, MODEL_NAME)