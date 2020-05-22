import pickle
import os
import math
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

class AnalyseResults:
    def __init__(self,dirChasing):
        self.dirChasing = dirChasing

    def loadPositionHistory(self, fileName):
        return pickle.load(open(fileName, "rb"))

    def EuclidianDistance(self,x1,x2,y1,y2,z1,z2):
        return math.sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2))

    def LoadResults(self):
        file = 'res/results.txt'
        with open(file,'r') as f:
            lines = [line.rstrip() for line in f]
        return lines

    def FinishedPercentage(self, historyChased, historyChasing):
        lastPosChasing = historyChasing[-1]

        nOfPositionsDriven = 0
        tmp = 0
        for i in range(1,len(historyChasing)):
            m = len(historyChasing) - 1
            d = self.EuclidianDistance(lastPosChasing[0], historyChasing[m-i][0], lastPosChasing[1], historyChasing[m-i][1],
                                   lastPosChasing[2], historyChasing[m-i][2])
            if d > 2:
                break
            else:
                tmp +=1
        nOfPositionsDriven = len(historyChased) - tmp
        print(tmp)

        # find shortest position from the last path to the path
        shortestDist = 1000000000
        shortestIndex = 0
        for i in range(nOfPositionsDriven-1,-1,-1):
            dist = self.EuclidianDistance(lastPosChasing[0],historyChased[i][0],lastPosChasing[1],historyChased[i][1],lastPosChasing[2],historyChased[i][2])
            if dist < shortestDist:
                shortestDist = dist
                shortestIndex = i
            else:
                break
            # if dist > 2*shortestDist:
            #     break
        # shortestIndex = nOfPositionsDriven

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

def Analyse(dirChasing):
    dirChasing = dirChasing
    dirChased = 'drives'
    analyse = AnalyseResults(dirChasing)

    # chasedFiles = os.listdir(dirChased)
    # chasedFiles = ['ride11.p', 'ride12.p', 'ride13.p', 'ride14.p', 'ride15.p', 'ride16.p', 'ride17.p', 'ride18.p','ride19.p', 'ride20.p']
    chasedFiles = ['ride1.p'] #['ride1.p','ride2.p','ride3.p','ride4.p','ride5.p','ride6.p','ride7.p','ride8.p','ride9.p','ride10.p']
    # chasedFiles = ['ride1.p', 'ride2.p', 'ride3.p', 'ride4.p', 'ride5.p', 'ride6.p', 'ride7.p', 'ride8.p', 'ride9.p',
    #               'ride10.p',
    #                'ride11.p', 'ride12.p', 'ride13.p', 'ride14.p', 'ride15.p', 'ride16.p', 'ride17.p', 'ride18.p',
    #                'ride19.p', 'ride20.p']
    finished = 0
    percentages = []
    maes = [];
    rmses = [];
    crashes = []

    for file in chasedFiles:
        historyChased = analyse.loadPositionHistory(os.path.join(dirChased, file))
        historyChasing = analyse.loadPositionHistory(os.path.join(dirChasing, file))
        percentage = analyse.FinishedPercentage(historyChased, historyChasing)
        if percentage >= 0.94:
            finished += 1
            mae, rmse, crash = analyse.FindMAE(file)
            # print(mae, rmse, crash)
            maes.append(mae)
            rmses.append(rmse)
            crashes.append(crash)

        percentages.append(percentage)
        # print(file,':',percentage)
    print('Number of finished drives:', finished)
    print('Average percentage of finished drives:', np.mean(percentages))
    # print('Average number of crashes:',np.mean(crashes))
    # print('Average number MAE:', np.mean(maes))
    # print('Average number RMSE:',np.mean(rmses))

    return np.mean(percentages)



def PlotTrajectory():
    #img = plt.imread("carla_view_h.png")
    fig, ax = plt.subplots()
    dirChased = 'drives'
    dirChasing = 'chasingTrajectory'
    chasedFiles = ['ride1.p']
    analyse = AnalyseResults(dirChased)
    speeds = []
    for file in chasedFiles:
        historyChased = analyse.loadPositionHistory(os.path.join(dirChased, file))
        historyChasing = analyse.loadPositionHistory(os.path.join(dirChasing, file))

    historyChasing = np.array(historyChasing)
    historyChased = np.array(historyChased)
    print(len(historyChasing),len(historyChased))
    plt.rc('axes', labelsize=26)

    plt.plot(historyChasing[:,1],historyChasing[:,0],color='#0065BD',linewidth=4,alpha=0.7) # #0065BD
    plt.plot(historyChased[:,1],historyChased[:,0],color='black',linewidth=3,alpha=0.7,linestyle='--',dashes=(2, 1))
    # plt.scatter(X, speeds, color=colors, s=100)

    plt.ylabel('X [m]')
    plt.xlabel('Y [m]')
    # plt.yticks(fontsize=14)
    # plt.xticks([-0.3, 0, 1, 1.3], ['', 'easy drives', 'difficult drives', ''], fontsize=18)
    plt.gca().set_aspect("equal")
    plt.savefig("trajectory.pdf", bbox_inches='tight')
    # plt.show(img)



def main():
    PlotTrajectory()
    Analyse('chasingTrajectory')
    exit()




if __name__ == '__main__':
    main()
