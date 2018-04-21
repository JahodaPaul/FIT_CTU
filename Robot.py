from Config import *

class Robot:
    def __init__(self):
        self.visitedBoxCorner = False
        self.direction = UNINICIALIZED
        self.previousCoordinates = None
        self.previouslyPickedUpTreasure = False

        #for inside of box
        self.goUp = True
        self.moveRight = True
        self.moveRightX = -2

    def RightDirection(self,x,y,goalX,goalY):
        if goalY > y:
            return UP
        if goalY < y:
            return DOWN
        if goalX > x:
            return RIGHT
        if goalX < x:
            return LEFT

    def TurnLeftOrRight(self,goalDirection):#
        if self.direction == goalDirection:
            print('PROOOBLEM')
            return SERVER_TURN_RIGHT
        if self.direction - goalDirection == 1 or self.direction == UP and goalDirection == LEFT:
            self.direction = (self.direction - 1) % 4
            return SERVER_TURN_LEFT
        else:
            self.direction = (self.direction + 1) % 4
            return SERVER_TURN_RIGHT

    def VisitCorner(self,x,y):
        correctDirection = self.RightDirection(x,y,-2,2)
        if correctDirection == self.direction:
            return SERVER_MOVE
        else:
            return self.TurnLeftOrRight(correctDirection)

    def SetAnotherGoalCoordinatesInBox(self,x,y):
        if y != 2 and self.goUp:
            return x,2
        if y == 2 and self.goUp and x == self.moveRightX:
            return x+1,y
        if y == 2 and self.goUp and x > self.moveRightX:
            self.moveRightX = x
            self.goUp = False
            return x, -2
        if y != -2 and not self.goUp:
            return x, -2
        if y == -2 and not self.goUp and x == self.moveRightX:
            return x+1,y
        if y == 2 and not self.goUp and x > self.moveRightX:
            self.moveRightX = x
            self.goUp = True
            return x, 2

    def LookForTreasure(self,x,y):
        if not self.previouslyPickedUpTreasure:
            self.previouslyPickedUpTreasure = True
            return SERVER_PICK_UP
        else:
            goalX,goalY = self.SetAnotherGoalCoordinatesInBox(x,y)
            correctDirection = self.RightDirection(x, y, goalX, goalY)
            if correctDirection == self.direction:
                self.previouslyPickedUpTreasure = False
                return SERVER_MOVE
            else:
                return self.TurnLeftOrRight(correctDirection)


    def Move(self,x,y):
        if x == 999999 and y == 999999:
            return SERVER_MOVE
        if self.previousCoordinates == None:
            self.previousCoordinates = (x,y)
            return SERVER_MOVE
        if self.direction == UNINICIALIZED:
            if x > self.previousCoordinates[0]:
                self.direction = RIGHT
            elif x < self.previousCoordinates[0]:
                self.direction = LEFT
            elif y < self.previousCoordinates[1]:
                self.direction = DOWN
            elif y > self.previousCoordinates[1]:
                self.direction = UP

        if not self.visitedBoxCorner and (x,y) == (-2,2):
            self.visitedBoxCorner = True

        if self.visitedBoxCorner:
            return self.LookForTreasure(x,y)
        return self.VisitCorner(x,y)
