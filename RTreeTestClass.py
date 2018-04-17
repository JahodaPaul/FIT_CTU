from RTree import *
from RTreeComponents import *

class Test:
    def __init__(self):
        self.passed = True
        self.listOfValues = []

    def Preorder(node, nOfChildren):
        if node == None:
            return
        print('----------------------,', node.nOfChildren)
        node.value.PrintForTesting()
        for i in range(nOfChildren):
            Preorder(node.children[i], nOfChildren)

    def CheckBB(self,bb1,bb2,twoBoundingBoxes):
        passed = True
        if twoBoundingBoxes:
            for counter, val in enumerate(bb1.MinValues):
                if val > bb2.MinValues[counter]:
                    passed = False
                    return passed
            for counter, val in enumerate(bb1.MaxValues):
                if val < bb2.MaxValues[counter]:
                    passed = False
                    return passed
        else:
            for counter, val in enumerate(bb1.MinValues):
                if val > bb2.coordinates[counter] or bb1.MaxValues[counter] < bb2.coordinates[counter]:
                    passed = False
                    return passed

        return passed

    def PreorderCheckBoundingBox(self,node, nOfChildren, boundingBox):
        if node == None:
            return
        if not self.CheckBB(boundingBox.value,node.value,node.value.IsItBoundingBox()):
            boundingBox.value.PrintForTesting()
            node.value.PrintForTesting()
            print('')
            self.passed = False
        for i in range(nOfChildren):
            self.PreorderCheckBoundingBox(node.children[i], nOfChildren,node)

    def Height(self,node):
        if node == None:
            return 0
        maximum = 0

        for child in node.children:
            val = self.Height(child)
            if val > maximum:
                maximum = val
        return 1 + maximum
    def IsBalanced(self,node,nOfChildren):
        if node == None:
            return 1
        maxVal = -1
        minVal = -1

        for i in range(nOfChildren):
            if node.children[i] != None:
                val = self.Height(node.children[i])
                if minVal > val or minVal == -1:
                    minVal = val
                if maxVal < val or maxVal == -1:
                    maxVal = val
        balanced = 1
        if maxVal - minVal > 1 and minVal != -1 and maxVal != -1:
            balanced = 0
            return balanced
        for child in node.children:
            if not self.IsBalanced(child,nOfChildren):
                balanced = 0
                return balanced
        return balanced

    def Insert(self,value):
        self.listOfValues.append(value)

    def bruteForceTestKDistFromPoint(self,value, myTree,distance):
        nOfPoints = 0
        for item in self.listOfValues:
            tmp = myTree.EuclidianDistTwoPoints(item,value)
            if tmp <= distance:
                nOfPoints += 1
        return nOfPoints

    def TestingCloseKDistance(self,myTree,testCases, machineTesting): #At the moment, testing only number of points
        passed = True

        #testCases contains list of testcases, each testcase is a list of three items - point, distance, nOfPointsCloseCorrect
        for i in range(len(testCases)):
            temporaryList = myTree.SearchCloseKDist(testCases[i][0],testCases[i][1])
            if machineTesting:
                if len(temporaryList) != self.bruteForceTestKDistFromPoint(testCases[i][0],myTree,testCases[i][1]):
                    passed = False
                    print('TEST', i, 'NUMBER OF POINTS CLOSE TO POINT TEST FAILED')
            elif len(temporaryList) != testCases[i][2]:
                passed = False
                print('TEST',i,'NUMBER OF POINTS CLOSE TO POINT TEST FAILED')
        self.listOfValues = []
        return passed

    def TestingSection(self,RTree, nOfChildren, machineTesting=False, testCasesKDistClose = []):
        finalPassed = True
        self.passed = True
        self.PreorderCheckBoundingBox(RTree.root,nOfChildren,RTree.root)
        if not self.passed:
            print('TEST BOUNDING BOX FAILED')
            finalPassed = False

        self.passed = True
        self.passed = self.IsBalanced(RTree.root,nOfChildren)
        if not self.passed:
            print('TEST BALANCED FAILED')
            finalPassed = False

        self.passed = True
        self.passed = self.TestingCloseKDistance(RTree,testCasesKDistClose,machineTesting)
        if not self.passed:
            print('TEST POINTS K DISTANCE CLOSE FAILED')
            finalPassed = False

        if finalPassed:
            print('SUCCESS. TESTS PASSED')