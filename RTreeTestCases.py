from RTree import *
from RTreeTestClass import Test

test = Test()

myTree6 = RTree(2,2,'random')
myTree6.root.children[0] = Node(2,myTree6.root)
myTree6.root.children[0].children[0] = Node(2,myTree6.root.children[0])
myTree6.root.children[0].children[0].children[0] = Node(2,myTree6.root.children[0].children[0])
myTree6.root.children[1] = Node(2,myTree6.root)
if not test.IsBalanced(myTree6.root,myTree6.numberOfChildrenInNode):
    print('NOT BALANCED, WHICH IS OK - THIS IS FOR TESTING TESTING SYSTEM')
else:
    print('TESTING SYSTEM NOT WORKING PROPERLY')

myTree = RTree(4,2,'random')

myTree.Insert(Value([1,1],0))
myTree.Insert(Value([2,2],1))

test.TestingSection(myTree, myTree.numberOfChildrenInNode,[ #point, distance, nOfPointsCloseCorrect
    [Value([0,0],-1),2,1 ],
    [Value([0,0],-1),10,2 ],
    [Value([0,1],-1),1,1 ]
])

myTree4 = RTree(4,2,'random')

for i in range(13):
    myTree4.Insert(Value([i, i], i))

test.TestingSection(myTree4,myTree4.numberOfChildrenInNode)

myTree2 = RTree(4,2,'random')

for i in range(14):
    if i == 5:
        myTree2.Insert(Value([i, i], i))
    else:
        myTree2.Insert(Value([i, i], i))

test.TestingSection(myTree2,myTree2.numberOfChildrenInNode)

myTree3 = RTree(2,3,'random')
for i in range(10000):
    myTree3.Insert(Value([i,i,i],i))

test.TestingSection(myTree3,myTree3.numberOfChildrenInNode)

myTree5 = RTree(4,2,'random')

for i in range(100):
    myTree5.Insert(Value([100-i,100-i],i))

test.TestingSection(myTree5,myTree5.numberOfChildrenInNode)

myTree7 = RTree(4,2,'random')
myTree7.Insert(Value([0, 0], 0))
myTree7.Insert(Value([10, 10], 0))
myTree7.Insert(Value([3, 2], 0))
myTree7.Insert(Value([7, 1], 0))
myTree7.Insert(Value([1, 7], 0))
myTree7.Insert(Value([3, 8], 0))
myTree7.Insert(Value([4, 4], 0))

test.TestingSection(myTree7,myTree7.numberOfChildrenInNode,[#point, distance, nOfPointsCloseCorrect
    [Value([0,0],-1),0,1],
    [Value([5,5],-1),2,1],
    [Value([5,5],-1),100,7],
    [Value([12,-2],-1),1000,7],
    [Value([-1,-1],-1),1,0]
])


myTree8 = RTree(4,2,'random')
myTree8.Insert(Value([1000.3, 0.7], 0))
myTree8.Insert(Value([22, 22.1], 0))
myTree8.Insert(Value([21.8, 22.3], 0))
myTree8.Insert(Value([22.2, 20], 0))

myTree8.Insert(Value([1.2, 1000.4], 0))
myTree8.Insert(Value([7.6, 7], 0))
myTree8.Insert(Value([6.5, 6.9], 0))
myTree8.Insert(Value([7.1, 7.2], 0))

myTree8.Insert(Value([0, 0], 0))
myTree8.Insert(Value([7.3, 6.8], 0))
myTree8.Insert(Value([7, 7], 0))
myTree8.Insert(Value([7.0, 7.2], 0))

myTree8.Insert(Value([1000, 1000.3], 0))
myTree8.Insert(Value([100, 100], 0))
myTree8.Insert(Value([99, 100], 0))
myTree8.Insert(Value([98, 100], 0))

test.TestingSection(myTree8,myTree8.numberOfChildrenInNode,[#point, distance, nOfPointsCloseCorrect
    [Value([0,0],-1),10000,16],
    [Value([7,7],-1),2,6],
    [Value([100,100],-1),2,3],
    [Value([1000,-2],-1),100,1],
    [Value([1000,0.7],-1),0,0],
    [Value([7,7],-1),0.25,3],
    [Value([7,7],-1),0,1],
    [Value([7,7],-1),0.2,2]
])





