import datetime

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
