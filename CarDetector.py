import math
from client_bounding_boxes import ClientSideBoundingBoxes
import numpy as np
import cv2
import random

VIEW_WIDTH = 800
VIEW_HEIGHT = 600
VIEW_FOV = 90

class CarDetector:
    def __init__(self):
        self.boundingBoxes = ClientSideBoundingBoxes()
        self.consecutiveFramesLeft = 0
        self.lastN = 5
        self.lastNDistances = []
        self.lastNAngles = []
        self.exponentialMovingAverageDist = 0
        self.exponentialMovingAverageAngle = 0
        self.alpha = 0.5

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

    def CreateBoundBoxMistakes(self, boundingBox):
        # Not returning any bounding box at all
        # the chance defined as 10% overall, but let's make it so there are consecutive frames where nothing is found
        if self.consecutiveFramesLeft > 0:
            self.consecutiveFramesLeft -= 1
            return []
        elif random.randint(1,30) == 1:
            self.consecutiveFramesLeft = random.randint(1,5)
            return []
        else:
            bbBoxes = np.array(boundingBox)
            for i in range(len(bbBoxes)):
                # print(bbBoxes)
                # print(bbBoxes[0])
                # print(bbBoxes[0][0])
                # print(bbBoxes[0][0][0])
                front_indices = [0,3,4,7] # front of the car bounding box indices
                back_indices = [1,2,5,6] # back of the car bounding box indices

                #Do the change depending on the size of the bounding box
                sizewidthFront = abs(bbBoxes[i][4][0]-bbBoxes[i][7][0])
                sizeheightFront = abs(bbBoxes[i][0][1]-bbBoxes[i][4][1])
                sizewidthBack = abs(bbBoxes[i][5][0]-bbBoxes[i][6][0])
                sizeheightBack = abs(bbBoxes[i][1][1]-bbBoxes[i][5][1])


                xMoveFront = (1 if np.random.randint(0,1) == 0 else -1) * np.random.exponential(1) * sizewidthFront / VIEW_WIDTH * 10
                yMoveFront = (1 if np.random.randint(0, 1) == 0 else -1) * np.random.exponential(1) * sizeheightFront / VIEW_HEIGHT * 10
                xMoveBack = (1 if np.random.randint(0, 1) == 0 else -1) * np.random.exponential(1) * sizewidthBack / VIEW_WIDTH * 10
                yMoveBack = (1 if np.random.randint(0, 1) == 0 else -1) * np.random.exponential(1) * sizeheightBack / VIEW_HEIGHT * 10

                print(xMoveFront, yMoveFront, xMoveBack, yMoveBack)

                for j in front_indices:
                    bbBoxes[i][j][0] += xMoveFront
                    bbBoxes[i][j][1] += yMoveFront

                for j in back_indices:
                    bbBoxes[i][j][0] += xMoveBack
                    bbBoxes[i][j][0] += yMoveBack

                # for ind in indices:
                #     boundingBox[0][ind] += 20
            return bbBoxes

    # Calculates rotation matrix to euler angles
    # The result is the same as MATLAB except the order
    # of the euler angles ( x and z are swapped ).
    def rotationMatrixToEulerAngles(self,R):

        sy = math.sqrt(R[0, 0] * R[0, 0] + R[1, 0] * R[1, 0])

        singular = sy < 1e-6

        if not singular:
            x = math.atan2(R[2, 1], R[2, 2])
            y = math.atan2(-R[2, 0], sy)
            z = math.atan2(R[1, 0], R[0, 0])
        else:
            x = math.atan2(-R[1, 2], R[1, 1])
            y = math.atan2(-R[2, 0], sy)
            z = 0

        return np.array([math.degrees(x), math.degrees(y), math.degrees(z)])


    def getDistance(self, vehicle, camera):
        calibration = np.identity(3)
        calibration[0, 2] = VIEW_WIDTH / 2.0
        calibration[1, 2] = VIEW_HEIGHT / 2.0
        calibration[0, 0] = calibration[1, 1] = VIEW_WIDTH / (2.0 * np.tan(VIEW_FOV * np.pi / 360.0))
        camera.calibration = calibration # intrinsic camera matrix

        bounding_boxes = self.boundingBoxes.get_bounding_boxes([vehicle], camera) # bounding boxes in images
        bounding_boxes = self.CreateBoundBoxMistakes(bounding_boxes)
        if len(bounding_boxes) == 0:
            if len(self.lastNDistances) >= 2:
                predicted_distance = 2 * self.lastNDistances[-1] - self.lastNDistances[-2] #simple extrapolation
                predicted_angle = 2 * self.lastNAngles[-1] - self.lastNAngles[-2] #simple extrapolation
                self.exponentialMovingAverageDist = self.alpha * predicted_distance + (1 - self.alpha) * self.exponentialMovingAverageDist
                self.exponentialMovingAverageAngle = self.alpha * predicted_angle + (1 - self.alpha) * self.exponentialMovingAverageAngle

                self.lastNDistances.append(predicted_distance)
                self.lastNAngles.append(predicted_angle)
                if len(self.lastNDistances) > self.lastN:
                    self.lastNDistances = self.lastNDistances[1:]
                    self.lastNAngles = self.lastNAngles[1:]

                print('estimated angle:', predicted_angle)

                return bounding_boxes, self.exponentialMovingAverageDist, self.exponentialMovingAverageAngle

            return bounding_boxes, -1, 0
        bounding_boxes = bounding_boxes[0]
        points = [(float(bounding_boxes[i, 0]), float(bounding_boxes[i, 1])) for i in range(8)] # image points

        car_bb = self.boundingBoxes._create_bb_points(vehicle) # world bb coords
        res_car_bb = []#car_bbcar_bb[0]
        median_bb = []
        for i in range(len(car_bb[1])):
            median_bb.append((car_bb[1][i] + car_bb[6][i])/2.0)
        # print(car_bb[1])
        # print(car_bb[6])
        for i in range(len(car_bb)):
            tmp = car_bb[i] - median_bb # - car_bb[0]
            res_car_bb.append([tmp[0],tmp[1],tmp[2]]) # object points
        res_car_bb = np.array(res_car_bb,dtype=float)
        res_car_bb = np.reshape(res_car_bb,(8,3,1))
        points = np.array(points,dtype=float)
        points = np.reshape(points,(8,2,1))
        # res_car_bb = res_car_bb[:3]
        # points = points[:3]

        distortion = np.zeros((4,1))
        ret, rvecs, tvecs = cv2.solvePnP(res_car_bb, points, calibration,distortion)
        rodr = cv2.Rodrigues(rvecs)[0]
        print('rodr',math.degrees(math.atan2(rodr[0][0], rodr[2][0])))
        # print('rodr',math.degrees(math.asin(rodr[2][1])))
        # print('pred angle:',math.degrees(math.atan2(-tvecs[0][0],-tvecs[2][0])))
        # print('predicted angle',self.getAngle([-0.3,0],[-0.3,1],[tvecs[0][0],abs(tvecs[2][0])]))
        tmp_Predicted_Angle = math.degrees(math.atan2(-tvecs[0][0],-tvecs[2][0]))
        # print('tvecs',tvecs)




        # print(tvecs)
        tmp_Predicted_Distance = math.sqrt(tvecs[0][0]**2+tvecs[1][0]**2+tvecs[2][0]**2)

        # korekce
        triangleAngle = 0
        if tmp_Predicted_Angle >= 0:
            triangleAngle = 90.0 - tmp_Predicted_Angle
        elif tmp_Predicted_Angle < 0:
            triangleAngle = 90.0 + (-1* tmp_Predicted_Angle)

        prvniStrana = 0.001

        # Cosinova veta na spocteni 3. strany trojuhelnika
        predicted_distance = math.sqrt(prvniStrana**2+tmp_Predicted_Distance**2-2*prvniStrana*tmp_Predicted_Distance*math.cos(math.radians(triangleAngle)))
        # print(predicted_distance,tmp_Predicted_Distance, triangleAngle)
        # print(math.acos((0.3**2+predicted_distance**2-tmp_Predicted_Distance**2)/(2*0.3*predicted_distance)))

        tmpAngle = math.degrees(math.acos((prvniStrana**2+predicted_distance**2-tmp_Predicted_Distance**2)/(2*prvniStrana*predicted_distance)))

        if tmp_Predicted_Angle >= 0:
            predicted_Angle = 90.0 - (180-tmpAngle)
        else:
            predicted_Angle = -1* (90.0 - (tmpAngle))

        print('pred distance:', predicted_distance)
        print('pred angle:', predicted_Angle)


        # print('predicted dist:',predicted_distance)

        # print(points)
        self.lastNDistances.append(predicted_distance)
        self.lastNAngles.append(predicted_Angle)
        if len(self.lastNDistances) > self.lastN:
            self.lastNDistances = self.lastNDistances[1:]
            self.lastNAngles = self.lastNAngles[1:]
        alpha = self.alpha if len(self.lastNDistances) > 1 else 1
        self.exponentialMovingAverageDist = alpha * predicted_distance + (1 - alpha) * self.exponentialMovingAverageDist
        self.exponentialMovingAverageAngle = alpha * predicted_Angle + (1 - alpha) * self.exponentialMovingAverageAngle

        return bounding_boxes, predicted_distance, predicted_Angle
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
