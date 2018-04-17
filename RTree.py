import random
import math
from copy import deepcopy
from RTreeComponents import *

class RTree:
    def __init__(self,numberOfChildrenInNode,numberOfDimensions, splittingType):
        self.returnList = []
        self.numberOfChildrenInNode = numberOfChildrenInNode
        self.numberOfDimensions = numberOfDimensions
        self.root = Node(self.numberOfChildrenInNode, None)
        self.minimumNumberOfChildrenInNode = 1 if numberOfChildrenInNode == 3 else int(numberOfChildrenInNode/2)
        self.splittingType = splittingType

    def Insert(self,value):
        tmp = self.root
        while True:
            if tmp.nOfChildren == 0 or (tmp.nOfChildren != 0 and not tmp.children[0].value.IsItBoundingBox()):
                if tmp.nOfChildren != 0:
                    self.PropagateUpwards(tmp, value)
                else:
                    #root - create first item
                    temporaryNode = Node(self.numberOfChildrenInNode,None)
                    temporaryNode.value = value
                    self.root.children[0] = temporaryNode
                    self.root.children[0].parent = self.root
                    self.root.nOfChildren += 1
                    self.root.value = BoundingBox(self.numberOfDimensions)
                    self.root.value.CalculateBoundingBox(self.root,False)
                return
            temporaryIndex = self.FindOutToWhichBoundingBoxPointBelongs(value,tmp)
            tmp = tmp.children[temporaryIndex]
        pass

    def Delete(self):
        pass

    def SearchForPoint(self):
        pass

    def SearchKClosest(self):
        pass

    def EuclidianDistTwoPoints(self,p1,p2):
        sum = 0
        for i in range(len(p1.coordinates)):
            sum += ( (p1.coordinates[i] - p2.coordinates[i]) * (p1.coordinates[i] - p2.coordinates[i]) )
        return round(math.sqrt(sum),10)

    def PreorderKDist(self,node,value, distance):
        if node == None:
            return

        if not node.value.IsItBoundingBox():
            if self.EuclidianDistTwoPoints(node.value,value) <= distance:
                self.returnList.append(deepcopy(node.value))
            return

        for child in node.children:
            if child != None and (not child.value.IsItBoundingBox() or
                                      (child.value.IsItBoundingBox() and
                                           distance >= self.EuclidianDistTwoPoints(child.value.ClosestPointFromToBoundingBoxToPoint(value,child.value), value) )):
                self.PreorderKDist(child,value,distance)

    # takes as a parameters RTreeComponent Value
    def SearchCloseKDist(self,value,distance):
        self.returnList = []
        self.PreorderKDist(self.root, value,distance)
        return self.returnList

    def FindOutToWhichBoundingBoxPointBelongs(self,point,fatherNode):
        # Does he belong to any of the bounding box?
        # If so, which of them has smallest distance from center of bounding box
        # If not, which bounding box would be expanded least
        listOfBoundingBoxVolumeExpansions = []

        for i in range(fatherNode.nOfChildren):
            temporaryBoundingBox = deepcopy(fatherNode.children[i].value)
            temporaryBoundingBox.AddPointOrBBToBoundingBox(point.IsItBoundingBox(),point)
            listOfBoundingBoxVolumeExpansions.append(temporaryBoundingBox.CalculateVolumeOfBoundingBox() - fatherNode.children[i].value.CalculateVolumeOfBoundingBox() )
        index = 0
        temporaryMin = 0
        howManyZeros = 0
        for counter, value in enumerate(listOfBoundingBoxVolumeExpansions):
            if counter == 0:
                temporaryMin = value
            elif value <= temporaryMin:
                temporaryMin = value
                index = counter
            if value == 0:
                howManyZeros += 1

        if howManyZeros <= 1:
            return index
        else:
            index = 0
            temporaryMin = -1
            # finding closest to center of boundingBox
            for counter, value in enumerate(listOfBoundingBoxVolumeExpansions):
                if value == 0:
                    center = deepcopy(point) #just to inicialize
                    for i in range(len(fatherNode.children[counter].value.MaxValues)):
                        center.coordinates[i] = (fatherNode.children[counter].value.MaxValues[i] + fatherNode.children[counter].value.MinValues[i])/float(2)
                    val = self.EuclidianDistTwoPoints(center,point)
                    if temporaryMin == -1 or val < temporaryMin:
                        temporaryMin = val
                        index = counter

            return index

    def SplitOverflowingNodes(self, oldArray, newValue, boundingBoxesOrNot, type):
        # Take old array of points/bounding boxes and new point/bounding box and find out which combination
        # that satisfies requirements has least amount of overlap
        first = None
        second = None

        if type == "random":
            nOfChildrenInFirst = (oldArray.nOfChildren + 1) // 2
            nOfChildrenInSecond = (oldArray.nOfChildren + 1) - nOfChildrenInFirst
            first = Node(self.numberOfChildrenInNode, oldArray.parent)
            first.nOfChildren = nOfChildrenInFirst

            second = Node(self.numberOfChildrenInNode, None)
            second.nOfChildren = nOfChildrenInSecond

            if random.randint(1,2) == 1:
                for i in range(nOfChildrenInFirst):
                    first.children[i] = oldArray.children[i]
                for i in range(nOfChildrenInFirst, nOfChildrenInFirst + nOfChildrenInSecond):
                    if i == nOfChildrenInSecond + nOfChildrenInFirst - 1:
                        second.children[i-nOfChildrenInFirst] = newValue
                    else:
                        second.children[i-nOfChildrenInFirst] = oldArray.children[i]
            else:
                for i in range(nOfChildrenInSecond,nOfChildrenInSecond+nOfChildrenInFirst):
                    if i == nOfChildrenInSecond + nOfChildrenInFirst - 1:
                        first.children[i-nOfChildrenInSecond] = newValue
                    else:
                        first.children[i-nOfChildrenInSecond] = oldArray.children[i]
                for i in range(nOfChildrenInSecond):
                    second.children[i] = oldArray.children[i]

        elif type == "heuristic": #QuadraticSplit which minimizes overlap
            pass
        elif type == "bruteforce": #find a split that creates areas with smallest sum of volume
            pass

        for child in first.children:
            if child != None:
                child.parent = first

        for child in second.children:
            if child != None:
                child.parent = second

        first.value = BoundingBox(self.numberOfDimensions)
        first.value.CalculateBoundingBox(first, boundingBoxesOrNot)
        second.value = BoundingBox(self.numberOfDimensions)
        second.value.CalculateBoundingBox(second, boundingBoxesOrNot)

        return first, second
        pass


    def PropagateUpwards(self, node, value):
        dealingWithBoundingBoxes = False
        tmpValue = Node(self.numberOfChildrenInNode,None)
        tmpValue.value = deepcopy(value)
        value = tmpValue

        while True:
            if node.nOfChildren < self.numberOfChildrenInNode:
                node.children[node.nOfChildren] = value
                node.children[node.nOfChildren].parent = node
                node.value.AddPointOrBBToBoundingBox(node.children[node.nOfChildren].value.IsItBoundingBox(), node.children[node.nOfChildren].value)
                node.nOfChildren += 1


                while node.parent != None:
                    value = node
                    node.parent.value.AddPointOrBBToBoundingBox(value.value.IsItBoundingBox(),value.value)
                    node = node.parent
                return
            else:
                existingNode, newNode = self.SplitOverflowingNodes(node, value, dealingWithBoundingBoxes, self.splittingType)
                temporaryID = id(node)
                node = existingNode #prepise se ten odkaz
                value = newNode
                if node.parent != None:
                    for counter,child in enumerate(node.parent.children):
                        if temporaryID == id(child):
                            node.parent.children[counter] = existingNode
                    node = node.parent
                    node.value.CalculateBoundingBox(node,True)

                else:
                    #what to do when you need to split root - create new root
                    self.root = Node(self.numberOfChildrenInNode, None)
                    self.root.value = BoundingBox(self.numberOfDimensions)
                    newNode.parent = self.root
                    existingNode.parent = self.root
                    self.root.children[0] = existingNode
                    self.root.children[1] = newNode
                    self.root.value.CalculateBoundingBox(self.root,True)
                    self.root.nOfChildren = 2
                    return
                dealingWithBoundingBoxes = True