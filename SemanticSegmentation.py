import numpy as np

class SemanticSegmentation:
    def __init__(self):
        self.counter = 0
        self.lastpixelXCar = -1
        self.lastpixelYCar = -1
        self.lastMaxAngle = 0
        self.imageWidth = 0
        self.imageHeight = 0

    def IsThereACarInThePicture(self,segmImage):
        array = np.frombuffer(segmImage.raw_data, dtype=np.dtype("uint8"))
        array = np.reshape(array, (segmImage.height, segmImage.width, 4))
        for i in range(0,segmImage.height,30):
            for j in range(0,segmImage.width,30):
                if array[i][j][2] == 10:
                    return True

        for i in range(0,segmImage.height,10):
            for j in range(0,segmImage.width,2):
                if array[i][j][2] == 10:
                    return True
        return False

    def BresenhamLine(self,x0, y0, x1, y1):
        counter = 0
        if x0 > x1:
            tmpX = x1
            tmpY = y1
            x1 = x0
            x0 = tmpX
            y1 = y0
            y0 = tmpY

        coords = []
        dx = x1 - x0
        dy = abs(y1 - y0)
        D = 2 * dy - dx
        y = y0

        for x in range(x0, x1 + 1):
            # if counter%3==0:
            coords.append([x, y])
            counter += 1
            while D > 0 and (x!=x1 or y != y1):
                y = y + (1 if y1 >= y0 else -1)
                # if counter % 3 == 0:
                coords.append([x, y])
                counter += 1
                D = D - 2 * dx
            D = D + 2 * dy
        return coords

    def IsThePointInsideElipse(self,x,y):
        y = self.imageHeight-y
        halfWidth = self.imageWidth//2
        halfHeight = self.imageHeight//2
        val = ((x-halfWidth)**2)/float((halfWidth//1)**2) + (y**2)/float((halfHeight//1)**2)
        return val <= 1

    def FindPossibleAngle(self, segmImage, bbox, maxAngle):
        self.imageHeight = segmImage.height
        self.imageWidth = segmImage.width
        bestBadPixels = 1000000
        XBestBadPixels = 0
        bestPercentage = 0

        if self.counter > 30:
            array = np.frombuffer(segmImage.raw_data, dtype=np.dtype("uint8"))
            array = np.reshape(array, (segmImage.height, segmImage.width, 4))
            if self.lastpixelYCar == -1:
                self.lastpixelXCar = segmImage.width//2
                self.lastpixelYCar = segmImage.height//2
            if len(bbox) != 0:
                xCoordTo = (int(bbox[1, 0]) + int(bbox[2, 0])) // 2
                yCoordTo = int(bbox[1, 1])
                self.lastpixelXCar = xCoordTo
                self.lastpixelYCar = yCoordTo
                self.lastMaxAngle = maxAngle

            prevDiffX = self.lastpixelXCar - self.imageWidth
            if self.lastMaxAngle != 0:
                currentDiffX = maxAngle/float(self.lastMaxAngle) * prevDiffX
                currentPredictedX = int(self.imageWidth + currentDiffX)
            else:
                currentPredictedX = self.lastpixelXCar

            middleX = segmImage.width//2
            if middleX >= currentPredictedX:
                XCoordsToCheck = np.arange(currentPredictedX,middleX+1,1)
            else:
                XCoordsToCheck = np.arange(currentPredictedX,middleX-1,-1)
            # print('LAST X AND Y',self.lastpixelXCar, self.lastpixelYCar)
            # print(XCoordsToCheck)
            # print(self.lastpixelXCar,middleX)
            for xCoord in XCoordsToCheck:
                coords = self.BresenhamLine(self.imageWidth//2,self.imageHeight-1,xCoord,self.lastpixelYCar)
                # print('coords:',coords)
                # print(self.imageWidth//2,self.imageHeight-1,xCoord,self.lastpixelYCar)
                badPixels = 0
                for coord in coords:
                    if self.IsThePointInsideElipse(coord[0],coord[1]):
                        if array[coord[1]][coord[0]][2] != 7 and array[coord[1]][coord[0]][2] != 6:
                            badPixels += 1
                if bestBadPixels > badPixels:
                    bestBadPixels = badPixels
                    XBestBadPixels = xCoord

                    overallDistX = len(XCoordsToCheck)
                    distFromX = abs(currentPredictedX - xCoord)
                    percentage = (overallDistX - distFromX) / overallDistX
                    percentage = percentage * percentage
                    bestPercentage = percentage

                if badPixels == 0:
                    res = []
                    for coord in coords:
                        if self.IsThePointInsideElipse(coord[0], coord[1]):
                            res.append([coord[0],coord[1]])
                    # print(res)
                    overallDistX = len(XCoordsToCheck)
                    distFromX = abs(currentPredictedX-xCoord)
                    percentage = (overallDistX-distFromX)/overallDistX
                    print('perc',percentage)
                    percentage = percentage*percentage
                    return percentage*maxAngle, res
            # check other side
            if middleX >= currentPredictedX:
                XCoordsToCheck = np.arange(middleX, self.imageWidth,1)
            else:
                XCoordsToCheck = np.arange(middleX,0,-1)
            for xCoord in XCoordsToCheck:
                coords = self.BresenhamLine(self.imageWidth//2,self.imageHeight-1,xCoord,self.lastpixelYCar)
                badPixels = 0
                for coord in coords:
                    if self.IsThePointInsideElipse(coord[0],coord[1]):
                        if array[coord[1]][coord[0]][2] != 7 and array[coord[1]][coord[0]][2] != 6:
                            badPixels += 1
                if bestBadPixels > badPixels:
                    bestBadPixels = badPixels
                    XBestBadPixels = xCoord
                    overallDistX = abs(currentPredictedX-middleX)
                    distFromX = abs(middleX-xCoord)
                    percentage = distFromX/overallDistX
                    percentage = percentage*percentage
                    percentage = -1 * percentage
                    bestPercentage = percentage
                if badPixels == 0:
                    res = []
                    for coord in coords:
                        if self.IsThePointInsideElipse(coord[0], coord[1]):
                            res.append([coord[0],coord[1]])
                    # print(res)
                    overallDistX = abs(currentPredictedX-middleX)
                    distFromX = abs(middleX-xCoord)
                    percentage = distFromX/overallDistX
                    print('perc',percentage*-1)
                    percentage = percentage*percentage
                    percentage = -1 * percentage
                    return percentage*maxAngle, res
            res = []
            coords = self.BresenhamLine(self.imageWidth // 2, self.imageHeight - 1, XBestBadPixels, self.lastpixelYCar)
            for coord in coords:
                if self.IsThePointInsideElipse(coord[0], coord[1]):
                    res.append([coord[0], coord[1]])
            print('Best perc',bestPercentage)
            return bestPercentage * maxAngle, res

        else:
            self.counter += 1
        return maxAngle, []


    def ObjectInFrontOfChasedCar(self, segmImage, bbox):
        if self.counter > 30:
            if len(bbox) != 0:
                xCoordTo = (int(bbox[1, 0]) + int(bbox[2, 0])) // 2
                yCoordTo = int(bbox[1, 1])
                self.lastpixelXCar = xCoordTo
                self.lastpixelYCar = yCoordTo
                print('using bbox')
            else:
                xCoordTo = segmImage.width//2
                yCoordTo = segmImage.height//2

            # print(segmImage.raw_data)
            array = np.frombuffer(segmImage.raw_data, dtype=np.dtype("uint8"))
            array = np.reshape(array, (segmImage.height, segmImage.width, 4))
            # carDetected = False
            for i in range(segmImage.height - yCoordTo):
                if array[segmImage.height-i-1][xCoordTo][2] == 10:
                    # carDetected = True
                    # print('CAR DETECTED')
                    return False, ''
                elif array[segmImage.height-i-1][xCoordTo][2] == 1 or array[segmImage.height-i-1][xCoordTo][2] == 2 or array[segmImage.height-i-1][xCoordTo][2] == 4 or \
                        array[segmImage.height-i-1][xCoordTo][2] == 11 or array[segmImage.height-i-1][xCoordTo][2] == 12:
                    print('BUILDING, CAREFUL')
                    for j in range(segmImage.width//2-1):
                        if array[segmImage.height-i-1][xCoordTo+j][2] != 1 and array[segmImage.height-i-1][xCoordTo+j][2] != 2 and array[segmImage.height-i-1][xCoordTo+j][2] != 4 and \
                                array[segmImage.height-i-1][xCoordTo+j][2] != 11 and array[segmImage.height-i-1][xCoordTo+j][2] != 12:
                            print('GO RIGHT')
                            return True, 'RIGHT'
                        elif array[segmImage.height-i-1][xCoordTo-1][2] != 1 and array[segmImage.height-i-1][xCoordTo-1][2] != 2 and array[segmImage.height-i-1][xCoordTo-1][2] != 4 and \
                                array[segmImage.height-i-1][xCoordTo-1][2] != 11 and array[segmImage.height-i-1][xCoordTo-1][2] != 12:
                            print('GO LEFT')
                            return True, 'LEFT'
        else:
            self.counter += 1
        return False, ''
                # return True
                # break
        # print('TEEEST',array[0][400][2])