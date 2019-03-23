import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

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
        plt.title('Call duratins', size=titleSize)
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

        # ecdf = ECDF(weightsSurvived)
        # plt.plot(ecdf.x, ecdf.y, color='g')
        # plt.title('Sparrows that survived', size=titleSize)
        # plt.ylabel('Cumulative Distribution Function', size=labelSize)
        # plt.xlabel('Weights', size=labelSize)
        # # plt.savefig('./Report/images/diedHist.png', bbox_inches='tight')
        # plt.show()
        #
        # ecdf = ECDF(weightsDied)
        # plt.plot(ecdf.x, ecdf.y, color='firebrick')
        # plt.title('Sparrows that perished', size=titleSize)
        # plt.ylabel('Cumulative Distribution Function', size=labelSize)
        # plt.xlabel('Weights', size=labelSize)
        # # plt.savefig('./Report/images/diedDist.png', bbox_inches='tight')
        # plt.show()
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

analysis = Input_analysis()
analysis.ReadData()
analysis.CalculateParameters()
analysis.ShowHistograms()