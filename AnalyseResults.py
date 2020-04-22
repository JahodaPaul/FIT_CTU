import pickle
import os
import math
import numpy as np

class AnalyseResults:
    def __init__(self,dirChasing):
        self.dirChasing = dirChasing

    def loadPositionHistory(self, fileName):
        return pickle.load(open(fileName, "rb"))

    def EuclidianDistance(self,x1,x2,y1,y2,z1,z2):
        return math.sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2))

    def LoadResults(self):
        file = self.dirChasing + '/results.txt'
        with open(file,'r') as f:
            lines = [line.rstrip() for line in f]
        return lines

    def FinishedPercentage(self, historyChased, historyChasing):
        lastPosChasing = historyChasing[-1]

        # find shortest position from the last path to the path
        shortestDist = 1000000000
        shortestIndex = 0
        for i in range(len(historyChased)):
            dist = self.EuclidianDistance(lastPosChasing[0],historyChased[i][0],lastPosChasing[1],historyChased[i][1],lastPosChasing[2],historyChased[i][2])
            if dist < shortestDist:
                shortestDist = dist
                shortestIndex = i
            if dist > 2*shortestDist:
                break

        distToLastPoint = 0
        distfromLastPoint = 0

        for i in range(len(historyChased)):
            if i+1 < len(historyChased):
                if i+1 <= shortestIndex:
                    distToLastPoint += self.EuclidianDistance(historyChased[i+1][0],historyChased[i][0],historyChased[i+1][1],historyChased[i][1],historyChased[i+1][2],historyChased[i][2])
                else:
                    distfromLastPoint += self.EuclidianDistance(historyChased[i + 1][0], historyChased[i][0],
                                                              historyChased[i + 1][1], historyChased[i][1],
                                                              historyChased[i + 1][2], historyChased[i][2])
        percentage = distToLastPoint/float(distToLastPoint+distfromLastPoint)
        return percentage

    def FindMAE(self,drivename):
        results = self.LoadResults()
        for i in range(len(results)):
            tmp = results[i].split(',')
            if drivename in tmp[0]:
                return float(tmp[1]), float(tmp[2]), float(tmp[3])

def main():
    dirChasing = 'chaseOutput_Simple_SimplesDrives'
    dirChased = 'drives'
    analyse = AnalyseResults(dirChasing)

    # chasedFiles = os.listdir(dirChased)
    chasedFiles = ['ride11.p', 'ride12.p', 'ride13.p', 'ride14.p', 'ride15.p', 'ride16.p', 'ride17.p', 'ride18.p','ride19.p', 'ride20.p']
    # chasedFiles = ['ride1.p','ride2.p','ride3.p','ride4.p','ride5.p','ride6.p','ride7.p','ride8.p','ride9.p','ride10.p']
    finished = 0
    percentages = []
    maes = []; rmses = []; crashes = []

    for file in chasedFiles:
        historyChased = analyse.loadPositionHistory(os.path.join(dirChased,file))
        historyChasing = analyse.loadPositionHistory(os.path.join(dirChasing,file))
        percentage = analyse.FinishedPercentage(historyChased,historyChasing)
        if percentage >= 0.94:
            finished += 1
            mae, rmse, crash = analyse.FindMAE(file)
            print(mae, rmse, crash)
            maes.append(mae)
            rmses.append(rmse)
            crashes.append(crash)

        percentages.append(percentage)
        print(file,':',percentage)
    print('Number of finished drives:',finished)
    print('Average percentage of finished drives:',np.mean(percentages))
    print('Average number of crashes:',np.mean(crashes))
    print('Average number MAE:', np.mean(maes))
    print('Average number RMSE:',np.mean(rmses))


if __name__ == '__main__':
    main()
