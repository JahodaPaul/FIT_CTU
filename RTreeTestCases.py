from RTree import *
from RTreeTestClass import Test
import random
import time
import matplotlib.pyplot as plt

test = Test()

# myTree6 = RTree(2,2,'heuristic')
# myTree6.root.children[0] = Node(2,myTree6.root)
# myTree6.root.children[0].children[0] = Node(2,myTree6.root.children[0])
# myTree6.root.children[0].children[0].children[0] = Node(2,myTree6.root.children[0].children[0])
# myTree6.root.children[1] = Node(2,myTree6.root)
# if not test.IsBalanced(myTree6.root,myTree6.numberOfChildrenInNode):
#     print('NOT BALANCED, WHICH IS OK - THIS IS FOR TESTING TESTING SYSTEM')
# else:
#     print('TESTING SYSTEM NOT WORKING PROPERLY')
#
# myTree = RTree(4,2,'heuristic')
#
# myTree.Insert(Value([1,1],0))
# myTree.Insert(Value([2,2],1))
#
# test.TestingSection(myTree, myTree.numberOfChildrenInNode,False,[ #point, distance, nOfPointsCloseCorrect
#     [Value([0,0],-1),2,1 ],
#     [Value([0,0],-1),10,2 ],
#     [Value([0,1],-1),1,1 ]
# ])
#
# myTree4 = RTree(4,2,'heuristic')
#
# for i in range(13):
#     myTree4.Insert(Value([i, i], i))
#
# test.TestingSection(myTree4,myTree4.numberOfChildrenInNode)
#
# myTree2 = RTree(4,2,'heuristic')
#
# for i in range(14):
#     if i == 5:
#         myTree2.Insert(Value([i, i], i))
#     else:
#         myTree2.Insert(Value([i, i], i))
#
# test.TestingSection(myTree2,myTree2.numberOfChildrenInNode)
#
# myTree3 = RTree(2,3,'heuristic')
# for i in range(1500):
#     myTree3.Insert(Value([i,i,i],i))
#
# test.TestingSection(myTree3,myTree3.numberOfChildrenInNode)
#
# myTree5 = RTree(4,2,'heuristic')
#
# for i in range(100):
#     myTree5.Insert(Value([100-i,100-i],i))
#
# test.TestingSection(myTree5,myTree5.numberOfChildrenInNode)
#
# myTree7 = RTree(4,2,'heuristic')
# myTree7.Insert(Value([0, 0], 0))
# myTree7.Insert(Value([10, 10], 0))
# myTree7.Insert(Value([3, 2], 0))
# myTree7.Insert(Value([7, 1], 0))
# myTree7.Insert(Value([1, 7], 0))
# myTree7.Insert(Value([3, 8], 0))
# myTree7.Insert(Value([4, 4], 0))
#
#
# test.TestingSection(myTree7,myTree7.numberOfChildrenInNode,False,[#point, distance, nOfPointsCloseCorrect
#     [Value([0,0],-1),0,1],
#     [Value([5,5],-1),2,1],
#     [Value([5,5],-1),100,7],
#     [Value([12,-2],-1),1000,7],
#     [Value([-1,-1],-1),1,0]
# ])
#
# #
# myTree8 = RTree(4,2,'heuristic')
# myTree8.Insert(Value([1000.3, 0.7], 0))
# myTree8.Insert(Value([22, 22.1], 0))
# myTree8.Insert(Value([21.8, 22.3], 0))
# myTree8.Insert(Value([22.2, 20], 0))
#
# myTree8.Insert(Value([1.2, 1000.4], 0))
# myTree8.Insert(Value([7.6, 7], 0))
# myTree8.Insert(Value([6.5, 6.9], 0))
# myTree8.Insert(Value([7.1, 7.2], 0))
#
# myTree8.Insert(Value([0, 0], 0))
# myTree8.Insert(Value([7.3, 6.8], 0))
# myTree8.Insert(Value([7, 7], 0))
# myTree8.Insert(Value([7.0, 7.2], 0))
#
# myTree8.Insert(Value([1000, 1000.3], 0))
# myTree8.Insert(Value([100, 100], 0))
# myTree8.Insert(Value([99, 100], 0))
# myTree8.Insert(Value([98, 100], 0))
#
#
# test.TestingSection(myTree8,myTree8.numberOfChildrenInNode,False,[#point, distance, nOfPointsCloseCorrect
#     [Value([0,0],-1),10000,16],
#     [Value([7,7],-1),2,6],
#     [Value([100,100],-1),2,3],
#     [Value([1000,-2],-1),100,1],
#     [Value([1000,0.7],-1),0,0],
#     [Value([7,7],-1),0.25,3],
#     [Value([7,7],-1),0,1],
#     [Value([7,7],-1),0.2,2]
# ])


