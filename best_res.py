import os

files = os.listdir('res')

bestRMSE = 1000000000
bestFile = ''

for f in files:
    with open(os.path.join('res',f),'r') as ff:
        lines = [line.rstrip('\n') for line in ff]
    RMSE = float(lines[0].split(',')[2])
    collissions = lines[0].split(',')[3]

    RMSE *= (float(collissions)*0.2+1)

    if bestRMSE > RMSE:
        bestRMSE = RMSE
        bestFile = f


print(bestRMSE)
print(bestFile)


