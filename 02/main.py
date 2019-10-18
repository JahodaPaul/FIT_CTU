

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

def FixMissingAges1(X):
    suma = 0
    counter = 0
    for i in range(len(X)):
        if X[i][4] != -1:
            suma += X[i][4]
            counter += 1
            
    mean = suma/counter
    for i in range(len(X)):
        if X[i][4] == -1:
            X[i][4] = mean
    
    return mean 
    
def FixMissingAges2(X):
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
    FixMissingAges2(X)
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
#for i in range(len(x_train)):
#    print(x_train[i],y_train[i])

x_val = x_train[800:]
y_val = y_train[800:]
x_train = x_train[:800]
y_train = y_train[:800]

# SVM
from sklearn import svm
clf = svm.SVC(max_iter=1000)
clf.fit(x_train, y_train)
print(clf.score(x_val, y_val))


# Extrmeely randomised trees
from sklearn.ensemble import ExtraTreesClassifier
trees = ExtraTreesClassifier(100,class_weight='balanced')
trees.fit(x_train, y_train)
print(trees.score(x_val, y_val))

# Random forest
from sklearn.ensemble import RandomForestClassifier
forest = RandomForestClassifier(100)
forest.fit(x_train, y_train)
print(forest.score(x_val, y_val))

