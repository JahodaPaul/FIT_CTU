from CarDetector import CarDetector
import cv2

img_name = '/home/pjahoda/Documents/YOLOv3_TensorFlow/data/my_data/testImg/326.png'
img_name = '/media/pjahoda/Local disk/Jahoda_test_1/images/img_1570690181997677.jpg' # full image (from both cameras)
img_name = '/home/pjahoda/Documents/CARLA_0.9.7.4/PythonAPI/self-driving-following-car/RC_Version/test_img.jpg'
# img_name = '/home/ctuxavier/Desktop/toyota-rc-car/code/jetson/test_img.jpg'

#TODO test with full image

print('starting to read image')
img_ori = cv2.imread(img_name)
print('image read')

cDet = CarDetector()

dirr = '/home/pjahoda/Downloads/Jahoda_vid2'
import os
arr = os.listdir(dirr)
# print(arr)
for fil in arr:
    path = os.path.join(dirr,fil)
    img_ori = cv2.imread(path)
    print(cDet.Run(img_ori,False))
# cDet.Run(img_ori,True)