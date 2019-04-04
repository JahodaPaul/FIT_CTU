# Written by Pavel Jahoda
from Generator import Generator
from Evaluation import Evaluation
from Object import Object
import time

class Simualation():
    def __init__(self):
        # system clock, which will be updated outside of events
        self.clock = 0

        self.n_of_dropped_calls = 0
        self.n_of_blocked_calls = 0
        # desired number of calls in the simulation
        self.n_of_calls = 100
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

    def PrintCurrentState(self):
        print('---------------------------------------------------------------------------')
        for item in self.eventList:
            print(item)
        print()
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

            self.PrintCurrentState()
            time.sleep(0.5)

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

            if self.n_of_calls_created == 10000: #some desired number of calls
                break

        return self.n_of_blocked_calls, self.n_of_dropped_calls, self.n_of_calls, self.n_of_channels_reverved

    def CalculateHowLongTillNextEvent(self, obj):
        kmTillNextEvent = obj.position % 2  # position modulo 2
        kmTillNextEvent = kmTillNextEvent + 2 if kmTillNextEvent == 0 else kmTillNextEvent

        if obj.direction == 'RIGHT' and kmTillNextEvent != 2:
            kmTillNextEvent = 2 - kmTillNextEvent

        return kmTillNextEvent/obj.speed * 3600 # in seconds

    def Initiation(self, obj):
        if self.free_channels_by_station[obj.station] - self.n_of_channels_reverved > 0:
            self.free_channels_by_station[obj.station] -= 1
        else:
            self.n_of_blocked_calls += 1

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
        self.free_channels_by_station[obj.station] -= 1

    def Handover(self, obj):
        # in the parameter station we use the new station that driver drives towards

        # first let's free the channel used of the previous station
        if obj.direction == 'RIGHT':
            self.free_channels_by_station[obj.station - 1] -= 1
        else:
            self.free_channels_by_station[obj.station + 1] -= 1

        if self.free_channels_by_station[obj.station] > 0:
            self.free_channels_by_station[obj.station] += 1
            # Car leaving the highway, no other handover can occur
            if (obj.station == 0 and obj.direction == 'LEFT') or \
                    (obj.station == 19 and obj.direction == 'RIGHT'):
                item = self.generator.Generate_next_termination(obj)
                item[0] = item[0] + self.clock
                self.eventList.append(item)
            else:  # handover
                item = self.generator.Generate_next_handover(obj)
                item[0] = item[0] + self.clock
                self.eventList.append(item)
        else:
            self.n_of_dropped_calls += 1



def main():
    n_of_iteratins = 1 # adjust number of iterations of the simulation
    evaluation = Evaluation()

    print('start')

    # We will run each simulation multiple times and evaluate the results at the end of the program run
    for i in range(n_of_iteratins):
        simulation = Simualation()
        simulation.Simulate(0)
        # evaluation.Evaluate(simulation.Simulate(0))

    # for i in range(n_of_iteratins):
    #     simulation = Simualation()
    #     evaluation.Evaluate(simulation.Simulate(1))
    #
    # evaluation.Evaluate()



if __name__ == '__main__':
    main()
