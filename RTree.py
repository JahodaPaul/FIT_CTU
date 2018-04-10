import random
from copy import deepcopy

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

    def ChangeValue(self,index,value,min):
        if min:
            self.MinValues[index] = value
        else:
            self.MaxValues[index] = value

    def CalculateBoundingBox(self,node,dealingWithBoundingBoxes):
        if dealingWithBoundingBoxes:
            for item in node.children:
                if item != None:
                    for counter, dimension in enumerate(item.value.MinValues):
                        if self.MinValues[counter] == None or self.MinValues[counter] > dimension:
                            self.MinValues[counter] = dimension
                    for counter, dimension in enumerate(item.value.MaxValues):
                        if self.MaxValues[counter] == None or self.MaxValues[counter] < dimension:
                            self.MaxValues[counter] = dimension
        else:
            for item in node.children:
                if item != None:
                    for counter, dimension in enumerate(item.value.coordinates):
                        if self.MinValues[counter] == None or self.MinValues[counter] > dimension:
                            self.MinValues[counter] = dimension
                    for counter, dimension in enumerate(item.value.coordinates):
                        if self.MaxValues[counter] == None or self.MaxValues[counter] < dimension:
                            self.MaxValues[counter] = dimension
        pass



class Node:
    def __init__(self,numberOfChildren, parent):
        self.value = None
        self.children = [None for i in range(numberOfChildren)]
        self.parent = parent
        self.nOfChildren = 0

class RTree:
    def __init__(self,numberOfChildrenInNode,numberOfDimensions, splittingType):
        self.numberOfChildrenInNode = numberOfChildrenInNode
        self.numberOfDimensions = numberOfDimensions
        self.root = Node(self.numberOfChildrenInNode, None)
        self.minimumNumberOfChildrenInNode = 1 if numberOfChildrenInNode == 3 else int(numberOfChildrenInNode/2)
        self.splittingType = splittingType

    def Insert(self,value):
        tmp = self.root
        while True:
            if tmp.nOfChildren == 0:
                if tmp.parent != None:
                    self.PropagateUpwards(tmp.parent, value)
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

    def SearchCloseKDist(self):
        pass

    def FindOutToWhichBoundingBoxPointBelongs(self,point,fatherNode):
        # Does he belong to any of the bounding box?
        #TODO # If so, which of them has smallest distance from center of bounding box

        #TODO # If not, which bounding box would be expanded least

        #TODO, FOR NOW I AM JUST RETURNING alway 0
        return 0

        # return index
        pass

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
                node.value.CalculateBoundingBox(node, node.children[node.nOfChildren].value.IsItBoundingBox())
                node.nOfChildren += 1


                while node.parent != None:
                    node.parent.value.CalculateBoundingBox(node.parent,True)
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