def TestAllThreeAndPrintTime(nOfChildren,nOfDimensions,valuesFrom,valuesTo,nOfValues,nOfQueries,queryDist):
    print('Children:',nOfChildren,'Number of dimensions:',nOfDimensions,'Number of values:',nOfValues,'Number of queries:',nOfQueries)
    myTreeRandom = RTree(nOfChildren,nOfDimensions,'random')
    myTreeBruteForce = RTree(nOfChildren, nOfDimensions, 'bruteforce')
    myTreeHeuristic = RTree(nOfChildren, nOfDimensions, 'heuristic')

    listOfValues = []
    for i in range(nOfValues):
        temporaryVal = Value([random.randint(valuesFrom, valuesTo) for j in range(nOfDimensions)], 0)
        listOfValues.append(temporaryVal)
        test.Insert(temporaryVal)
    queries = []
    for i in range(nOfQueries):
        queries.append([Value([random.randint(valuesFrom-10, valuesTo+10) for j in range(nOfDimensions)], 0), random.randint(0, queryDist), 0])

    before = time.time()
    for val in listOfValues:
        myTreeRandom.Insert(val)
    after = time.time()
    print('Insert random:',after-before)
    randIn = after - before

    before = time.time()
    for val in listOfValues:
        myTreeBruteForce.Insert(val)
    after = time.time()
    print('Insert bruteforce:', after - before)
    brutIn = after - before

    before = time.time()
    for val in listOfValues:
        myTreeHeuristic.Insert(val)
    after = time.time()
    print('Insert heuristic:', after - before)
    heuIn = after-before

    before = time.time()
    test.TestingSection(myTreeRandom,myTreeRandom.numberOfChildrenInNode,True,queries)
    after = time.time()
    print('Queries random:', after - before)
    randQ = after - before

    before = time.time()
    test.TestingSection(myTreeBruteForce,myTreeBruteForce.numberOfChildrenInNode,True,queries)
    after = time.time()
    print('Queries bruteforce:', after - before)
    brutQ = after - before

    before = time.time()
    test.TestingSection(myTreeHeuristic,myTreeHeuristic.numberOfChildrenInNode,True,queries)
    after = time.time()
    heuQ = after-before
    print('Queries heuristic:', after - before)
    print()
    return randIn,brutIn,heuIn,randQ,brutQ,heuQ

randInL, brutInL, heuInL, randQL, brutQL, heuQL  = [],[],[],[],[],[]
xAxis = []
for i in range(1,6):
    randIn, brutIn, heuIn, randQ, brutQ, heuQ = TestAllThreeAndPrintTime(8,3,0,100,2000,10000,10*i)
    randInL.append(randIn)
    brutInL.append(brutIn)
    heuInL.append(heuIn)
    randQL.append(randQ)
    brutQL.append(brutQ)
    heuQL.append(heuQ)
    xAxis.append(i*10)

randomLine = plt.plot(xAxis,randQL,label = 'random',color='purple')
bruteforceLine = plt.plot(xAxis,brutQL,label = 'brute force',color='red')
heuristicLine = plt.plot(xAxis,heuQL,label = 'heuristic',color='green')

plt.xlabel('Distance')
plt.ylabel('Seconds')
plt.title('What role does distance play')
plt.legend(loc='best')
# plt.legend([randomLine, bruteforceLine,heuristicLine], ['Random', 'brute force','heuristic'])
plt.show()