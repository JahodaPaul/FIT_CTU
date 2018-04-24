import random
import math
from copy import deepcopy
from operator import itemgetter
from RTreeComponents import *

class RTree:
    def __init__(self,numberOfChildrenInNode,numberOfDimensions, splittingType):
        self.returnList = []
        self.numberOfChildrenInNode = numberOfChildrenInNode
        self.numberOfDimensions = numberOfDimensions
        self.root = Node(self.numberOfChildrenInNode, None)
        self.minimumNumberOfChildrenInNode = int(numberOfChildrenInNode/2)
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

    def PreOrderClosest(self,node,value):
        if node == None:
            return
        if node.value.IsItBoundingBox() and node.nOfChildren and not node.children[0].value.IsItBoundingBox():
            # if true, search for closest value
            minDist = 0
            minIndex = 0
            for i in range(node.nOfChildren):
                temporaryDistance = self.EuclidianDistTwoPoints(node.children[i].value,value)
                if i == 0:
                    minDist = temporaryDistance
                elif temporaryDistance < minDist:
                    minDist = temporaryDistance
                    minIndex = i
            return node.children[minIndex].value, minDist
        #if you are not close to leaf, call FindOutToWhichBoundingBoxPointBelongs method which is used when inserting values
        index = self.FindOutToWhichBoundingBoxPointBelongs(value,node)
        return self.PreOrderClosest(node.children[index],value)


    def SearchKClosest(self,value): # right now its searching just for the closest
        return self.PreOrderClosest(self.root,value)

    def EuclidianDistTwoPoints(self,p1,p2):
        sum = 0
        for i in range(len(p1.coordinates)):
            sum += ( (p1.coordinates[i] - p2.coordinates[i]) * (p1.coordinates[i] - p2.coordinates[i]) )
        return round(math.sqrt(sum),10)

    def EuclidianDistTwoBoundingBoxes(self,p1,p2): # dist from center of one boundingBox to center of the other boundingBox
        tmpCoordinates1 = [0 for i in range(self.numberOfDimensions)]
        tmpCoordinates2 = [0 for i in range(self.numberOfDimensions)]
        for i in range(self.numberOfDimensions):
            tmpCoordinates1[i] = (p1.MaxValues[i]+p1.MinValues[i])/float(2)
            tmpCoordinates2[i] = (p2.MaxValues[i]+p2.MinValues[i])/float(2)
        tmpP1 = Value(tmpCoordinates1,0)
        tmpP2 = Value(tmpCoordinates2,0)
        sum = 0
        for i in range(len(tmpP1.coordinates)):
            sum += ( (tmpP1.coordinates[i] - tmpP2.coordinates[i]) * (tmpP1.coordinates[i] - tmpP2.coordinates[i]) )
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

    def nextPermutation(self,previousPermutation, nOfNumbers, maxIndex):
        if previousPermutation == 0:
            return [i for i in range(nOfNumbers)]

        counter = nOfNumbers - 1
        while True:
            if previousPermutation[counter] < (maxIndex - (nOfNumbers - 1 - counter)):
                previousPermutation[counter] += 1
                for i in range(counter + 1, nOfNumbers):
                    previousPermutation[i] = previousPermutation[i - 1] + 1
                    # counter = nOfNumbers - 1
                # print(previousPermutation) // uncoment these two lines to print every permutation
                return previousPermutation
            else:
                if counter != 0:
                    counter -= 1
                else:
                    return 0

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

        elif type == "heuristic": #variation of quadratic split
            # ---PHASE 1---: linear pick seeds
            minSum = 0
            minIndex = 0
            maxSum = 0
            maxIndex = 0

            for i in range(len(oldArray.children)+1):
                if i != len(oldArray.children):
                    tmpMin = oldArray.children[i].value.CalculateSumOfCoordinates()
                    tmpMax = oldArray.children[i].value.CalculateSumOfCoordinates(False)
                else:
                    tmpMin = newValue.value.CalculateSumOfCoordinates()
                    tmpMax = newValue.value.CalculateSumOfCoordinates(False)

                if i ==0:
                    minSum = tmpMin
                    maxSum = tmpMax
                else:
                    if tmpMin < minSum:
                        minSum = tmpMin
                        minIndex = i
                    if tmpMax > maxSum:
                        maxSum = tmpMax
                        maxIndex = i

            if maxIndex == minIndex:
                assigned = False
                for i in range(len(oldArray.children) + 1):
                    if i != len(oldArray.children):
                        tmpMax = oldArray.children[i].value.CalculateSumOfCoordinates(False)
                    else:
                        tmpMax = newValue.value.CalculateSumOfCoordinates(False)

                    if not assigned and i != minIndex:
                        maxSum = tmpMax
                        maxIndex = i
                        assigned = True
                    elif i != minIndex:
                        if tmpMax > maxSum:
                            maxSum = tmpMax
                            maxIndex = i

            first = Node(self.numberOfChildrenInNode, oldArray.parent)
            second = Node(self.numberOfChildrenInNode, None)
            #assign smallest to first and biggest to second

            if minIndex == len(oldArray.children):
                first.children[0] = newValue
            else:
                first.children[0] = oldArray.children[minIndex]

            if maxIndex == len(oldArray.children):
                second.children[0] = newValue
            else:
                second.children[0] = oldArray.children[maxIndex]
            first.nOfChildren = 1
            second.nOfChildren = 1

            # ---PHASE 2---: new distribute

            taken = [0 for i in range(len(oldArray.children)+1)]
            taken[minIndex] = 1
            taken[maxIndex] = 1

            # sort rest of (len(oldArray.children)+1) items by how close they are to first
            HowFarFromFirstList = []
            for i in range(len(oldArray.children)+1):
                if not taken[i]:
                    if i != len(oldArray.children):
                        if first.children[0].value.IsItBoundingBox():
                            HowFarFromFirstList.append((i, self.EuclidianDistTwoBoundingBoxes(first.children[0].value, oldArray.children[i].value)))
                        else:
                            HowFarFromFirstList.append((i,self.EuclidianDistTwoPoints(first.children[0].value,oldArray.children[i].value)))
                    else:
                        if first.children[0].value.IsItBoundingBox():
                            HowFarFromFirstList.append((i, self.EuclidianDistTwoBoundingBoxes(first.children[0].value, newValue.value)))
                        else:
                            HowFarFromFirstList.append((i, self.EuclidianDistTwoPoints(first.children[0].value,newValue.value)))

            HowFarFromFirstList = sorted(HowFarFromFirstList,key=itemgetter(1))
            # print(HowFarFromFirstList)

            for i in range(self.minimumNumberOfChildrenInNode-1):
                taken[HowFarFromFirstList[i][0]] = 1
                if HowFarFromFirstList[i][0] == len(oldArray.children):
                    first.children[first.nOfChildren] = newValue
                    first.nOfChildren += 1
                else:
                    first.children[first.nOfChildren] = oldArray.children[HowFarFromFirstList[i][0]]
                    first.nOfChildren += 1

            # sort rest of (len(oldArray.children)+1) items by how close they are to second
            HowFarFromSecondList = []
            for i in range(len(oldArray.children)+1):
                if not taken[i]:
                    if i != len(oldArray.children):
                        if second.children[0].value.IsItBoundingBox():
                            HowFarFromSecondList.append((i, self.EuclidianDistTwoBoundingBoxes(second.children[0].value, oldArray.children[i].value)))
                        else:
                            HowFarFromSecondList.append((i,self.EuclidianDistTwoPoints(second.children[0].value,oldArray.children[i].value)))
                    else:
                        if second.children[0].value.IsItBoundingBox():
                            HowFarFromSecondList.append((i, self.EuclidianDistTwoBoundingBoxes(second.children[0].value, newValue.value)))
                        else:
                            HowFarFromSecondList.append((i, self.EuclidianDistTwoPoints(second.children[0].value,newValue.value)))

            HowFarFromSecondList = sorted(HowFarFromSecondList,key=itemgetter(1))
            # print(HowFarFromSecondList)

            for i in range(self.minimumNumberOfChildrenInNode-1):
                taken[HowFarFromSecondList[i][0]] = 1
                if HowFarFromSecondList[i][0] == len(oldArray.children):
                    second.children[second.nOfChildren] = newValue
                    second.nOfChildren += 1
                else:
                    second.children[second.nOfChildren] = oldArray.children[HowFarFromSecondList[i][0]]
                    second.nOfChildren += 1

            #rest of the not taken nodes assign to whoever is closer - first or second
            for i in range(len(oldArray.children) + 1):
                if not taken[i]:
                    firstDist = 0
                    secondDist = 0

                    for item in HowFarFromFirstList:
                        if item[0] == i:
                            firstDist = item[1]

                    for item in HowFarFromSecondList:
                        if item[0] == i:
                            secondDist = item[1]

                    if firstDist < secondDist or second.nOfChildren == self.numberOfChildrenInNode:
                        if i == len(oldArray.children):
                            first.children[first.nOfChildren] = newValue
                            first.nOfChildren += 1
                        else:
                            first.children[first.nOfChildren] = oldArray.children[i]
                            first.nOfChildren += 1
                    else:
                        if i == len(oldArray.children):
                            second.children[second.nOfChildren] = newValue
                            second.nOfChildren += 1
                        else:
                            second.children[second.nOfChildren] = oldArray.children[i]
                            second.nOfChildren += 1

        elif type == "bruteforce": #find a split that creates areas with smallest sum of volume
            minNOfChildren = self.minimumNumberOfChildrenInNode
            maxNOfChildren = (oldArray.nOfChildren + 1) - minNOfChildren

            minVolume = -1
            minPermutation = None
            nOfChildrenInFirstFinal = 0
            nOfChildrenInSecondFinal = 0

            for i in range(minNOfChildren,maxNOfChildren+1):
                nOfChildrenInFirst = i
                nOfChildrenInSecond = (oldArray.nOfChildren+1) - nOfChildrenInFirst
                #every permutation of i children in N children

                previousPermutation = 0;
                permutation = 0
                nOfNumbers = nOfChildrenInFirst
                maxNumber = self.numberOfChildrenInNode+1

                while True:
                    previousPermutation = deepcopy(permutation)
                    permutation = self.nextPermutation(previousPermutation, nOfNumbers, maxNumber - 1)
                    if permutation == 0:  # zero means end
                        break
                    binaryPermutation = [0 for i in range(maxNumber)]
                    for index in permutation:
                        binaryPermutation[index] = 1

                    volume1 = 0
                    volume2 = 0
                    first = Node(self.numberOfChildrenInNode, None)
                    second = Node(self.numberOfChildrenInNode, None)

                    indexFirst = 0
                    indexSecond = 0
                    for counter, item in enumerate(binaryPermutation):  # TODO
                        if item == 1:
                            if counter == nOfChildrenInFirst + nOfChildrenInSecond - 1:
                                first.children[indexFirst] = newValue
                            else:
                                first.children[indexFirst] = oldArray.children[counter]
                            indexFirst += 1
                        elif item == 0:
                            if counter == nOfChildrenInFirst + nOfChildrenInSecond - 1:
                                second.children[indexSecond] = newValue
                            else:
                                second.children[indexSecond] = oldArray.children[counter]
                            indexSecond += 1

                    # calculate volume of both bounding boxes
                    first.value = BoundingBox(self.numberOfDimensions)
                    first.value.CalculateBoundingBox(first, boundingBoxesOrNot)
                    second.value = BoundingBox(self.numberOfDimensions)
                    second.value.CalculateBoundingBox(second, boundingBoxesOrNot)
                    volume1 = first.value.CalculateVolumeOfBoundingBox()
                    volume2 = second.value.CalculateVolumeOfBoundingBox()
                    if volume1 + volume2 < minVolume or minVolume == -1:
                        minVolume = volume1 + volume2
                        minPermutation = deepcopy(binaryPermutation)
                        nOfChildrenInFirstFinal = nOfChildrenInFirst
                        nOfChildrenInSecondFinal = nOfChildrenInSecond


            #create final first and second node
            first = Node(self.numberOfChildrenInNode, oldArray.parent)
            nOfChildrenInFirst = nOfChildrenInFirstFinal
            first.nOfChildren = nOfChildrenInFirst
            second = Node(self.numberOfChildrenInNode, None)
            nOfChildrenInSecond = nOfChildrenInSecondFinal
            second.nOfChildren = nOfChildrenInSecond

            indexFirst = 0;indexSecond = 0
            for counter, item in enumerate(minPermutation): #TODO
                if item == 1:
                    if counter == nOfChildrenInFirst+nOfChildrenInSecond-1:
                        first.children[indexFirst] = newValue
                    else:
                        first.children[indexFirst] = oldArray.children[counter]
                    indexFirst += 1
                elif item == 0:
                    if counter == nOfChildrenInFirst+nOfChildrenInSecond-1:
                        second.children[indexSecond] = newValue
                    else:
                        second.children[indexSecond] = oldArray.children[counter]
                    indexSecond += 1

        for i in range(first.nOfChildren):
            first.children[i].parent = first

        for i in range(second.nOfChildren):
            second.children[i].parent = second

        first.value = BoundingBox(self.numberOfDimensions)
        first.value.CalculateBoundingBox(first, boundingBoxesOrNot)
        second.value = BoundingBox(self.numberOfDimensions)
        second.value.CalculateBoundingBox(second, boundingBoxesOrNot)

        return first, second


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
                    # node.parent.value.CalculateBoundingBox(node.parent,True)
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