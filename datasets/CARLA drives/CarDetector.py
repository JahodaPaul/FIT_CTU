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
        if self.consecutiveFramesLeft > 0:
            self.consecutiveFramesLeft -= 1
            return []
        elif random.randint(1,30) == 1:
            self.consecutiveFramesLeft = random.randint(1,5)
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


    def get3DboundingBox(self, vehicle, camera, carInTheImage=True, extrapolation=True, nOfFramesToSkip=0):
        bounding_boxes = self.boundingBoxes.get_bounding_boxes([vehicle], camera) # bounding boxes in images
        bounding_boxes = self.CreateBoundBoxMistakes(bounding_boxes,nOfFramesToSkip)
        if not carInTheImage:
            bounding_boxes = []

        bounding_boxes = bounding_boxes[0]
        return bounding_boxes