#%matplotlib inline
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from scipy import stats
from scipy.stats import expon
from statsmodels.distributions.empirical_distribution import ECDF

def importData(dataPath):
    data = pd.read_csv(dataPath, sep=';').replace({'perished' : 0, 'survived' : 1})
    return np.array(data.loc[data.Status == 1].Weight), np.array(data.loc[data.Status == 0].Weight)

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
    print(len(weightsSurvived),len(weightsDied))
    return np.mean(weightsSurvived), np.var(weightsSurvived), np.mean(weightsDied), np.var(weightsDied)

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

def SolutionTask3(weightsSurvived, weightsDied):
    titleSize = 20
    labelSize = 16

    EX1 = 25.462857273646772
    x1 = np.linspace(min(weightsSurvived),max(weightsSurvived),100)
    exponencialX1 = expon.pdf(x1,scale=1,loc=min(weightsSurvived))
    normalDistributionX1 = stats.norm.pdf(x1,loc=EX1)


    plt.hist(weightsSurvived,density=True, color='lightgray')
    pl1 = plt.plot(x1,exponencialX1,color='blue')
    pl2 = plt.plot(x1,normalDistributionX1,color='green')
    pl3 = plt.plot([min(weightsSurvived),max(weightsSurvived)],[1/float(max(weightsSurvived)-min(weightsSurvived)) for i in range(2)],color='red')
    plt.title('Sparrows that survived',size=titleSize)
    plt.xlabel('Weights',size=labelSize)
    plt.ylabel('Density',size=labelSize)
    plt.legend([pl1[0],pl2[0],pl3[0]],['Exponencial','Normal','Uniform'],fontsize='x-large')
    plt.show()

    EX2 = 26.275
    x2 = np.linspace(min(weightsDied),max(weightsDied),100)
    exponencialX2 = expon.pdf(x2,scale=1,loc=min(weightsDied))
    normalDistributionX2 = stats.norm.pdf(x2,loc=EX2)

    n,bins,_ = plt.hist(weightsDied, density=True, color='lightgray')
    pl1 = plt.plot(x2,exponencialX2,color='blue')
    pl2 = plt.plot(x2,normalDistributionX2,color='green')
    pl3 = plt.plot([min(weightsDied),max(weightsDied)],[1/float(max(weightsDied)-min(weightsDied)) for i in range(2)],color='red')
    plt.title('Sparrows that perished',size=titleSize)
    plt.xlabel('Weights',size=labelSize)
    plt.ylabel('Density',size=labelSize)
    plt.legend([pl1[0], pl2[0], pl3[0]], ['Exponencial', 'Normal', 'Uniform'], fontsize='x-large')
    plt.show()

    sumExpon = 0
    sumNormal = 0
    for cnt in range(len(bins)-1):
        closestVal = 10000000
        closestIndex = 0
        for i in range(len(x2)):
            if abs((bins[cnt]+bins[cnt+1])/2 - x2[i]) < closestVal:
                closestVal = abs((bins[cnt]+bins[cnt+1])/2 - x2[i])
                closestIndex = i
        sumExpon += abs(n[cnt] - exponencialX2[closestIndex])*abs(n[cnt] - exponencialX2[closestIndex])
        sumNormal += abs(n[cnt] - normalDistributionX2[closestIndex])*abs(n[cnt] - normalDistributionX2[closestIndex])
    print('The sum of differences between exponencial distribution and histogram is:', sumExpon)
    print('The sum of differences between normal distribution and histogram is:', sumNormal)

def SolutionTask4(weightsSurvived, weightsDied, meanS, varS, meanD, varD):
    S_gen = []
    D_gen = []
    
    for i in range(0,100): 
        S_gen.append(np.random.normal(loc=meanS,scale=np.sqrt(varS)))

    for i in range(0,100):
        D_gen.append(np.random.normal(loc=meanD,scale=np.sqrt(varD)))
    
    bins = np.linspace(21, 33, 13, endpoint=True)
    plt.figure(figsize=(6,4))
    plt.xlim(21, 33)
    plt.title('Generated X1')
    plt.hist(S_gen, bins, color='red', alpha=0.5)
    plt.xlabel('Weight')
    plt.ylabel('No. of birds')
#     plt.savefig('pst/Report/images/4_Survived_Gen.png', bbox_inches='tight')
    plt.show()

    plt.figure(figsize=(6,4))
    plt.xlim(21, 33)
    plt.title('X1')
    plt.hist(weightsSurvived, bins, color='blue', alpha=0.5)
    plt.xlabel('Weight')
    plt.ylabel('No. of birds')
#     plt.savefig('pst/Report/images/4_Survived_Data.png', bbox_inches='tight')
    plt.show()

    plt.figure(figsize=(6,4))
    plt.xlim(21, 33)
    plt.title('Generated X2')
    plt.hist(D_gen, bins, color='red',alpha=0.5)
    plt.xlabel('Weight')
    plt.ylabel('No. of birds')
#     plt.savefig('pst/Report/images/4_Died_Gen.png', bbox_inches='tight')
    plt.show()

    plt.figure(figsize=(6,4))
    plt.xlim(21, 33)
    plt.title('X2')
    plt.hist(weightsDied, bins, color='blue', alpha=0.5)
    plt.xlabel('Weight')
    plt.ylabel('No. of birds')
#     plt.savefig('pst/Report/images/4_Died_Data.png', bbox_inches='tight')
    plt.show()

def SolutionTask5(weightsSurvived, weightsDied, meanS, varS, meanD, varD):
    n1 = len(weightsSurvived)
    n2 = len(weightsDied)
    
    res1 = 0
    for i in range(0,n1):
        res1 += (weightsSurvived[i] - meanS) ** 2
    res1 = res1/(n1-1)

    t1 = 2.03
    L1 = meanS - t1 * np.sqrt(res1) / np.sqrt(n1)
    U1 = meanS + t1 * np.sqrt(res1) / np.sqrt(n1)
    
    res2 = 0
    for i in range(0,n2):
        res2 += (weightsDied[i] - meanD) ** 2
    res2 = res2/(n2-1)
    
    t2 = 2.06
    L2 = meanD - t2 * np.sqrt(res2) / np.sqrt(n2)
    U2 = meanD + t2 * np.sqrt(res2) / np.sqrt(n2)
    
    print('Lower for X1: %0.3f' % L1)
    print('Upper for X1: %0.3f' % U1)
    print('=================')
    print('Lower for X2: %0.3f' % L2)
    print('Lower for X2: %0.3f' % U2)    
    print('=================')
    print('sn1: %0.3f' % res1)
    print('sn2: %0.3f' % res2)

def SolutionTask7(weightsSurvived, weightsDied):
    p_value1 = stats.ttest_ind(weightsSurvived, weightsDied, equal_var=True)
    print(p_value1[1])
 
    p_value2 = stats.bartlett(weightsSurvived, weightsDied)
    print(p_value2[1])

weightsSurvived, weightsDied = importData('data.csv')
meanS, varS, meanD, varD = SolutionTask1(weightsSurvived=weightsSurvived,weightsDied=weightsDied)
#SolutionTask2(weightsSurvived=weightsSurvived,weightsDied=weightsDied)
SolutionTask3(weightsSurvived=weightsSurvived,weightsDied=weightsDied)
#SolutionTask4(weightsSurvived, weightsDied, meanS, varS, meanD, varD)
#SolutionTask5(weightsSurvived, weightsDied, meanS, varS, meanD, varD)
#SolutionTask7(weightsSurvived, weightsDied)