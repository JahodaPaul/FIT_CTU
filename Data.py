import os
from Config import *
import copy
from operator import itemgetter

class Data:
    def __init__(self):
        self.countries = []
        self.scores = [] #points, name of country
        self.directoryOFFiles = "./ZNS_DATA"

        self.dataMatrix = []
        self.indexOfCountry = []
        self.indexOfValue = []

        self.OpenFiles()
        self.dataMatrix = self.GetScoresOverTime(self.dataMatrix)
        pass

    def OpenFiles(self):
        cnt = 0
        indexFile = -1
        for file in os.listdir(self.directoryOFFiles):
            indexFile+=1
            cnt += 1
            tmpCountries = []
            if os.path.isdir(self.directoryOFFiles+'/'+file):
                indexFile-=1
                continue
            with open(self.directoryOFFiles+'/'+file,'r') as f:
                lines = f.read().splitlines()

            items = lines[0].split(',')

            for counter,item in enumerate(items):
                if "LOCATION" in item:
                    self.indexOfCountry.append(counter)
                if "Value" in item:
                    self.indexOfValue.append(counter)

            for counter,line in enumerate(lines):
                if counter != 0:
                    items = line.split(',')
                    for counter2, item in enumerate(items):
                        if counter2 == self.indexOfCountry[indexFile]:
                            if cnt == 1:
                                self.countries.append(item)
                            tmpCountries.append(item)

            self.countries = list(set(self.countries).intersection(tmpCountries))
        indexFile=0
        for file in os.listdir(self.directoryOFFiles):
            if not os.path.isdir(self.directoryOFFiles+'/'+file):
                self.dataMatrix.append(self.ProcessFile(file,indexFile=indexFile))
                indexFile+=1


    def ProcessFile(self,name,indexFile):
        returnValue = []
        returnValue.append(name)

        returnList = [[] for i in range(len(self.countries))]
        free = 0

        with open(self.directoryOFFiles + '/' + name, 'r') as f:
            lines = f.read().splitlines()

        for counter,line in enumerate(lines):
            if counter != 0:
                items = line.split(',')

                tmp = -1
                b = False
                for counter2, item in enumerate(items):
                    if counter2 == self.indexOfCountry[indexFile]:
                        for counter3, country in enumerate(returnList):
                            if len(country) != 0 and item in country[0]:
                                tmp = counter3
                                b = True
                                break
                        if not b and item in self.countries:
                            returnList[free].append(item)
                            tmp = free
                            free += 1
                    if counter2 == self.indexOfValue[indexFile] and tmp != -1:
                        returnList[tmp].append(item)

        returnValue.append(returnList)
        return returnValue

    # if we have values 10 5 0; and 2 1 0; both will be normalized to 1 0.5 0
    def Normalize(self,arr):
        max = 0
        for country in arr:
            if country[-1] == '':
                country[-1] = '0'
            if float(country[-1]) >= max:
                max = float(country[-1])

        for country in arr:
            country[-1] = str(float(country[-1])/max)

        return arr

    def GetScoresOverTime(self,matrix):
        expandedPart = []
        for dataFromFile in matrix:
            array = []
            array.append(dataFromFile[0]+'_OVER_THE_YEARS')
            arr2 = []
            for country in dataFromFile[1]:
                countryAndScore = []
                if len(country) > 2:
                    countryAndScore.append(country[0])
                    #get score that indicates how much has the value grown over last 5 years
                    if len(country) <= 6:
                        countryAndScore.append(float(country[-1]) - float(country[1]))
                        arr2.append(countryAndScore)
                    else:
                        countryAndScore.append(float(country[-1]) - float(country[-6]))
                        arr2.append(countryAndScore)
            array.append(arr2)

            if len(array) > 1:
                expandedPart.append(array)
        matrix.extend(expandedPart)
        return matrix

    def AddPointsToMainSystem(self,matrix,firstIndex,secondIndex,weight,scores,countries):
        if "OVER_THE_YEARS" in finalQuestionsReferences[firstIndex][secondIndex]:
            firstPart = ''
            cnt = 0
            while finalQuestionsReferences[firstIndex][secondIndex][cnt] != ';':
                firstPart += finalQuestionsReferences[firstIndex][secondIndex][cnt]
                cnt += 1
            for dataFromFile in matrix:
                if firstPart in dataFromFile[0] and "OVER_THE_YEARS" in dataFromFile[0]:
                    for country in dataFromFile[1]:
                        index = -1
                        for tmpCnt, countryName in enumerate(countries):
                            if country[0] in countryName or country[0] == countryName:
                                index = tmpCnt
                        if finalQuestionshigherBetter[firstIndex][secondIndex] == 1:
                            scores[index][0] += (float(country[-1]) * weight)
                        else:
                            scores[index][0] -= (float(country[-1]) * weight)
                        scores[index][1] = country[0]
        else:
            for dataFromFile in matrix:
                if finalQuestionsReferences[firstIndex][secondIndex] in dataFromFile[0]:
                    for country in dataFromFile[1]:
                        index = -1
                        for tmpCnt, countryName in enumerate(countries):
                            if country[0] in countryName or country[0] == countryName:
                                index = tmpCnt
                        if finalQuestionshigherBetter[firstIndex][secondIndex] == 1:
                            scores[index][0] += (float(country[-1]) * weight)
                        else:
                            scores[index][0] -= (float(country[-1]) * weight)
                        scores[index][1] = country[0]

        return scores

    def ReturnFirstCountryBasedOnPoints(self,scores):
        temporaryResult = copy.deepcopy(scores)
        temporaryResult.sort(key=itemgetter(0))
        temporaryResult.reverse()

        return temporaryResult[0][1]

    def ReturnIndex(self,number):
        myList = { 0 : 0, 0.1 : 4, 1 : 3, 1.5 : 2, 2 : 1}
        return myList[number]

    def ProcessHistoryData(self,historyOfWeights, historyOfScores):
        #first, find indexes of top2 countries by their scores
        maximum = -1000
        maximumIndex = -1
        secondMax = -1000
        secondMaxIndex = -1
        for i in range(len(historyOfScores[-1])):
            if historyOfScores[-1][i][0] > maximum:
                maximum = historyOfScores[-1][i][0]
                maximumIndex = i

        for i in range(len(historyOfScores[-1])):
            if i != maximumIndex and historyOfScores[-1][i][0] > secondMax:
                secondMax = historyOfScores[-1][i][0]
                secondMaxIndex = i
        #list of list - [scoreOfFirstCountry,scoreOfSecondCountry]
        returnArr = [ [0,0] for i in range(5)]

        for i in range(len(historyOfScores)):
            if i == 0:
                returnArr[self.ReturnIndex(historyOfWeights[i])][0] += historyOfScores[i][maximumIndex][0]
                returnArr[self.ReturnIndex(historyOfWeights[i])][1] += historyOfScores[i][secondMaxIndex][0]
            else:
                returnArr[self.ReturnIndex(historyOfWeights[i])][0] += historyOfScores[i][maximumIndex][0] - historyOfScores[i-1][maximumIndex][0]
                returnArr[self.ReturnIndex(historyOfWeights[i])][1] += historyOfScores[i][secondMaxIndex][0] - historyOfScores[i-1][secondMaxIndex][0]

        returnArr.append([ historyOfScores[-1][maximumIndex][1],historyOfScores[-1][secondMaxIndex][1]  ])

        return returnArr
