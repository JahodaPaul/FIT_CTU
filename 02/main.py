from sklearn.model_selection import cross_val_score

def ConvertNameToVector(name):
    titles = ['Sir.','Master.','Mr.','Mrs.','Miss.']
    tmp = -1
    for i in range(len(titles)):
        if titles[i] in name:
            tmp = i
    return [len(name),tmp]

def ConvertEmbarkedToVector(embarked):
    if embarked == 'C':
        return [1,0,0]
    if embarked == 'Q':
        return [0,1,0]
    if embarked == 'S':
        return [0,0,1]
    return [0,0,0]
    
def ConvertEmbarkedToVector(embarked):
    if embarked == 'C':
        return [1,0,0]
    if embarked == 'Q':
        return [0,1,0]
    if embarked == 'S':
        return [0,0,1]
    return [0,0,0]


def ConvertFile(path): #Write missing values as -1
    with open(path,'r') as f:
        lines = [line.rstrip('\n') for line in f]
    X = []
    Y = []
    for line in lines[1:]:
        cnt = 0
        tmpArr = line.split(',')
        if not 'evaluation' in path:
            Y.append(int(tmpArr[1]))
        else:
            cnt -= 1
            Y.append(int(tmpArr[0]))
        tmpX = []
        
        pClass = -1 if tmpArr[2+cnt] == '' else (int(tmpArr[2+cnt]))
        
        name = ''
        while tmpArr[3+cnt] != 'male' and tmpArr[3+cnt] != 'female' and tmpArr[3+cnt] != '':
            name += tmpArr[3+cnt]
            cnt += 1
        
        tmpX.extend(ConvertNameToVector(name))
        cnt -= 1
        
        maleXFemale = -1 if tmpArr[4+cnt] == '' else (1 if tmpArr[4+cnt] == 'male' else 0)
        tmpX.append(pClass)
        tmpX.append(maleXFemale)
        for i in range(5+cnt,10+cnt):
            try:
                val = -1 if tmpArr[i] == '' else (float(tmpArr[i]))
            except Exception as ex: # cabin with string at the beginning
                tmp = tmpArr[i].split(' ')
                if len(tmp) == 1:
                    val = -1
                else:
                    val = float(tmp[-1])
            tmpX.append(val)
        tmpX.extend(ConvertEmbarkedToVector(tmpArr[11+cnt]))
        X.append(tmpX)
        
    return X, Y

# This one achieved higher accuracy
def FixMissingAges1(X): # Predict missing ages using distribution of current ages
    import random
    currentAges = []
    for i in range(len(X)):
        if X[i][4] != -1:
            currentAges.append(X[i][4])

    for i in range(len(X)):
        if X[i][4] == -1:
            X[i][4] = currentAges[random.randrange(0,len(currentAges))]
    return X
    
def FixMissingAges2(X): # Predict missing ages using regression
    from sklearn.ensemble import RandomForestRegressor
    regressionArr, y = [],[]
    regressionTestArr = []
    for i in range(len(X)):
        if X[i][4] != -1:
            tmp = []
            for j in range(len(X[i])):
                if j!=4:
                    tmp.append(X[i][j])
                    
            regressionArr.append(tmp)
            y.append(X[i][4])
    for i in range(len(X)):
        if X[i][4] == -1:
            tmp = []
            for j in range(len(X[i])):
                if j!=4:
                    tmp.append(X[i][j])
                    
            regressionTestArr.append(tmp)
    
    rfRegressor = RandomForestRegressor(100)
    rfRegressor.fit(regressionArr,y)
    predictions = rfRegressor.predict(regressionTestArr)
    
    counter = 0
    for i in range(len(X)):
        if X[i][4] == -1:
            X[i][4] = predictions[counter]
            counter += 1
    return X
    
    
def myNorm(X):
    FixMissingAges1(X)
    myMaxes = [0 for i in range(len(X[0]))]
    for item in X:
        for i in range(len(item)):
            if item[i] > myMaxes[i]:
                myMaxes[i] = item[i]
    
    for j in range(len(X)):
        for i in range(len(X[j])):
            X[j][i] /= float(myMaxes[i])

    return X



x_train, y_train = ConvertFile('data.csv')
x_train = myNorm(x_train)
x_test, y_test = ConvertFile('evaluation.csv')

# SVM
from sklearn import svm
clf = svm.SVC(max_iter=1000,gamma='auto')
print('SVM accuracy:',cross_val_score(clf, x_train, y_train,cv=10).mean())


# Extremely randomised trees
from sklearn.ensemble import ExtraTreesClassifier
trees = ExtraTreesClassifier(100,class_weight='balanced')
print('Extremely randomised trees accuracy:',cross_val_score(trees, x_train, y_train,cv=10).mean())

# Random forest
from sklearn.ensemble import RandomForestClassifier
forest = RandomForestClassifier(100)
print('Random Forest accuracy:',cross_val_score(forest, x_train, y_train,cv=10).mean())

# Knn
from sklearn.neighbors import KNeighborsClassifier
knn = KNeighborsClassifier(n_neighbors=5)
print('kNN accuracy:',cross_val_score(knn, x_train, y_train,cv=10).mean())


# Find optimal hyper parameters for Random Forest
nOfEstimators = [10,50,100,150]
bestIndexEst = 0
max_depth = [4,8,16,32,64]
bestIndexDepth = 0
max_features = ['log2','sqrt']
bestIndexFeat = 0
bestCurrentVal = 0

for i in range(len(nOfEstimators)):
    for j in range(len(max_depth)):
        for k in range(len(max_features)):
            forest = RandomForestClassifier(n_estimators=nOfEstimators[i],max_depth=max_depth[j],max_features=max_features[k])
            val = cross_val_score(forest, x_train, y_train,cv=10).mean()
            print(str(i*(len(max_depth)*len(max_features)) + j*len(max_features) + k) +'/'+str(len(nOfEstimators)*len(max_depth)*len(max_features))+ ' searching hyperparameters')
            if val > bestCurrentVal:
                bestCurrentVal = val
                bestIndexEst = i
                bestIndexDepth = j
                bestIndexFeat = k
print('Best cross-validation accuracy:',bestCurrentVal)
print('Best parameters:')
print('Estimators:',nOfEstimators[bestIndexEst])
print('Max depth:',max_depth[bestIndexDepth])
print('Max features:',max_features[bestIndexFeat])
forest = RandomForestClassifier(n_estimators=nOfEstimators[bestIndexEst],max_depth=max_depth[bestIndexDepth],max_features=max_features[bestIndexFeat])
forest.fit(x_train, y_train)
predictions = forest.predict(x_test)
with open('results.csv','w') as f:
    for i in range(len(predictions)):
        line = str(y_test[i]) + ',' + str(predictions[i]) + '\n'
        f.write(line)
