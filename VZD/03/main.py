import datetime
import numpy as np
import matplotlib.pyplot as plt
# This import registers the 3D projection, but is otherwise unused.
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 unused import
import matplotlib
import matplotlib.patches as mpatches

#plt.rc('xtick', labelsize=18) 
#plt.rc('ytick', labelsize=18)
plt.rc('axes', titlesize=20)  
plt.rc('axes', labelsize=18)

LABEL_COLOR_MAP = {0 : 'r', 1 : 'g', 2 : 'b', 3 : 'c', 4 : 'm', 5 : 'y', 6 : 'k'}




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


INT_MAX = 2147483647
with open("eshop.csv",'r') as f:
    lines = [line.rstrip('\n') for line in f]

lastDay = datetime.datetime(2015,12,19)
matrix = {} #ID customer, diff between last date and date of an sale, price of an sale
for line in lines[1:]:
    tmp = line.split(',')
    tmpDate = tmp[1].split('/')
    time1 = datetime.datetime(int(tmpDate[2]),int(tmpDate[0]),int(tmpDate[1]))
    diffDays = (lastDay-time1).days

    if int(tmp[0]) not in matrix.keys():
        matrix[int(tmp[0])] = [[diffDays,float(tmp[2])]]
    else:
        matrix[int(tmp[0])].append([diffDays,float(tmp[2])])

uniqueIDList = list(matrix.keys())

#každý řádek odpovídá jednomu zákazníkovi a sloupce (příznaky) jsou uvedené výše.
rmfDataFrame = [[] for i in range(len(uniqueIDList))]
rmfDataFrameBonus = [[] for i in range(len(uniqueIDList))]

# Recency
# nebonus -> Počet dnů od posledního nákupu (poslední datum v datasetu pro daného zákazníka).
# bonus -> maximum počtu měsíců od posledního nákupu a čísla 1
for cnt, ID in enumerate(uniqueIDList):
    nebonus = INT_MAX
    bonus = INT_MAX
    for order in matrix[ID]:
        if order[0] < nebonus:
            nebonus = order[0]
        if order[0]//30 < bonus:
            bonus = order[0]//30
    bonus = max(bonus,1)
    rmfDataFrame[cnt].append(nebonus)
    rmfDataFrameBonus[cnt].append(bonus)

# Frequency
# nebonus -> Počet nákupů.
# bonus -> maximum počtu nákupů daného zákazníka v posledních 12 měsících a čísla 1
for cnt, ID in enumerate(uniqueIDList):
    nebonus = 0
    bonus = 0
    for order in matrix[ID]:
        nebonus += 1
        if order[0] <= 365:
            bonus += 1
    bonus = max(bonus,1)
    rmfDataFrame[cnt].append(nebonus)
    rmfDataFrameBonus[cnt].append(bonus)

# Monetary
# nebonus -> Celková suma, kterou daný zákazník utratil.
# bonus -> Nejvyšší hodnota nákupu daného zákazníka
for cnt, ID in enumerate(uniqueIDList):
    nebonus = 0.0
    bonus = -1
    for order in matrix[ID]:
        nebonus += order[1]
        if order[1] > bonus:
            bonus = order[1]
    bonus = max(bonus,1)
    rmfDataFrame[cnt].append(nebonus)
    rmfDataFrameBonus[cnt].append(bonus)

from sklearn.cluster import KMeans
rmfDataFrame = np.array(rmfDataFrame)
rmfDataFrameBonus = np.array(rmfDataFrameBonus)

import collections, numpy


# Ukázka dat
# Nyní si ukážeme rmf body ve 3D prostoru.
kmeans = KMeans(n_clusters=3, random_state=0).fit(rmfDataFrame)
print(collections.Counter(kmeans.labels_))
label_color = [LABEL_COLOR_MAP[l] for l in kmeans.labels_]
ax = plt.figure().add_subplot(111, projection='3d')
ax.scatter(rmfDataFrame[:,0],rmfDataFrame[:,1],rmfDataFrame[:,2],color=label_color)
ax.set_xlabel("Recency")
ax.set_ylabel("Frequency")
ax.set_zlabel("Monetary")
plt.show()

