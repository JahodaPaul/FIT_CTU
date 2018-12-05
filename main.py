%matplotlib inline
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from scipy import stats

dataPath = 'data.csv'

def importData(dataPath):
    data = pd.read_csv(dataPath, sep=';').replace({'perished' : 0, 'survived' : 1}).reset_index()
    return np.array(data.Weight), np.array(data.Status)

def SolutionTask4(mi=25.793220423035702,sig=1.9175809969270372, EV=0.5932203389830508):
#     np.random.seed(42)
    W_gen = []
    S_gen = []
    
    for i in range(0,100): #59 is sample size, so 100 values might feel a bit off
        W_gen.append(np.random.normal(loc=mi,scale=np.sqrt(sig)))
        S_gen.append(np.random.choice(a=[0, 1], p=[1-EV,EV]))
    
    bins = np.linspace(21, 32, 25)
    plt.grid(axis='y', alpha=0.75)
    plt.xlabel('Weight')
    plt.ylabel('No. of birbs')

    plt.hist(W_gen, bins, color='red', alpha=0.5, label='generated')
    plt.hist(weights, bins, color='blue', alpha=0.5, label='given')
    plt.legend(loc='upper right')
    plt.show()

    plt.xlabel('Survival')
    plt.ylabel('No. of birbs')

    plt.hist(S_gen, color='red', alpha=0.5, label='generated')
    plt.hist(survive, color='blue', alpha=0.5, label='given')
    plt.legend(loc='upper center')
    plt.show()

    
def SolutionTask1(weights, survive):
    print('Weight of birbs')
    print('Expected value:',np.mean(weights)) # assuming it's an uniform distribution
    print('Variance:',np.var(weights))
    print('Median:',np.median(weights))
    print('==================================')
    print('Survival of birbs')
    print('Expected value:', np.mean(survive))  # assuming it's an uniform distribution
    print('Variance:', np.var(survive))
    print('Median:', np.median(survive))

weights, survive = importData('data.csv')
SolutionTask1(weights=weights,survive=survive)
SolutionTask4()