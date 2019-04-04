import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from scipy.stats import chisquare
from numpy.random import normal
import math
from scipy.stats import normaltest
from scipy.special import erf


class Input_analysis:
    def __init__(self):
        self.arrival_times = []
        self.arrivel_times_processed = []
        self.base_stations = []
        self.call_durations = []
        self.velocities = []

    def ReadData(self):
        lines = [line.rstrip() for line in open('data.csv','r')]
        for line in lines[1:]:
            items = line.split(',')
            self.arrival_times.append(float(items[1]))
            self.base_stations.append(int(items[2]))
            self.call_durations.append(float(items[3]))
            self.velocities.append(float(items[4]))

        for i in range(1,len(self.arrival_times)):
            self.arrivel_times_processed.append(self.arrival_times[i]-self.arrival_times[i-1])

    def Scatter(self):
        plt.scatter(self.call_durations,self.velocities)
        plt.title('Calls',size=22)
        plt.xlabel('Call duration (seconds)',size=18)
        plt.ylabel('Car Velocity (km/h)',size=18)
        plt.show()

    def CheckData(self):
        error_values = False
        for item in self.base_stations:
            if item < 1 or item > 20:
                error_values = True
        if error_values:
            print('There are bad values in the dataset')
        else:
            print('No error values')

    def ShowHistograms(self):
        titleSize = 24
        labelSize = 20

        plt.hist(self.arrivel_times_processed, color='skyblue')
        plt.title('Inter-arrival times', size=titleSize)
        plt.xlabel('seconds', size=labelSize)
        plt.ylabel('No. of occurrences', size=labelSize)
        # plt.savefig('./Report/images/survivedHist.png', bbox_inches='tight')
        plt.show()

        plt.hist(self.base_stations, color='skyblue')
        plt.title('Base station', size=titleSize)
        plt.xlabel('Station number', size=labelSize)
        plt.ylabel('No. of occurrences', size=labelSize)
        # plt.savefig('./Report/images/survivedDist.png', bbox_inches='tight')
        plt.show()

        plt.hist(self.call_durations, color='skyblue')
        plt.title('Call durations', size=titleSize)
        plt.xlabel('seconds', size=labelSize)
        plt.ylabel('No. of occurrences', size=labelSize)
        # plt.savefig('./Report/images/survivedHist.png', bbox_inches='tight')
        plt.show()

        plt.hist(self.velocities, color='skyblue')
        plt.title('Car velocity', size=titleSize)
        plt.xlabel('km/h', size=labelSize)
        plt.ylabel('No. of occurrences', size=labelSize)
        # plt.savefig('./Report/images/survivedDist.png', bbox_inches='tight')
        plt.show()


    def CalculateParameters(self):
        self.lambda_interarrival = len(self.arrivel_times_processed)/float(sum(self.arrivel_times_processed))
        self.lambda_callDuration = len(self.call_durations)/float(sum(self.call_durations))
        print('lambda inter-arrival times:',self.lambda_interarrival,'lambda call duration times:',self.lambda_callDuration)

        self.mean_velocities = sum(self.velocities)/float(len(self.velocities))
        self.variance_velocities = 0
        for item in self.velocities:
            self.variance_velocities += (item-self.mean_velocities)*(item-self.mean_velocities)
        self.variance_velocities = self.variance_velocities/float(len(self.velocities))
        print('mean velocities:',self.mean_velocities,'variance velocities:',self.variance_velocities)

    def HypothesisTesting(self):
        print('Velocities mean:',np.mean(np.array(self.velocities)))
        norm_vel = normal(self.mean_velocities, math.sqrt(self.variance_velocities),len(self.velocities))
        print(normaltest(self.velocities))
        print('Chi square test:',chisquare(self.velocities,norm_vel,2))

    def CalculateChiSquareTestRanges(self):
        self.rangesInterArrival = []
        self.rangesCallDuration = []
        prevInt = 0
        prevDur = 0
        print(min(self.call_durations))
        for i in range(1,100):
            x1 = math.log(-1*(i/100)+1,math.e)/self.lambda_interarrival*(-1)
            x2 = math.log(-1 * (i / 100) + 1, math.e) / self.lambda_callDuration * (-1)  + min(self.call_durations)
            self.rangesInterArrival.append((prevInt,x1))
            self.rangesCallDuration.append((prevDur,x2))
            prevInt = x1
            prevDur = x2
            # print(x1,x2)
        self.rangesInterArrival.append((prevInt,max(self.arrivel_times_processed)+1)) # bigger number than all of them..
        self.rangesCallDuration.append((prevDur,max(self.call_durations)+1))

    def CalculateFrequencies(self):
        self.interArrivalFrequencies = [0 for i in range(100)]
        self.durationFrequencies = [0 for i in range(100)]
        for i in range(100):
            for item in self.arrivel_times_processed:
                if self.rangesInterArrival[i][0] <= item and self.rangesInterArrival[i][1] > item:
                    self.interArrivalFrequencies[i] += 1

            for item in self.call_durations:
                if self.rangesCallDuration[i][0] <= item and self.rangesCallDuration[i][1] > item:
                    self.durationFrequencies[i] += 1
        print("duration call frequncies:",self.durationFrequencies)
        print("inter-arrival times frequencies",self.interArrivalFrequencies)

    def ChiSquareTest(self):
        sumInter = 0
        sumDur = 0
        for i in range(100):
            # print(sumInter,sumDur)
            sumInter += math.pow((self.interArrivalFrequencies[i]-100),2)/100
            sumDur += math.pow((self.durationFrequencies[i]-100),2)/100
        print(sumInter)
        print(sumDur)


analysis = Input_analysis()
analysis.ReadData()
analysis.CheckData()
analysis.CalculateParameters()
# analysis.HypothesisTesting()
# analysis.Scatter()
# analysis.ShowHistograms()
analysis.CalculateChiSquareTestRanges()
analysis.CalculateFrequencies()
analysis.ChiSquareTest()