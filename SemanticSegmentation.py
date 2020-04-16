import numpy as np

class SemanticSegmentation:
    def __init__(self):
        self.counter = 0
        self.lastpixelXCar = -1
        self.lastpixelYCar = -1
        self.lastMaxAngle = 0
        self.imageWidth = 0
        self.imageHeight = 0

        self.prevAngle = 0
        self.arrNBadPixels = []
        self.CoordRectangles = [] #y,x

        self.lastN = 5
        self.lastNX = []
        self.lastNY = []
        self.exponentialMovingAverageX = 0
        self.exponentialMovingAverageY = 0
        self.alpha = 0.5

        self.size_w = 0
        self.size_h = 0

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

    def BresenhamLineSample(self,arr, k):
        if k >= len(arr):
            return arr
        else:
            x0 = 0
            x1 = k - 1
            y0 = 0
            y1 = len(arr) - (k + 1)

        dx = x1 - x0
        dy = abs(y1 - y0)
        D = 2 * dy - dx
        y = y0
        res = []
        counter = 0

        for x in range(x0, x1 + 1):
            res.append(arr[counter])
            counter += 1
            while D > 0 and (x != x1 or y != y1):
                y = y + (1 if y1 >= y0 else -1)
                counter += 1
                D = D - 2 * dx
            D = D + 2 * dy
        return res

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

    def GetPercentage(self,middleX,xCoord, currentPredictedX, otherSide=False):
        overallDistX = abs(currentPredictedX - middleX)
        distFromMiddle = abs(middleX - xCoord)
        percentage = distFromMiddle / overallDistX
        # percentage = percentage * percentage
        if otherSide:
            percentage = -1 * percentage
        return percentage


    def AngleBasedOnPreviousAngle(self, currentCarAngle):
        # with open('test.txt','a') as f:
        #     f.write(str(self.prevAngle) + '\n')
        #     f.write(str(self.arrNBadPixels) + '\n')
        # print(self.prevAngle)
        # print(self.arrNBadPixels)
        # add +1 to everyone,
        b = True
        arrMax = 0
        for i in range(len(self.arrNBadPixels)):
            if self.arrNBadPixels[i][0] != 0 and abs(self.arrNBadPixels[i][2] - 1) < 0.15:
                b = False
            self.arrNBadPixels[i][0] += 1
            if arrMax < self.arrNBadPixels[i][0]:
                arrMax = self.arrNBadPixels[i][0]
        if b:
            # with open('test.txt', 'a') as f:
            #     f.write('CHANGE' + '\n')
            return 1,0
        tmp = [0 for i in range(len(self.arrNBadPixels))]
        # add difference from prevAngle
        # penalize change

        for i in range(len(self.arrNBadPixels)):
            tmp[i] += abs(self.prevAngle - (currentCarAngle*self.arrNBadPixels[i][2]))

        tmpMax = np.max(tmp)
        for i in range(len(self.arrNBadPixels)):
            tmp[i] /= float(tmpMax)

        for i in range(len(self.arrNBadPixels)):
            self.arrNBadPixels[i][0] *= tmp[i]
        self.arrNBadPixels.sort()
        # with open('test.txt','a') as f:
        #     f.write(str(currentCarAngle) + '\n')
        #     f.write(str(self.prevAngle) + '\n')
        #     f.write(str(self.arrNBadPixels) + '\n')
        return self.arrNBadPixels[0][2], self.arrNBadPixels[0][1]

    def parse_segm(self,segmImage, obj):
        array = np.frombuffer(segmImage.raw_data, dtype=np.dtype("uint8"))
        array = np.reshape(array, (segmImage.height, segmImage.width, 4))

        n_cols = 10
        n_rows = 10
        self.size_w = self.imageWidth // n_cols
        self.size_h = self.imageHeight // n_rows

        rows = self.imageHeight // self.size_h
        cols = self.imageWidth // self.size_w
        objects = []
        if len(self.CoordRectangles) == 0:
            for i in range(rows):
                for j in range(cols):
                    self.CoordRectangles.append([i * self.size_h + (self.size_h//2),j * self.size_w + (self.size_w//2)])

        for i in range(rows):
            for j in range(cols):
                half_of_pixels = self.size_w * self.size_h // 2
                half_of_pixels = half_of_pixels//25
                counter = 0
                for k in range(self.size_h):
                    if k%5 == 1:
                        for l in range(self.size_w):
                            if l%5==1:
                                if (array[i * self.size_h + k][j * self.size_w + l][2] == 6 or array[i * self.size_h + k][j * self.size_w + l][2] == 7):
                                    if not (i * self.size_h + k >= int(obj[2]) and i * self.size_h + k <= int(obj[3]) and j * self.size_w + l >= int(obj[0]) and j * self.size_w + l <= int(obj[1])):
                                        counter += 1
                if counter >= half_of_pixels:
                    objects.extend([1])
                else:
                    objects.extend([0])
        return objects

    def FindClosestRect(self,x,y):
        smallestVal = 10000000
        smallestIndex = 0
        for i in range(len(self.CoordRectangles)):
            if abs(self.CoordRectangles[i][0] - y) + abs(self.CoordRectangles[i][1] - x) < smallestVal:
                smallestVal = abs(self.CoordRectangles[i][0] - y) + abs(self.CoordRectangles[i][1] - x)
                smallestIndex = i
        return smallestIndex

    def FindPossibleAngle(self,segmImage,bbox,maxAngle):
        # bbox = bbox[0]
        x_Middle = 0
        y_Middle = 0
        if len(bbox) != 0:
            points = [[int(bbox[i, 0]), int(bbox[i, 1])] for i in range(8)]
            x_Middle = (points[1][0] + points[2][0]) // 2
            y_Middle = points[1][1]#(points[1][1] + points[5][1]) // 2
            self.lastNX.append(x_Middle)
            self.lastNY.append(y_Middle)
            if len(self.lastNX) > self.lastN:
                self.lastNX = self.lastNX[1:]
                self.lastNY = self.lastNY[1:]
            alpha = self.alpha if len(self.lastNX) > 1 else 1
            self.exponentialMovingAverageX = alpha * x_Middle + (1 - alpha) * self.exponentialMovingAverageX
            self.exponentialMovingAverageY = alpha * y_Middle + (1 - alpha) * self.exponentialMovingAverageY

        self.imageHeight = segmImage.height
        self.imageWidth = segmImage.width

        if self.counter >= 30:
            xMin, xMax, yMin, yMax = -1, -1, -1, -1
            if len(bbox) != 0:
                points = [[int(bbox[i, 0]), int(bbox[i, 1])] for i in range(8)]

                x_Middle = (points[1][0] + points[2][0]) // 2
                y_Middle = points[1][1]#(points[1][1] + points[5][1]) // 2

                for i in range(len(points)):
                    if points[i][0] > xMax or xMax == -1:
                        xMax = points[i][0]
                    if points[i][1] > yMax or yMax == -1:
                        yMax = points[i][1]
                    if points[i][0]  < xMin or xMin == -1:
                        xMin = points[i][0]
                    if points[i][1] < yMin or yMin == -1:
                        yMin = points[i][1]
            else:
                if len(self.lastNX) >= 2:
                    x_Middle = 2 * self.lastNX[-1] - self.lastNX[-2]  # simple extrapolation
                    y_Middle = 2 * self.lastNY[-1] - self.lastNY[-2]  # simple extrapolation

                    self.exponentialMovingAverageX = self.alpha * x_Middle + (1 - self.alpha) * self.exponentialMovingAverageX
                    self.exponentialMovingAverageY = self.alpha * y_Middle + (1 - self.alpha) * self.exponentialMovingAverageY

                    self.lastNX.append(x_Middle)
                    self.lastNY.append(y_Middle)
                    if len(self.lastNX) > self.lastN:
                        self.lastNX = self.lastNX[1:]
                        self.lastNY = self.lastNY[1:]
                    x_Middle = self.exponentialMovingAverageX
                    y_Middle = self.exponentialMovingAverageY
            y_Middle += self.size_h
            drivableIndexes = self.parse_segm(segmImage=segmImage,obj=[xMin,xMax,yMin,yMax])

            closestRectIndex = self.FindClosestRect(x_Middle, y_Middle)

            coords = self.BresenhamLine(self.imageWidth // 2, self.imageHeight - 1, self.CoordRectangles[closestRectIndex][1], self.CoordRectangles[closestRectIndex][0])
            coords = self.BresenhamLineSample(coords,8)
            possible = True
            for i in range(len(coords)):
                closestRectIndex = self.FindClosestRect(coords[i][0], coords[i][1])
                if drivableIndexes[closestRectIndex] == 0:
                    possible = False
                    print('False')
                else:
                    print('True')
            if possible:
                print('It is possible')
                return maxAngle, drivableIndexes
            else:
                print('It is not possible')
                closestRectIndex = self.FindClosestRect(x_Middle, y_Middle)
                line = closestRectIndex//10 #TODO if the number of rectangles changes
                if line == 9:
                    return 0, drivableIndexes
                print('Line:',line,closestRectIndex)
                mostDrivable = 0
                mostDrivableIndex = 0
                for j in range(10):
                    closestRectIndex = line*10+j
                    coords = self.BresenhamLine(self.imageWidth // 2, self.imageHeight - 1,self.CoordRectangles[closestRectIndex][1],self.CoordRectangles[closestRectIndex][0])
                    coords = self.BresenhamLineSample(coords, 8)


                    current = 0
                    for i in range(len(coords)):
                        closestRectIndex = self.FindClosestRect(coords[i][0], coords[i][1])
                        if drivableIndexes[closestRectIndex] == 1:
                            current += 1
                    if current > mostDrivable:
                        mostDrivable = current
                        mostDrivableIndex = line*10+j
                print(mostDrivableIndex, self.CoordRectangles[mostDrivableIndex][1],x_Middle)

                percentage = self.GetPercentage(self.imageWidth//2,self.CoordRectangles[mostDrivableIndex][1],x_Middle)
                # Trick to see if the drivable x coordinate and extrapoled X coordinate are on the same side of the image
                if (self.CoordRectangles[mostDrivableIndex][1] - self.imageWidth//2) * (x_Middle - self.imageWidth//2) < 0:
                    percentage = percentage*-1
                return maxAngle*percentage, drivableIndexes
        else:
            self.counter += 1
            return maxAngle, []
        return maxAngle, drivableIndexes



    def FindPossibleAnglePrev(self, segmImage, bbox, maxAngle):
        self.imageHeight = segmImage.height
        self.imageWidth = segmImage.width
        bestBadPixels = 1000000
        XBestBadPixels = 0
        bestPercentage = 0

        self.arrNBadPixels = []


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

            prevDiffX = self.lastpixelXCar - (self.imageWidth//2)
            if self.lastMaxAngle != 0:
                currentDiffX = maxAngle/float(self.lastMaxAngle) * prevDiffX
                currentPredictedX = int((self.imageWidth//2) + currentDiffX)
            else:
                currentPredictedX = self.lastpixelXCar

            middleX = segmImage.width//2
            if middleX >= currentPredictedX:
                XCoordsToCheck = np.arange(currentPredictedX,middleX+1,1)
            else:
                XCoordsToCheck = np.arange(currentPredictedX,middleX-1,-1)

            XCoordsToCheck = self.BresenhamLineSample(XCoordsToCheck,20) #optimisation
            for xCoord in XCoordsToCheck:
                coords = self.BresenhamLine(self.imageWidth//2,self.imageHeight-1,xCoord,self.lastpixelYCar)
                badPixels = 0
                for coord in coords:
                    if self.IsThePointInsideElipse(coord[0],coord[1]) and coord[1] < int(segmImage.height) and coord[0] < int(segmImage.width)\
                            and coord[1] >= 0 and coord[0] >= 0:
                        if array[coord[1]][coord[0]][2] != 7 and array[coord[1]][coord[0]][2] != 6:
                            badPixels += 1

                # if badPixels == 0:
                #     res = []
                #     for coord in coords:
                #         if self.IsThePointInsideElipse(coord[0], coord[1]):
                #             res.append([coord[0],coord[1]])
                #     percentage = self.GetPercentage(middleX,xCoord,currentPredictedX)
                #     return percentage*maxAngle, res

                if bestBadPixels > badPixels:
                    bestBadPixels = badPixels
                    XBestBadPixels = xCoord
                    bestPercentage = self.GetPercentage(middleX,xCoord,currentPredictedX)
                self.arrNBadPixels.append([badPixels,xCoord,self.GetPercentage(middleX,xCoord,currentPredictedX)])

            # check other side
            if middleX >= currentPredictedX:
                XCoordsToCheck = np.arange(middleX, self.imageWidth,1)
            else:
                XCoordsToCheck = np.arange(middleX,0,-1)

            XCoordsToCheck = self.BresenhamLineSample(XCoordsToCheck, 20)  # optimisation
            for xCoord in XCoordsToCheck:
                coords = self.BresenhamLine(self.imageWidth//2,self.imageHeight-1,xCoord,self.lastpixelYCar)
                badPixels = 0
                for coord in coords:
                    if self.IsThePointInsideElipse(coord[0],coord[1]) and coord[1] < int(segmImage.height) and coord[0] < int(segmImage.width)\
                            and coord[1] >= 0 and coord[0] >= 0:
                        if array[coord[1]][coord[0]][2] != 7 and array[coord[1]][coord[0]][2] != 6:
                            badPixels += 1
                if bestBadPixels > badPixels:
                    bestBadPixels = badPixels
                    XBestBadPixels = xCoord
                    bestPercentage = self.GetPercentage(middleX,xCoord,currentPredictedX,True)
                self.arrNBadPixels.append([badPixels,xCoord,self.GetPercentage(middleX,xCoord,currentPredictedX,True)])

                # if badPixels == 0:
                #     res = []
                #     for coord in coords:
                #         if self.IsThePointInsideElipse(coord[0], coord[1]):
                #             res.append([coord[0],coord[1]])
                #     percentage = self.GetPercentage(middleX,xCoord,currentPredictedX,True)
                #
                #     return percentage*maxAngle, res

            bestPercentage, XBestBadPixels = self.AngleBasedOnPreviousAngle(maxAngle)
            res = []
            coords = self.BresenhamLine(self.imageWidth // 2, self.imageHeight - 1, XBestBadPixels, self.lastpixelYCar)
            for coord in coords:
                if self.IsThePointInsideElipse(coord[0], coord[1]):
                    res.append([coord[0], coord[1]])

            self.prevAngle = bestPercentage * maxAngle
            return bestPercentage * maxAngle, res

        else:
            self.prevAngle = maxAngle
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