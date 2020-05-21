import math

class PurePursuitAlgorithm:
    def __init__(self, lookAheadDistance):
        self.lookAheadDistance = lookAheadDistance
        self.pathCoords = []

    def updatePath(self):
        if len(self.pathCoords) > 300:
            self.pathCoords = self.pathCoords[1:]

    def AddPathPoint(self, x, y):
        self.updatePath()
        self.pathCoords.append([x,y])

    def EuclidianDistance(self,x1,x2,y1,y2):
        return math.sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))

    def GetNextPoint(self, myCarX, myCarY):
        x, y = None, None
        lastSeenCarX = 0 if len(self.pathCoords) == 0 else self.pathCoords[-1][0]
        lastSeenCarY = 0 if len(self.pathCoords) == 0 else self.pathCoords[-1][1]

        currentDist = 10000000
        #distFromFollowingCar = 10000000
        for coordinate in self.pathCoords:
            dist = self.EuclidianDistance(myCarX,coordinate[0],myCarY,coordinate[1])
            distFollowing = self.EuclidianDistance(lastSeenCarX, coordinate[0],lastSeenCarY, coordinate[1])
            distanceBetweenCars = self.EuclidianDistance(lastSeenCarX,myCarX,lastSeenCarY,myCarY)
            if distFollowing < distanceBetweenCars:
                if (currentDist > self.lookAheadDistance and dist < currentDist):
                    x = coordinate[0]
                    y = coordinate[1]
                    currentDist = dist
                elif (dist < self.lookAheadDistance and (dist>currentDist or currentDist > self.lookAheadDistance)): #and distFollowing < distFromFollowingCar):
                    x = coordinate[0]
                    y = coordinate[1]
                    currentDist = dist
                    #distFromFollowingCar = distFollowing

        print(x,y,myCarX,myCarY,lastSeenCarX, lastSeenCarY)

        return x, y

