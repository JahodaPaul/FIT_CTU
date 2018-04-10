from RTree import *


def Preorder(node, nOfChildren):
    if node == None:
        return
    print('----------------------,',node.nOfChildren)
    node.value.PrintForTesting()
    for i in range(nOfChildren):
        Preorder(node.children[i],nOfChildren)



myTree = RTree(4,2,'random')
print('TEST1')

myTree.Insert(Value([1,1],0))
myTree.Insert(Value([2,2],1))

Preorder(myTree.root,4)

myTree2 = RTree(4,2,'random')
print('TEST2')

for i in range(40):
    if i == 5:
        myTree2.Insert(Value([i, i], i))
    else:
        myTree2.Insert(Value([i, i], i))

Preorder(myTree2.root,4)