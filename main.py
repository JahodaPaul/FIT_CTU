import numpy as np
#import matplotlib.pyplot as plt

dataPath = 'data.csv'

def importData():
    with open('data.csv','r') as f:
        data = [line.rstrip('\n') for line in f]
        survive = []
        weights = []
        for cnt, item in enumerate(data):
            data[cnt] = item.split(';')
            if cnt != 0:
                weights.append(float(data[cnt][0]))
                data[cnt][1] = data[cnt][1][1:-1] # the column contains words 'perished' and 'survived', for easier use
                                                  # I will convert 'perished' -> 0 and 'survived' -> 1
                if data[cnt][1] == 'survived':
                    survive.append(1)
                else:
                    survive.append(0)

        weights = np.array(weights)
        survive = np.array(survive)
        return weights, survive

def SolutionTask1(weights, survive):
    print('Expected value:',np.mean(weights)) # assuming it's an uniform distribution
    print('Variance:',np.var(weights))
    print('Median:',np.median(weights))

    print('Expected value:', np.mean(survive))  # assuming it's an uniform distribution
    print('Variance:', np.var(survive))
    print('Median:', np.median(survive))

weights, survive = importData()
SolutionTask1(weights=weights,survive=survive)
