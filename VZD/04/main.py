from sklearn import svm
from sklearn.model_selection import cross_val_score
from sklearn.linear_model import LinearRegression
from sklearn.linear_model import Ridge
from sklearn.decomposition import PCA
from sklearn.linear_model import LassoCV
from sklearn.ensemble import RandomForestRegressor

import warnings
warnings.simplefilter(action='ignore', category=FutureWarning)

def myNorm(X):
    myMaxes = [0 for i in range(len(X[0]))]
    for item in X:
        for i in range(len(item)):
            if item[i] > myMaxes[i]:
                myMaxes[i] = item[i]

    for j in range(len(X)):
        for i in range(len(X[j])):
            X[j][i] /= float(myMaxes[i])

    return X

def LoadData():
    path = 'Residential-Building-Data-Set.xlsx'
    import pandas
    df = pandas.read_excel(path,header=1)
    return df


def ConvertToArray(df):
    X, Y1, Y2 = [], [], []
    n_of_rows = len(df.index)

    for i in range(n_of_rows):
        entire_row = list(df.iloc[i])
        X.append(entire_row[:-2])
        Y1.append(entire_row[-2])
        Y2.append(entire_row[-1])

    return X, Y1, Y2


print('Results without any normalization or feature engineering:')

df = LoadData()
X, Y1, Y2 = ConvertToArray(df)
delimiter = 330

x_test = X[delimiter:]
y1_test = Y1[delimiter:]
y2_test = Y2[delimiter:]

X = X[:delimiter]
Y1 = Y1[:delimiter]
Y2 = Y2[:delimiter]

reg = LinearRegression()
res = abs(cross_val_score(reg, X, Y1,cv=10,scoring='neg_mean_absolute_error').mean()) + abs(cross_val_score(reg, X, Y2,cv=10,scoring='neg_mean_absolute_error').mean())
res /= 2.0
print('Linear Regression MAE:',res)

ridge = Ridge()
res = abs(cross_val_score(ridge, X, Y1,cv=10,scoring='neg_mean_absolute_error').mean()) + abs(cross_val_score(ridge, X, Y2,cv=10,scoring='neg_mean_absolute_error').mean())
res /= 2.0
print('Ridge Regression MAE:',res)

regr = RandomForestRegressor(max_depth=8, random_state=0)
res = abs(cross_val_score(regr, X, Y1,cv=10,scoring='neg_mean_absolute_error').mean()) + abs(cross_val_score(regr, X, Y2,cv=10,scoring='neg_mean_absolute_error').mean())
res /= 2.0
print('Random Forest MAE:',res)


def TakeFinalFeature(df):
    for i in range(11,29):
        for j in range(1,3):
            df = df.drop(['V-'+str(i)+'.'+str(j)],axis=1)

    return df


def SelectFeatures(df):
    cor = df.corr()
    cor_target1 = abs(cor['V-9'])
    relevant_features1 = cor_target1[cor_target1 < 0.2]

    cor_target2 = abs(cor['V-10'])
    relevant_features2 = cor_target2[cor_target2 < 0.2]

    print(relevant_features1)
    print(relevant_features2)

    df.drop(['V-3','V-28.4'], axis=1)

    return df

print('Results with feature selection:')

df = LoadData()
df = TakeFinalFeature(df)
df = SelectFeatures(df)
X, Y1, Y2 = ConvertToArray(df)

x_test = X[delimiter:]
y1_test = Y1[delimiter:]
y2_test = Y2[delimiter:]

X = X[:delimiter]
Y1 = Y1[:delimiter]
Y2 = Y2[:delimiter]

reg = LinearRegression()
res = abs(cross_val_score(reg, X, Y1,cv=10,scoring='neg_mean_absolute_error').mean()) + abs(cross_val_score(reg, X, Y2,cv=10,scoring='neg_mean_absolute_error').mean())
res /= 2.0
print('Linear Regression MAE:',res)

ridge = Ridge()
res = abs(cross_val_score(ridge, X, Y1,cv=10,scoring='neg_mean_absolute_error').mean()) + abs(cross_val_score(ridge, X, Y2,cv=10,scoring='neg_mean_absolute_error').mean())
res /= 2.0
print('Ridge Regression MAE:',res)

