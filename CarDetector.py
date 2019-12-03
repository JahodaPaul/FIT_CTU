import math
from client_bounding_boxes import ClientSideBoundingBoxes
import numpy as np
import cv2

VIEW_WIDTH = 800
VIEW_HEIGHT = 600
VIEW_FOV = 90

class CarDetector:
    def __init__(self):
        self.boundingBoxes = ClientSideBoundingBoxes()

    def CreatePointInFrontOFCar(self, x, y, angle):
        x2 = math.cos(math.radians(angle))
        y2 = math.sin(math.radians(angle))
        return x+x2, y+y2

    def getAngle(self, orig, firstP, secondP):
        vecA = [firstP[0]-orig[0],firstP[1]-orig[1]]
        vecB = [secondP[0]-orig[0],secondP[1]-orig[1]]
        AB = vecA[0]*vecB[0] + vecA[1]*vecB[1]
        # distA = math.sqrt(vecA[0]*vecA[0] + vecA[1]*vecA[1])
        # distB = math.sqrt(vecB[0] * vecB[0] + vecB[1] * vecB[1])

        # ang = math.degrees(math.acos(AB/(distA*distB)))
        # print(ang)
        det = vecA[0] * vecB[1] - vecA[1] * vecB[0]  # determinant
        angle = math.degrees(math.atan2(det, AB))
        # ang = math.degrees(math.atan2(secondP[1] - firstP[1], secondP[0] - firstP[0]) - math.atan2(firstP[1] - orig[1], firstP[0] - orig[0]))
        # print(angle)
        # return ang + 360 if ang < 0 else ang
        return angle

    def getDistance(self, vehicle, camera):
        calibration = np.identity(3)
        calibration[0, 2] = VIEW_WIDTH / 2.0
        calibration[1, 2] = VIEW_HEIGHT / 2.0
        calibration[0, 0] = calibration[1, 1] = VIEW_WIDTH / (2.0 * np.tan(VIEW_FOV * np.pi / 360.0))
        camera.calibration = calibration # intrinsic camera matrix

        bounding_boxes = self.boundingBoxes.get_bounding_boxes([vehicle], camera) # bounding boxes in images
        if len(bounding_boxes) == 0:
            return bounding_boxes, -1
        bounding_boxes = bounding_boxes[0]
        points = [(float(bounding_boxes[i, 0]), float(bounding_boxes[i, 1])) for i in range(8)] # image points

        car_bb = self.boundingBoxes._create_bb_points(vehicle) # world bb coords
        res_car_bb = []#car_bbcar_bb[0]
        for i in range(len(car_bb)):
            tmp = car_bb[i] - car_bb[0]
            res_car_bb.append([tmp[0],tmp[1],tmp[2]]) # object points
        res_car_bb = np.array(res_car_bb,dtype=float)
        res_car_bb = np.reshape(res_car_bb,(8,3,1))
        points = np.array(points,dtype=float)
        points = np.reshape(points,(8,2,1))
        # res_car_bb = res_car_bb[:3]
        # points = points[:3]

        distortion = np.zeros((4,1))
        ret, rvecs, tvecs = cv2.solvePnP(res_car_bb, points, calibration,distortion)
        print(rvecs)
        # print(tvecs[0][0])
        predicted_distance = math.sqrt(tvecs[0][0]**2+tvecs[1][0]**2+tvecs[2][0]**2)
        print('predicted dist:',predicted_distance)

        # print(points)
        return bounding_boxes, predicted_distance
        # print(res_car_bb)


# # Tests
# c = CarDetector()
# pX1,pY1 = c.CreatePointInFrontOFCar(50,50,-170)
# c.getAngle([50,50],[pX1,pY1],[55,49])
#
# pX1,pY1 = c.CreatePointInFrontOFCar(50,50,170)
# c.getAngle([50,50],[pX1,pY1],[50,53])
#
# pX1,pY1 = c.CreatePointInFrontOFCar(50,50,45)
# c.getAngle([50,50],[pX1,pY1],[51,51])
#
# pX1,pY1 = c.CreatePointInFrontOFCar(50,50,45)
# c.getAngle([50,50],[pX1,pY1],[49,49])
#
# pX1,pY1 = c.CreatePointInFrontOFCar(50,50,45)
# c.getAngle([50,50],[pX1,pY1],[50,49])

# pX1,pY1 = c.CreatePointInFrontOFCar(50,50,0)
# c.getAngle([50,50],[pX1,pY1],[55,49])
#
# pX1,pY1 = c.CreatePointInFrontOFCar(50,50,90)
# c.getAngle([50,50],[pX1,pY1],[55,49])
#
# pX1,pY1 = c.CreatePointInFrontOFCar(50,50,-90)
# c.getAngle([50,50],[pX1,pY1],[55,49])
