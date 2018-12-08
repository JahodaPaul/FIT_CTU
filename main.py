#%matplotlib inline
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from scipy import stats
from statsmodels.distributions.empirical_distribution import ECDF

dataPath = 'data.csv'

def importData(dataPath):
    data = pd.read_csv(dataPath, sep=';').replace({'perished' : 0, 'survived' : 1}).reset_index()
    weightsSurvived = []; weightsDied = []

    for i in range(len(data)):
        if data.Status[i] == 1:
            weightsSurvived.append(data.Weight[i])
        else:
            weightsDied.append(data.Weight[i])

    return np.array(weightsSurvived), np.array(weightsDied)

def SolutionTask1(weightsSurvived, weightsDied):
    print('Weight of birds that survived')
    print('Expected value:',np.mean(weightsSurvived))
    print('Variance:',np.var(weightsSurvived))
    print('Median:',np.median(weightsSurvived))
    print('==================================')
    print('Survival of birds that perished')
    print('Expected value:', np.mean(weightsDied))
    print('Variance:', np.var(weightsDied))
    print('Median:', np.median(weightsDied))

def SolutionTask2(weightsSurvived,weightsDied):
    titleSize = 24
    labelSize = 20

    plt.hist(weightsSurvived, color='g')
    plt.title('Sparrows that survived',size=titleSize)
    plt.xlabel('Weights',size=labelSize)
    plt.ylabel('No. of sparrows',size=labelSize)
    plt.show()

    plt.hist(weightsDied, color='firebrick')
    plt.title('Sparrows that perished',size=titleSize)
    plt.xlabel('Weights',size=labelSize)
    plt.ylabel('No. of sparrows',size=labelSize)
    plt.show()

    ecdf = ECDF(weightsSurvived)
    plt.plot(ecdf.x, ecdf.y, color='g')
    plt.title('Sparrows that survived',size=titleSize)
    plt.ylabel('Cumulative Distribution Function',size=labelSize)
    plt.xlabel('Weights',size=labelSize)
    plt.show()

    ecdf = ECDF(weightsDied)
    plt.plot(ecdf.x, ecdf.y, color='firebrick')
    plt.title('Sparrows that perished',size=titleSize)
    plt.ylabel('Cumulative Distribution Function',size=labelSize)
    plt.xlabel('Weights',size=labelSize)
    plt.show()

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

    


weightsSurvived, weightsDied = importData('data.csv')
SolutionTask1(weightsSurvived=weightsSurvived,weightsDied=weightsDied)
SolutionTask2(weightsSurvived=weightsSurvived,weightsDied=weightsDied)
# SolutionTask4()