regr = RandomForestRegressor(max_depth=8, random_state=0)
res = abs(cross_val_score(regr, X, Y1,cv=10,scoring='neg_mean_absolute_error').mean()) + abs(cross_val_score(regr, X, Y2,cv=10,scoring='neg_mean_absolute_error').mean())
res /= 2.0
print('Random Forest MAE:',res)



# Data standardization
from sklearn.preprocessing import StandardScaler
scaler = StandardScaler()
scaler.fit(X)
transformedX = scaler.transform(X)

res = abs(cross_val_score(reg, transformedX, Y1, cv=10, scoring='neg_mean_absolute_error').mean()) + abs(cross_val_score(reg, transformedX, Y2, cv=10, scoring='neg_mean_absolute_error').mean())
print('Linear regression MAE after standardization:',res/2.0)

res = abs(cross_val_score(ridge, transformedX, Y1, cv=10, scoring='neg_mean_absolute_error').mean()) + abs(cross_val_score(ridge, transformedX, Y2, cv=10, scoring='neg_mean_absolute_error').mean())
print('Ridge regression MAE after standardization:',res/2.0)

res = abs(cross_val_score(regr, transformedX, Y1, cv=10, scoring='neg_mean_absolute_error').mean()) + abs(cross_val_score(regr, transformedX, Y2, cv=10, scoring='neg_mean_absolute_error').mean())
print('Random forest MAE after standardization:',res/2.0)




# Find hyperparameters
import numpy as np
from sklearn.model_selection import RandomizedSearchCV

n_estimators = [20,50,100,200]
max_features = ['auto', 'sqrt']
max_depth = [3,6,10,30]
max_depth.append(None)
min_samples_split = [2, 5, 10]
min_samples_leaf = [1, 2, 4]
bootstrap = [True, False]

# Create the random grid
random_grid = {'n_estimators': n_estimators,
               'max_features': max_features,
               'max_depth': max_depth,
               'min_samples_split': min_samples_split,
               'min_samples_leaf': min_samples_leaf,
               'bootstrap': bootstrap}

grid_search = RandomizedSearchCV(estimator = regr, param_distributions = random_grid, n_iter = 100, cv = 3, verbose=1, random_state=42, n_jobs = 1)
grid_search.fit(X,Y1)

print('Best parameters:',grid_search.best_params_)

regr = RandomForestRegressor(**(grid_search.best_params_))

res = abs(cross_val_score(regr, X, Y1, cv=10, scoring='neg_mean_absolute_error').mean()) + abs(cross_val_score(regr, X, Y2, cv=10, scoring='neg_mean_absolute_error').mean())
print('Best Random forest MAE:',res/2.0)


solver = ['svd', 'cholesky', 'lsqr', 'sparse_cg', 'sag', 'saga']
alpha = [0.001, 0.05,0.2,1,3,10,100,300]

# Create the random grid for ridge regression
random_grid_ridge = {'solver': solver,
               'alpha': alpha,}

grid_search = RandomizedSearchCV(estimator = ridge, param_distributions = random_grid_ridge, n_iter = 100, cv = 3, verbose=1, random_state=42, n_jobs = 1)
grid_search.fit(X,Y1)

print('Best parameters for ridge regression:',grid_search.best_params_)

ridge = Ridge(**(grid_search.best_params_))

res = abs(cross_val_score(ridge, X, Y1, cv=10, scoring='neg_mean_absolute_error').mean()) + abs(cross_val_score(ridge, X, Y2, cv=10, scoring='neg_mean_absolute_error').mean())
print('Best Ridge regression MAE:',res/2.0)



from sklearn.metrics import mean_absolute_error
res = 0

regr.fit(X,Y1)
pred = regr.predict(x_test)
res += mean_absolute_error(pred,y1_test)

regr.fit(X,Y2)
pred = regr.predict(x_test)
res += mean_absolute_error(pred,y2_test)

print('Best Random forest MAE on a testing set:',res/2.0)

res = 0
ridge.fit(X,Y1)
pred = ridge.predict(x_test)
res += mean_absolute_error(pred,y1_test)

ridge.fit(X,Y2)
pred = ridge.predict(x_test)
res += mean_absolute_error(pred,y2_test)
print('Ridge on a testing set:',res/2.0)