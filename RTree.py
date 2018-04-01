class BoundingBox:
    def __init__(self, numberOfDimensions):
        self.MinValues = [None for i in range(numberOfDimensions)]
        self.MaxValues = [None for i in range(numberOfDimensions)]

    def ChangeValue(self,index,value,min):
        if min:
            self.MinValues[index] = value
        else:
            self.MaxValues[index] = value

    def FindMinMax(self,listOfValues, min):
        if len(listOfValues) == 0:
            print("No values")
            return
        resultItem = listOfValues[0]
        if min:
            for item in listOfValues:
                if item < resultItem:
                    resultItem = item
        else:
            for item in listOfValues:
                if item > resultItem:
                    resultItem = item

        return resultItem



class Node:
    def __init__(self,numberOfValuesInNode):
        self.boundingBox = BoundingBox()
        self.values = [None for i in range(numberOfValuesInNode)]
        self.children = [None for i in range(numberOfValuesInNode)]
        self.nOfValues = 0
        self.nOfChildren = 0

class RTree:
    def __init__(self,numberOfValuesInNode,numberOfDimensions):
        self.numberOfValuesInNode = numberOfValuesInNode
        self.numberOfDimensions = numberOfDimensions
        self.root = Node(self.numberOfValuesInNode)
        self.minimumNumberOfValuesInNode = 1 if numberOfValuesInNode == 3 else int(numberOfValuesInNode/2)

    def Insert(self,value):
        tmp = self.root
        while true:
            if tmp.children == 0:
                return #TODO I AM IN LEAF
            temporaryIndex = self.FindOutToWhichBoundingBoxPointBelongs(value,tmp)
            tmp = tmp.children[temporaryIndex]
        pass

    def Delete(self):
        pass

    def SearchKClosest(self):
        pass

    def SearchCloseKDist(self):
        pass

    def FindOutToWhichBoundingBoxPointBelongs(self,point,fatherNode):
        # Does he belong to any of the bounding box?
        # If so, which of them has smallest distance from center of bounding box

        # If not, which bounding box would be expanded least

        # return index
        pass