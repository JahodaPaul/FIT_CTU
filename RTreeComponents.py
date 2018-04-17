class Value:
    def __init__(self, coordinates,index):
        self.coordinates = coordinates #TODO hardcopy these
        self.index = index
    def PrintForTesting(self):
        print(self.coordinates,self.index)

    def IsItBoundingBox(self):
        return False

class BoundingBox:
    def __init__(self, numberOfDimensions):
        self.MinValues = [None for i in range(numberOfDimensions)]
        self.MaxValues = [None for i in range(numberOfDimensions)]

    def PrintForTesting(self):
        print(self.MinValues, self.MaxValues)

    def IsItBoundingBox(self):
        return True

    def CalculateBoundingBox(self,node,dealingWithBoundingBoxes):
        temporaryValue = len(self.MaxValues)
        node.value = BoundingBox(temporaryValue)
        if dealingWithBoundingBoxes:
            for item in node.children:
                if item != None:
                    node.value.AddPointOrBBToBoundingBox(item.value.IsItBoundingBox(), item.value)
        else:
            for item in node.children:
                if item != None:
                    node.value.AddPointOrBBToBoundingBox(item.value.IsItBoundingBox(), item.value)

    def AddPointOrBBToBoundingBox(self,dealingWithBoundingBoxes, pointOrBB):
        if dealingWithBoundingBoxes:
            for counter, dimension in enumerate(pointOrBB.MinValues):
                if self.MinValues[counter] == None or self.MinValues[counter] > dimension:
                    self.MinValues[counter] = dimension
            for counter, dimension in enumerate(pointOrBB.MaxValues):
                if self.MaxValues[counter] == None or self.MaxValues[counter] < dimension:
                    self.MaxValues[counter] = dimension
        else:
            for counter, dimension in enumerate(pointOrBB.coordinates):
                if self.MinValues[counter] == None or self.MinValues[counter] > dimension:
                    self.MinValues[counter] = dimension
            for counter, dimension in enumerate(pointOrBB.coordinates):
                if self.MaxValues[counter] == None or self.MaxValues[counter] < dimension:
                    self.MaxValues[counter] = dimension

    def CalculateVolumeOfBoundingBox(self):
        volume = 0
        for i in range(len(self.MaxValues)):
            if i == 0:
                volume = self.MaxValues[i] - self.MinValues[i]
            else:
                volume *= (self.MaxValues[i] - self.MinValues[i])
        return volume

    def PointInsideOfBoundingBox(self,point,boundingBox):
        for counter, maxValue in enumerate(boundingBox.MaxValues):
            if maxValue < point.coordinates[counter]:
                return False

        for counter, minValue in enumerate(boundingBox.MinValues):
            if minValue > point.coordinates[counter]:
                return False

        return True

    #In how many dimensions is the point outside of the boundingBox
    def PointDimOutside(self, point, boundingbox):
        counter = 0
        list = []
        for cnt, dim in enumerate(point.coordinates):
            if dim < boundingbox.MinValues[cnt]:
                list.append(1)
                counter+=1
            elif dim > boundingbox.MaxValues[cnt]:
                list.append(2)
                counter+=1
            else:
                list.append(0)

        return list,counter

    # Find closest point in the boundingBox to the point
    def ClosestPointFromToBoundingBoxToPoint(self,point,boundingBox):
        list, howManyDimensionsOutsideOfBB = self.PointDimOutside(point,boundingBox)

        if howManyDimensionsOutsideOfBB == 0: #if point is inside of boundingBox, return the point itself
            return point

        myPoint = Value([0 for i in range(len(point.coordinates))],0)

        # Lets say you have point 0,0,0 and boundingBox 1,1,1 : 3,3,3... since in all dimensions the point is
        # outside of bounding box, the closest point would be the vertex of the bounding box (min,max values),
        # which in this case is 1,1,1.. but lets say you move the bounding box by 2 on X dimension from
        # 1,1,1 : 3,3,3 to -1,1,1 : 1,3,3. Now, the point is in the boundingBox dimensions X, so the closest
        # point from the bounding Box will be same as the point on X dimension -> 0,1,1 is the
        # closest point from the bounding box to 0,0,0.
        for cnt, item in enumerate(list):
            if item == 0:
                myPoint.coordinates[cnt] = point.coordinates[cnt]
            elif item == 1:
                myPoint.coordinates[cnt] = boundingBox.MinValues[cnt]
            else:
                myPoint.coordinates[cnt] = boundingBox.MaxValues[cnt]

        return myPoint



class Node:
    def __init__(self,numberOfChildren, parent):
        self.value = None
        self.children = [None for i in range(numberOfChildren)]
        self.parent = parent
        self.nOfChildren = 0