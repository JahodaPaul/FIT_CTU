# Written by Pavel Jahoda
from Generator import Generator
from Evaluation import Evaluation
from Object import Object
import time
import matplotlib.pyplot as plt
import numpy as np

class Simualation():
    def __init__(self):
        # system clock, which will be updated outside of events
        self.clock = 0

        self.n_of_dropped_calls = 0
        self.n_of_blocked_calls = 0
        # desired number of calls in the simulation
        self.n_of_calls = 10000
        self.n_of_channels_reverved = 0

        # we will update this number until we reach our
        # desired number of initiation calls
        self.n_of_calls_created = 0

        self.generator = Generator()

        # we will have a list-like data structure that will
        # keep events sorted by the simulated time
        # [time of next event in seconds, type of event,
        # Object(speed, call duration etc)]
        # type of event -> 0: i
        self.eventList = []

        # how many free channels each station currently has
        self.free_channels_by_station = [10 for i in range(20)]

        self.history_dropped = []
        self.history_blocked = []
        self.history_x = []
        self.n_of_calls_finished = 0
        self.deviation_hist_dropped = []
        self.deviation_hist_blocked = []
        self.history_dev = []

        self.warmup_period = True
        self.warmup_period_n_of_calls = 0

    def PrintCurrentState(self):
        print('---------------------------------------------------------------------------')
        for item in self.eventList:
            print(item)
        print()
        print(self.free_channels_by_station)
        print('Current clock:',self.clock)

    # parameter - number of channels reserved for handovers
    # when other channels are not available
    def Simulate(self, n_of_channels_reverved):
        self.n_of_channels_reverved = n_of_channels_reverved

        # generate first initiation
        self.eventList.append(self.generator.Generate_next_initiation())
        self.n_of_calls_created += 1

        while len(self.eventList) != 0:
            # update the system clock time to the time of next event
            self.clock = self.eventList[0][0]

            # if self.n_of_calls_finished % 1000 == 0:
            #     print('Number of calls finished',self.n_of_calls_finished)
            # self.PrintCurrentState()
            #time.sleep(0.5)

            # depending on the type of the object in the event list,
            # call function initiation, termination or handover
            if self.eventList[0][1] == 0: # if the event is new call, generate another call
                self.Initiation(self.eventList[0][2])
            elif self.eventList[0][1] == 1: # handover
                self.Handover(self.eventList[0][2])
            else: # termination
                self.Termination(self.eventList[0][2])

            # after we make the call we update the event list and remove the first item
            self.eventList = self.eventList[1:]
            self.eventList.sort()

        return self.n_of_blocked_calls, self.n_of_dropped_calls, self.n_of_calls, self.n_of_channels_reverved

    def CalculateHowLongTillNextEvent(self, obj):
        if obj.direction == 'RIGHT':
            kmTillNextEvent = (obj.position // 2)*2 + 2 - obj.position
        else:
            kmTillNextEvent = abs((obj.position // 2)*2 - obj.position)
            if kmTillNextEvent == 0:
                kmTillNextEvent = 2

        return kmTillNextEvent/obj.speed * 3600 # in seconds

    def UpdateHistory(self):
        self.n_of_calls_finished += 1
        self.history_x.append(self.n_of_calls_finished)
        self.history_dropped.append(self.n_of_dropped_calls/float(self.n_of_calls_finished)*100)
        self.history_blocked.append(self.n_of_blocked_calls/float(self.n_of_calls_finished)*100)

        if self.warmup_period:
            self.history_dev.append(self.n_of_calls_finished)
            if(len(self.history_dropped) < 10) or \
                            self.n_of_blocked_calls == 0 or self.n_of_dropped_calls == 0:
                self.deviation_hist_dropped.append(1)
                self.deviation_hist_blocked.append(1)
            else:
                mean_dropped = np.mean(self.history_dropped)
                mean_blocked = np.mean(self.history_blocked)

                sum_dev_dropped = 0
                sum_dev_blocked = 0
                for i in range(1,11):
                    sum_dev_dropped += pow((mean_dropped-self.history_dropped[-1*i]),2)
                    sum_dev_blocked += pow((mean_blocked-self.history_blocked[-1*i]),2)

                self.deviation_hist_dropped.append(sum_dev_dropped/10.0)
                self.deviation_hist_blocked.append(sum_dev_blocked/10.0)
                if self.deviation_hist_dropped[-1] < 0.1 and self.deviation_hist_blocked[-1] < 0.1:
                    self.warmup_period = False
                    self.n_of_calls_created -= self.n_of_calls_finished
                    self.warmup_period_n_of_calls = self.n_of_calls_finished
                    self.n_of_dropped_calls = 0
                    self.n_of_blocked_calls = 0
                    self.n_of_calls_finished = 0
                    self.history_x = []
                    self.history_dropped = []
                    self.history_blocked = []


    def Initiation(self, obj):
        blocked = False
        if self.free_channels_by_station[obj.station] - self.n_of_channels_reverved > 0:
            self.free_channels_by_station[obj.station] -= 1
        else:
            self.n_of_blocked_calls += 1
            blocked = True
            self.UpdateHistory()

        if not blocked:
            # Car leaving the highway, no other handover can occur
            if (obj.station == 0 and obj.direction == 'LEFT') or \
                    (obj.station == 19 and obj.direction == 'RIGHT'):
                item = self.generator.Generate_next_termination(obj)
                item[0] = item[0] + self.clock
                self.eventList.append(item)
            else: # handover
                item = self.generator.Generate_next_handover(obj)
                item[0] = item[0] + self.clock
                self.eventList.append(item)

        if self.n_of_calls_created != self.n_of_calls:
            # generate next initiation
            item = self.generator.Generate_next_initiation()
            item[0] = item[0] + self.clock
            self.eventList.append(item)
            self.n_of_calls_created += 1

    def Termination(self, obj):
        if obj.direction == 'RIGHT':
            self.free_channels_by_station[obj.station - 1] += 1
        else:
            self.free_channels_by_station[obj.station + 1] += 1
        self.UpdateHistory()

    def Handover(self, obj):
        # in the parameter station we use the new station that driver drives towards

        # first let's free the channel used of the previous station
        if obj.direction == 'RIGHT':
            self.free_channels_by_station[obj.station - 1] += 1
        else:
            self.free_channels_by_station[obj.station + 1] += 1

        if self.free_channels_by_station[obj.station] > 0:
            self.free_channels_by_station[obj.station] -= 1
            # Car leaving the highway, no other handover can occur
            if (obj.station == 0 and obj.direction == 'LEFT') or \
                    (obj.station == 19 and obj.direction == 'RIGHT'):
                item = self.generator.Generate_next_termination(obj)
                # print('ITEM',item[0])
                item[0] = item[0] + self.clock
                self.eventList.append(item)
            else:  # handover
                item = self.generator.Generate_next_handover(obj)
                # print('ITEM',item[0])
                item[0] = item[0] + self.clock
                self.eventList.append(item)
        else:
            self.n_of_dropped_calls += 1
            self.UpdateHistory()

    def Plot(self):
        titleSize = 22
        labelSize = 18

        plt.title('Percentage of dropped/blocked calls in time', size=titleSize)
        plt.xlabel('Number of calls finished', size=labelSize)
        plt.ylabel('Percentage', size=labelSize)
        plt.plot(self.history_x,self.history_blocked,'red',label='Blocked calls')
        plt.plot(self.history_x,self.history_dropped,'blue',label='Dropped calls')
        plt.legend()
        plt.show()

        plt.title('Volatility of the percentage of dropped/blocked calls in time', size=titleSize)
        plt.xlabel('Number of calls finished', size=labelSize)
        plt.ylabel('Volatility', size=labelSize)
        plt.plot(self.history_dev,self.deviation_hist_blocked,'red',label='Blocked calls')
        plt.plot(self.history_dev,self.deviation_hist_dropped,'blue',label='Dropped calls')
        plt.legend()
        plt.show()


def main():
    n_of_iteratins = 100 # adjust number of iterations of the simulation
    evaluation = Evaluation()

    print('start')

    # We will run each simulation multiple times and evaluate the results at the end of the program run
    for i in range(n_of_iteratins):
        simulation = Simualation()
        x, y, z, l = simulation.Simulate(0)
        evaluation.ProcessResults(x,y,z,l)
        print('Simulation',i,'finished')
        # print(simulation.Simulate(1))
        # print(simulation.warmup_period_n_of_calls)
        # simulation.Plot()
        # evaluation.Evaluate(simulation.Simulate(0))

    for i in range(n_of_iteratins):
        simulation = Simualation()
        x,y,z,l = simulation.Simulate(1)
        evaluation.ProcessResults(x,y,z,l)
        print('Simulation', i, 'finished')

    evaluation.Evaluate()



if __name__ == '__main__':
    main()