# Vidíme, že jelikož jsou body nepřeškálované, tak mají některé dimenze větši vliv než ostatní (kvůli tomu, že clustery určujeme podle vzdálenosti)
# Proto normalizujeme body podle příznaků tak, aby byl každý příznak rmf bodu mezi [0-1].
rmfDataFrame = myNorm(rmfDataFrame)
rmfDataFrameBonus = myNorm(rmfDataFrameBonus)
kmeans = KMeans(n_clusters=3, random_state=0).fit(rmfDataFrame)
print(collections.Counter(kmeans.labels_))
label_color = [LABEL_COLOR_MAP[l] for l in kmeans.labels_]
ax = plt.figure().add_subplot(111, projection='3d')
ax.scatter(rmfDataFrame[:,0],rmfDataFrame[:,1],rmfDataFrame[:,2],color=label_color)
ax.set_xlabel("Recency")
ax.set_ylabel("Frequency")
ax.set_zlabel("Monetary")
plt.show()


## Hledání počtu clusterů
# Jelikož máme data dimenze 3, můžeme si data a jednotlivé clustery vizualizovat a výsledný počet clusterů můžeme určit odhadem,
# kdy se nám bude zdát, že je splněna podmínka kdy blízké body budou ve stejném shluku a zároveň vzdálené body budou v různých shlucích.
# Častým způsobem určení k je hledání tzv. loket (angl. elbow) neboli místa grafu účelové funkce pro kterou se mění pokles účelové funkce z hodně prudkého na méně prudký.
# V našem případě použijeme jako účelovou funkci tzv. Silhouette hodnotu.

from sklearn.metrics import silhouette_score
X, Y, YBonus = [], [], []
for i in range(2,20):
    kmeans = KMeans(n_clusters=i, random_state=0).fit(rmfDataFrame)
    kmeansBonus = KMeans(n_clusters=i, random_state=0).fit(rmfDataFrameBonus)
    score = silhouette_score(rmfDataFrame,kmeans.labels_)
    scoreBonus = silhouette_score(rmfDataFrameBonus,kmeansBonus.labels_)
    X.append(i)
    Y.append(score)
    YBonus.append(scoreBonus)

plt.plot(X,Y,color='green')
plt.plot(X,YBonus,color='blue')
plt.xlabel('Pocet clusteru')
plt.ylabel('Silhouette score')
plt.title('Vliv poctu clusteru na Silhouette score')
patchesList = []
patchesList.append(mpatches.Patch(color='green', label='RMF'))
patchesList.append(mpatches.Patch(color='blue', label='Modifikovana RMF'))
plt.legend(handles=patchesList)
plt.show()


# Hledání počtu clusterů
# Subjektivně řeknu, že tzv. loket nastáva když je k = 4. V našem případě nám tato metoda moc nepomohla, jelikož výsledné počet clusterů byl příliš malý odlišení superstar zákazníků.
# Nakonec jsem přidával k (počinaje od čísla 4), dokud jsem nenašel první číslo, které superstar zákazníky efektivně odlišilo. Došel jsem ke k=7.
kmeans = KMeans(n_clusters=7, random_state=0).fit(rmfDataFrame)
print(collections.Counter(kmeans.labels_))
label_color = [LABEL_COLOR_MAP[l] for l in kmeans.labels_]
ax = plt.figure().add_subplot(111, projection='3d')
ax.scatter(rmfDataFrame[:,0],rmfDataFrame[:,1],rmfDataFrame[:,2],color=label_color)
ax.set_xlabel("Recency")
ax.set_ylabel("Frequency")
ax.set_zlabel("Monetary")
plt.show()

kmeans = KMeans(n_clusters=7, random_state=0).fit(rmfDataFrameBonus)
print(collections.Counter(kmeans.labels_))
label_color = [LABEL_COLOR_MAP[l] for l in kmeans.labels_]
ax = plt.figure().add_subplot(111, projection='3d')
ax.scatter(rmfDataFrameBonus[:,0],rmfDataFrameBonus[:,1],rmfDataFrameBonus[:,2],color=label_color)
ax.set_xlabel("Recency")
ax.set_ylabel("Frequency")
ax.set_zlabel("Monetary")
plt.show()
