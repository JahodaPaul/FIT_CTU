# from tkinter import *
import sys
import copy
from operator import itemgetter
from Config import *
from PyQt5 import QtGui
from PyQt5 import QtWidgets, QtCore
from Fuzzy import Fuzzy

class UI(QtWidgets.QMainWindow):

    def __init__(self,fuzzy,data):
        self.listOfWidgetByEachStage = []
        self.stage1List = [] # two selected buttons
        self.fuzzy = fuzzy
        self.data = data
        self.indexStage2 = 0
        self.topicStage4 = -1
        self.indexStage4 = 1

        super(UI,self).__init__()
        self.setGeometry(650,300,400,500)
        self.setWindowTitle("Country Selector")
        self.setWindowIcon(QtGui.QIcon('icon.png'))
        self.Start()

    def Start(self):
        self.layout = QtWidgets.QGridLayout(self)
        self.DefineWidgets(self.listOfWidgetByEachStage,self.layout)
        self.StartStage1()
        self.show()

    def MyPrint(self,arr,showWholeRankings):
        temporaryResult = copy.deepcopy(arr)
        temporaryResult.sort(key=itemgetter(0))
        temporaryResult.reverse()
        howManyCountriesShow = len(self.data.countries)
        if not showWholeRankings:
            howManyCountriesShow = 3
        for i in range(howManyCountriesShow):
            self.listOfWidgetByEachStage[-1][i * 2].show()
            self.listOfWidgetByEachStage[-1][i * 2+1].show()
            self.listOfWidgetByEachStage[-1][i*2].setText(str(i+1)+'. '+ CountryFullName[temporaryResult[i][1]]+' :')
            self.listOfWidgetByEachStage[-1][i * 2+1].setText(str("%.2f" % temporaryResult[i][0]))

        if howManyCountriesShow == 3:
            for i in range(3,len(self.data.countries)):
                self.listOfWidgetByEachStage[-1][i * 2].hide()
                self.listOfWidgetByEachStage[-1][i * 2 + 1].hide()
            self.listOfWidgetByEachStage[-1][(len(self.data.countries)-1) * 2].show()
            self.listOfWidgetByEachStage[-1][(len(self.data.countries)-1) * 2 + 1].show()
            self.listOfWidgetByEachStage[-1][(len(self.data.countries)-1) * 2].setText(str((len(self.data.countries))) + '. ' + CountryFullName[temporaryResult[-1][1]] + ' :')
            self.listOfWidgetByEachStage[-1][(len(self.data.countries)-1) * 2 + 1].setText(str("%.2f" % temporaryResult[-1][0]))

    def HideRestOfWidgets(self,index,showRankings):
        for cnt,list in enumerate(self.listOfWidgetByEachStage):
            if cnt == len(self.listOfWidgetByEachStage)-1 and showRankings:
                self.MyPrint(self.data.scores,False)
            elif cnt != index:
                for item in list:
                    item.hide()
            else:
                for item in list:
                    item.show()

    def StartStage1(self):
        self.HideRestOfWidgets(0,False)

    def StartStage2(self):
        self.listOfWidgetByEachStage[1][0].setText(questionFormat + ' ' + finalQuestions[0][0])
        self.HideRestOfWidgets(1,True)

    def StartStage3(self):
        self.HideRestOfWidgets(2, True)

    def StartStage4(self):
        if self.indexStage4 == len(finalQuestions[self.topicStage4]):
            self.StartStage5()
        else:
            self.HideRestOfWidgets(3, True)
            self.listOfWidgetByEachStage[3][0].setText(questionFormat + ' ' + finalQuestions[self.topicStage4][1])

    def StartStage5(self):
        self.HideRestOfWidgets(4,False)
        self.MyPrint(self.data.scores,True)

    def StartStageExplaining(self):
        self.HideRestOfWidgets(5,False)
        self.listOfWidgetByEachStage[5][0].setText(CountryFullName[self.data.ReturnFirstCountryBasedOnPoints(self.data.scores)] +
                                                   ' ended up first because it matched your answers the most')

    def CreateButton(self,text,positionX,positionY,function,parameterForFunction,anotherParam,minX,minY):
        btn = QtWidgets.QPushButton(text,self)
        btn.move(positionX,positionY)
        btn.setMinimumSize(minX, minY)
        if anotherParam == 0:
            btn.clicked.connect(lambda : function(parameterForFunction,btn))
        else:
            btn.clicked.connect(lambda: function(parameterForFunction, anotherParam))
        return btn

    def CreateLabelRanking(self,text,positionX,positionY,minX,minY):
        label = QtWidgets.QLabel(text,self)
        label.setWordWrap(True)
        label.setMinimumSize(minX,minY)
        label.move(positionX,positionY)
        return label

    def DefaultFunction(self,param,param2):
        pass

    #selection 2 out of three items
    def Stage1Function(self,index,btn):
        self.stage1List.append(index)
        btn.hide()

        if len(self.stage1List) == 2:
            self.fuzzy.startFuzzySystem(self.stage1List)
            self.fuzzy.addPointsToMainSystem(self.data.scores,self.data.countries)
            self.MyPrint(self.data.scores,False)
            self.StartStage2()

    def Stage2Function(self,weight,btn):
        self.data.scores = self.data.AddPointsToMainSystem(self.data.dataMatrix,self.indexStage2,0,weight,self.data.scores,self.data.countries)
        self.MyPrint(self.data.scores, False)

        self.indexStage2 += 1
        if self.indexStage2 == len(finalQuestions):
            self.StartStage3()
        else:
            self.listOfWidgetByEachStage[1][0].setText(questionFormat + ' ' + finalQuestions[self.indexStage2][0])

    def Stage3Function(self,index,bnt):
        self.topicStage4 = index
        self.StartStage4()

    def Stage4Function(self,weight,btn):
        self.data.scores = self.data.AddPointsToMainSystem(self.data.dataMatrix,self.topicStage4,self.indexStage4,weight,self.data.scores,self.data.countries)

        self.MyPrint(self.data.scores, False)

        self.indexStage4 += 1
        if self.indexStage4 == len(finalQuestions[self.topicStage4]):
            self.StartStage5()
        else:
            self.listOfWidgetByEachStage[3][0].setText(questionFormat + ' ' + finalQuestions[self.topicStage4][self.indexStage4])

    def Explain(self,nothing,btn):
        self.StartStageExplaining()

    def Quit(self,nothing,nothing2):
        exit()

    def GoBack(self,nothing,nothing2):
        self.StartStage5()

    def DefineWidgets(self,widgetList,layout):
        positionButtonX = 150

        stage1 = []
        stage1.append(self.CreateLabelRanking("Which two of these three items are the most important to you?",110,50,200,130))
        stage1.append(self.CreateButton("Sunny",positionButtonX,180,self.Stage1Function,0,0,120,20))
        stage1.append(self.CreateButton("Beautiful nature", positionButtonX, 230, self.Stage1Function, 1,0,120,20))
        stage1.append(self.CreateButton("Great food", positionButtonX, 280, self.Stage1Function, 2,0,120,20))

        stage2 = []
        stage2.append(self.CreateLabelRanking("",110,50,200,130))
        stage2.append(self.CreateButton("Very important",positionButtonX-15,180,self.Stage2Function,2,0,150,20))
        stage2.append(self.CreateButton("Somewhat important", positionButtonX-15, 230, self.Stage2Function, 1.5,0,150,20))
        stage2.append(self.CreateButton("Less important", positionButtonX-15, 280, self.Stage2Function, 1,0,150,20))
        stage2.append(self.CreateButton("Not important at all",positionButtonX-15,320,self.Stage2Function,0.1,0,150,20))


        stage3 = []
        stage3.append(self.CreateLabelRanking("Which of these is the most important to you?",110,50,200,130))
        for cnt,item in enumerate(finalQuestionsTopic):
            stage3.append(self.CreateButton(item, positionButtonX - 15, 160+(40*cnt), self.Stage3Function, cnt, 0, 150, 20))

        stage4 = []
        stage4.append(self.CreateLabelRanking("",110,50,200,130))
        stage4.append(self.CreateButton("Very important",positionButtonX-15,180,self.Stage4Function,2,0,150,20))
        stage4.append(self.CreateButton("Somewhat important", positionButtonX-15, 230, self.Stage4Function, 1.5,0,150,20))
        stage4.append(self.CreateButton("Less important", positionButtonX-15, 280, self.Stage4Function, 1,0,150,20))
        stage4.append(self.CreateButton("Not important at all",positionButtonX-15,320,self.Stage4Function,0.1,0,150,20))

        stage5 = []
        stage5.append(self.CreateButton("Explain", 10, 460, self.Explain, 0, 0, 80, 20))
        stage5.append(self.CreateButton("Quit", 10, 420, self.Quit, 1,0,80,20))

        stage6 = []
        stage6.append(self.CreateLabelRanking("", 50, 50, 300, 200))
        stage6.append(self.CreateButton("Back", 150, 350, self.GoBack, 1,0,100,20))


        rankings = []

        for i in range(len(self.data.countries)):
            rankings.append(self.CreateLabelRanking("",120,i*22,125,20))
            rankings.append(self.CreateLabelRanking("",250, i * 22, 40, 20))

        widgetList.append(stage1)
        widgetList.append(stage2)
        widgetList.append(stage3)
        widgetList.append(stage4)
        widgetList.append(stage5)
        widgetList.append(stage6)
        widgetList.append(rankings)
        for list in widgetList:
            for cnt,item in enumerate(list):
                layout.addWidget(item,0,cnt)


