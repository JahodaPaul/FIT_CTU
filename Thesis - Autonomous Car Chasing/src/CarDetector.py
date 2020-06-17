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
        self.bboxInARow = 0

    def CreatePointInFrontOFCar(self, x, y, angle):
        x2 = math.cos(math.radians(angle))
        y2 = math.sin(math.radians(angle))
        return x+x2, y+y2

    def getAngle(self, orig, firstP, secondP):
        vecA = [firstP[0]-orig[0],firstP[1]-orig[1]]
        vecB = [secondP[0]-orig[0],secondP[1]-orig[1]]
        AB = vecA[0]*vecB[0] + vecA[1]*vecB[1]

        det = vecA[0] * vecB[1] - vecA[1] * vecB[0]  # determinant
        angle = math.degrees(math.atan2(det, AB))
        return angle

    def CreateBoundBoxMistakes(self, boundingBox,nOfFramesToSkip=0):
        # Not returning any bounding box at all
        # the chance defined as 10% overall, but we make it so there are consecutive frames where nothing is found
        # if self.consecutiveFramesLeft > 0:
        #     self.consecutiveFramesLeft -= 1
        #     return []
        # elif random.randint(1,30) == 1:
        #     self.consecutiveFramesLeft = random.randint(1,5)
        #     return []
        if random.randint(0,99) < nOfFramesToSkip:
            return []
        else:
            bbBoxes = np.array(boundingBox)
            for i in range(len(bbBoxes)):
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

                for j in front_indices:
                    bbBoxes[i][j][0] += xMoveFront
                    bbBoxes[i][j][1] += yMoveFront

                for j in back_indices:
                    bbBoxes[i][j][0] += xMoveBack
                    bbBoxes[i][j][0] += yMoveBack

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

    def LimitAngles(self,angle):
        return min(max(angle,-175),175)


    def getDistance(self, vehicle, camera, carInTheImage=True, extrapolation=True, nOfFramesToSkip=0):
        calibration = np.identity(3)
        calibration[0, 2] = VIEW_WIDTH / 2.0
        calibration[1, 2] = VIEW_HEIGHT / 2.0
        calibration[0, 0] = calibration[1, 1] = VIEW_WIDTH / (2.0 * np.tan(VIEW_FOV * np.pi / 360.0))
        camera.calibration = calibration # intrinsic camera matrix

        bounding_boxes = self.boundingBoxes.get_bounding_boxes([vehicle], camera) # bounding boxes in images
        bounding_boxes = self.CreateBoundBoxMistakes(bounding_boxes,nOfFramesToSkip)
        if not carInTheImage:
            bounding_boxes = []
        if len(bounding_boxes) == 0:
            if len(self.lastNDistances) >= 2:
                if extrapolation:
                    predicted_distance = 2 * self.lastNDistances[-1] - self.lastNDistances[-2] #simple extrapolation
                    predicted_angle = 2 * self.lastNAngles[-1] - self.lastNAngles[-2] #simple extrapolation
                else:
                    predicted_distance = self.lastNDistances[-1]
                    predicted_angle = self.lastNAngles[-1]

                predicted_angle = self.LimitAngles(predicted_angle)
                self.exponentialMovingAverageDist = self.alpha * predicted_distance + (1 - self.alpha) * self.exponentialMovingAverageDist
                self.exponentialMovingAverageAngle = self.alpha * predicted_angle + (1 - self.alpha) * self.exponentialMovingAverageAngle

                self.lastNDistances.append(predicted_distance)
                self.lastNAngles.append(predicted_angle)
                self.bboxInARow = 0
                if len(self.lastNDistances) > self.lastN:
                    self.lastNDistances = self.lastNDistances[1:]
                    self.lastNAngles = self.lastNAngles[1:]

                if extrapolation:
                    return bounding_boxes, self.exponentialMovingAverageDist, self.exponentialMovingAverageAngle
                else:
                    return bounding_boxes, self.lastNDistances[-1], self.lastNAngles[-1]

            return bounding_boxes, -1, 0
        bounding_boxes = bounding_boxes[0]
        points = [(float(bounding_boxes[i, 0]), float(bounding_boxes[i, 1])) for i in range(8)] # image points

        car_bb = self.boundingBoxes._create_bb_points(vehicle) # world bb coords
        res_car_bb = []
        median_bb = []
        for i in range(len(car_bb[1])):
            median_bb.append((car_bb[1][i] + car_bb[6][i])/2.0)

        for i in range(len(car_bb)):
            tmp = car_bb[i] - median_bb
            res_car_bb.append([tmp[0],tmp[1],tmp[2]]) # object points
        res_car_bb = np.array(res_car_bb,dtype=float)
        res_car_bb = np.reshape(res_car_bb,(8,3,1))
        points = np.array(points,dtype=float)
        points = np.reshape(points,(8,2,1))


        distortion = np.zeros((4,1))
        ret, rvecs, tvecs = cv2.solvePnP(res_car_bb, points, calibration,distortion)

        tmp_Predicted_Angle = math.degrees(math.atan2(-tvecs[0][0],-tvecs[2][0]))
        tmp_Predicted_Distance = math.sqrt(tvecs[0][0]**2+tvecs[1][0]**2+tvecs[2][0]**2)

        # korekce
        triangleAngle = 0
        if tmp_Predicted_Angle >= 0:
            triangleAngle = 90.0 - tmp_Predicted_Angle
        elif tmp_Predicted_Angle < 0:
            triangleAngle = 90.0 + (-1* tmp_Predicted_Angle)

        prvniStrana = 0.3

        # Cosinova veta na spocteni 3. strany trojuhelnika
        predicted_distance = math.sqrt(prvniStrana**2+tmp_Predicted_Distance**2-2*prvniStrana*tmp_Predicted_Distance*math.cos(math.radians(triangleAngle)))

        tmpAngle = math.degrees(math.acos((prvniStrana**2+predicted_distance**2-tmp_Predicted_Distance**2)/(2*prvniStrana*predicted_distance)))

        if tmp_Predicted_Angle >= 0:
            predicted_Angle = 90.0 - (180-tmpAngle)
        else:
            predicted_Angle = -1* (90.0 - (tmpAngle))

        predicted_Angle = self.LimitAngles(predicted_Angle)

        if self.bboxInARow == 0:
            self.lastNDistances.append(predicted_distance)
            self.lastNAngles.append(predicted_Angle)
            if len(self.lastNDistances) > self.lastN:
                self.lastNDistances = self.lastNDistances[1:]
                self.lastNAngles = self.lastNAngles[1:]
            self.bboxInARow += 1

            # Makes the extrapolation better during high false negative rate
            # Fixes the situations where we don't see the car for a long period and then we see it and these situations
            # the previous extrapolation might be way off from the current estimation which causes the new linear extrapolation
            # to be very wong
            if len(self.lastNAngles) >= 2 and predicted_Angle > 0 and self.lastNAngles[-2] > predicted_Angle:
                self.lastNAngles[-2] = predicted_Angle-1
            elif len(self.lastNAngles) >= 2 and predicted_Angle < 0 and self.lastNAngles[-2] < predicted_Angle:
                self.lastNAngles[-2] = predicted_Angle+1
            elif len(self.lastNAngles) >= 2 and predicted_Angle < 0 and self.lastNAngles[-2] > predicted_Angle:
                self.lastNAngles[-2] = min(predicted_Angle+1,self.lastNAngles[-2])
            elif len(self.lastNAngles) >= 2 and predicted_Angle > 0 and self.lastNAngles[-2] < predicted_Angle:
                self.lastNAngles[-2] = max(predicted_Angle - 1,self.lastNAngles[-2])
            if len(self.lastNDistances) >= 2 and predicted_distance > 0 and self.lastNDistances[-2] > predicted_distance:
                self.lastNDistances[-2] = predicted_distance - 1
            elif len(self.lastNDistances) >= 2:
                self.lastNDistances[-2] = predicted_distance
        else:
            self.lastNDistances.append(predicted_distance)
            self.lastNAngles.append(predicted_Angle)
            if len(self.lastNDistances) > self.lastN:
                self.lastNDistances = self.lastNDistances[1:]
                self.lastNAngles = self.lastNAngles[1:]
            self.bboxInARow += 1
        alpha = self.alpha if len(self.lastNDistances) > 1 else 1
        self.exponentialMovingAverageDist = alpha * predicted_distance + (1 - alpha) * self.exponentialMovingAverageDist
        self.exponentialMovingAverageAngle = alpha * predicted_Angle + (1 - alpha) * self.exponentialMovingAverageAngle

        return bounding_boxes, predicted_distance, predicted_Angle


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
