import pickle
import matplotlib.pyplot as plt
import numpy as np

#This class is used for evaluating and processing the results of the simulations
class Evaluation:
    def __init__(self):
        self.results = []

    def ProcessResults(self,n_of_blocked_calls, n_of_dropped_calls, n_of_calls, n_of_channels_reverved):
        self.results.append([n_of_blocked_calls,n_of_dropped_calls,n_of_calls,n_of_channels_reverved])
        pickle.dump(self.results, open("results.p", "wb"))

    def Evaluate(self):
        titleSize = 20
        labelSize = 16

        self.results = pickle.load(open("results.p", "rb"))
        y_d_0 = []
        x_d_0 = []
        y_d_1 = []
        x_d_1 = []
        y_b_0 = []
        x_b_0 = []
        y_b_1 = []
        x_b_1 = []

        for item in self.results:
            if item[3] == 1:
                y_d_1.append(item[1])
                y_b_1.append(item[0])

                x_d_1.append(1)
                x_b_1.append(1)
            else:
                y_d_0.append(item[1])
                y_b_0.append(item[0])

                x_d_0.append(0)
                x_b_0.append(0)




        plt.scatter(x_d_1, y_d_1, c='blue')
        plt.scatter(x_b_1, y_b_1, c='red')

        plt.scatter(x_d_0, y_d_0, c='blue',label='Dropped calls')
        plt.scatter(x_b_0, y_b_0, c='red',label='Blocked calls')
        plt.title('Dropped/Blocked calls based on reserved channels', size=titleSize)
        plt.ylabel('Number of calls out of 10 000', size=labelSize)
        plt.xlabel('Number of reserved channels for handover', size=labelSize)
        plt.legend()
        plt.show()

        ax1 = plt.subplot(211)
        plt.hist(y_d_1, color='blue',label='Dropped calls')
        plt.hist(y_b_1, color='red',label='Blocked calls')
        plt.title('Dropped/Blocked calls with reserved channel for handover', size=titleSize)
        plt.xlabel('Number of calls out of 10 000', size=labelSize)
        plt.ylabel('Number of occurrences', size=labelSize)
        plt.legend()
        #plt.show()

        plt.subplot(212,sharex=ax1)
        plt.hist(y_d_0, color='blue',label='Dropped calls')
        plt.hist(y_b_0, color='red',label='Blocked calls')
        plt.title('Dropped/Blocked calls with no channel reservation', size=titleSize)
        plt.xlabel('Number of calls out of 10 000', size=labelSize)
        plt.ylabel('Number of occurrences', size=labelSize)
        plt.legend()
        plt.show()

        print('Average number of dropped calls (1 reserved channel):', np.mean(y_d_1))
        print('Average number of blocked calls (1 reserved channel):', np.mean(y_b_1))
        print('Average number of dropped calls (0 reserved channel):', np.mean(y_d_0))
        print('Average number of blocked calls (0 reserved channel):', np.mean(y_b_0))