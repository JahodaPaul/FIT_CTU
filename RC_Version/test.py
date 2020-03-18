from CarDetector import CarDetector

img_name = '/home/pjahoda/Documents/YOLOv3_TensorFlow/data/my_data/testImg/326.png'
img_name = '/media/pjahoda/Local disk/Jahoda_test_1/images/img_1570690181997677.jpg' # full image (from both cameras)

#TODO test with full image

cDet = CarDetector()
cDet.Run(img_name,True)