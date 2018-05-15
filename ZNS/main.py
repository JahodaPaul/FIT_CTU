import sys
from Config import *
from Data import Data
from UI import UI
from Fuzzy import Fuzzy
from PyQt5 import QtWidgets


data = Data()
fuzzy = Fuzzy()

for dataFromFile in data.dataMatrix:
    dataFromFile[1] = data.Normalize(dataFromFile[1])

data.scores = [[0,""] for i in range(len(data.countries))]

try:
    app = QtWidgets.QApplication(sys.argv)
    GUI = UI(fuzzy=fuzzy,data=data)
    sys.exit(app.exec_())
except Exception as exc:
    pass