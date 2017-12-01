import os
from Data import Data
from operator import itemgetter
import copy
from UI import UI
from tkinter import *
from Fuzzy import Fuzzy

data = Data()
fuzzy = Fuzzy()
# fuzzy.test()
# exit()
# file, name or file array, array of a country, item
# print(data.dataMatrix[0][1][0])

# window = Tk()
# ui = UI(window)
# window.mainloop()

def myPrint(arr):
    temporaryResult = copy.deepcopy(arr)
    temporaryResult.sort(key=itemgetter(0))
    temporaryResult.reverse()
    os.system('clear')
    for i in range(3):
        print(temporaryResult[i][1],":",temporaryResult[i][0])
    print('Worst country for you:',temporaryResult[-1][1],":",temporaryResult[-1][0])
    print('\n')

questionFormat = "How important is it for you that country"


finalQuestionsTopic = ["EDUCATION - 0","INTERNET - 1","ENERGY, RESEARCH AND GOVERNEMTN SPENDING - 2","CARE OF CHILDREN - 3","CAREER - 4","TAXES - 5","OTHER - 6"]

finalQuestions = [
    ["pays it's teachers well?", "has educated population?", "has high tertiary education spending per student?"],  #EDUCATION

    ["has high percentage of people with access to the internet?"], #INTERNET

    ["spends a lot on research and development?", "has low debt to GDP ratio?",
    "has high percentage of it's energy source from renewable sources?", "increased output of its renewable energy sources?"], #ENERGY AND RESEARCH AND GOVERNEMNT SPENDING

    ["has high percentage of vaccinated children?", "has high fertility rate?"],  #CARE OF CHILDREN

    ["has low unemployment rate?", "has low poverty rate?","has low income inequality?","has high average salary?"],  #CAREER

    ["has low tax on personal income","has low tax on property?","has low tax on services?"],  #TAXES

    ["has low number of deaths caused by road accidents?"] #OTHER
]

finalQuestionsReferences = [
    ["TEACHER","POPULATION_WITH","EDUCATION_SPENDING"],

    ["ACCESS"],

    ["RESEARCH","DEBT","RENEWABLE","RENEWABLE"],

    ["VACCINATION","FERTILITY"],

    ["UNEMPLOYMENT","POVERTY","INEQUALITY","AVERAGE_SALARY"],

    ["PERSONAL_INCOME","TAX_ON_PROPERTY","ON_SERVICES"],

    ["ROAD_"]
]

finalQuestionshigherBetter = [
    [1,1,1],

    [1],

    [1,-1,1,1],

    [1,1],

    [-1,-1,-1,1],

    [-1,-1,-1],

    [-1]
]

for i in range(len(finalQuestions)):
    for j in range(len(finalQuestions[i])):
        for dataFromFile in data.dataMatrix:
            if finalQuestionsReferences[i][j] in dataFromFile[0]:
                dataFromFile[1] = data.Normalize(dataFromFile[1])

data.scores = [[0,""] for i in range(len(data.countries))]

fuzzy.startFuzzySystem()
fuzzy.addPointsToMainSystem(data.scores,data.countries)
os.system('clear')
myPrint(data.scores)

counter = 0

while len(finalQuestions)>counter:
    print(questionFormat,finalQuestions[counter][0])
    print("Very important - 1 |","Somewhat important - 2 |","Less important - 3 |","Not important at all - 4")
    answer = input()
    answerInt = -1
    if answer == "1":
        answerInt = 2
    elif answer == "2":
        answerInt = 1.5
    elif answer == "3":
        answerInt = 1
    elif answer == "4":
        answerInt = 0.1
    else:
        continue

    for dataFromFile in data.dataMatrix:
        if finalQuestionsReferences[counter][0] in dataFromFile[0]:
            for country in dataFromFile[1]:
                index = -1
                for tmpCnt, countryName in enumerate(data.countries):
                    if country[0] in countryName or country[0] == countryName:
                        index = tmpCnt
                if finalQuestionshigherBetter[counter][0] == 1:
                    data.scores[index][0] += (float(country[-1])*answerInt)
                else:
                    data.scores[index][0] -= (float(country[-1]) * answerInt)
                data.scores[index][1] = country[0]

    myPrint(data.scores)
    counter += 1

topic = -1

print("Which of these is the most important to you?")
for item in finalQuestionsTopic:
    print(item)
userInput = input()
topic = int(userInput)
os.system('clear')

for i in range(1,len(finalQuestions[topic])):
    print(questionFormat,finalQuestions[topic][i])
    print("Very important - 1 |","Somewhat important - 2 |","Less important - 3 |","Not important at all - 4")
    answer = input()
    answerInt = -1
    if answer == "1":
        answerInt = 2
    elif answer == "2":
        answerInt = 1.5
    elif answer == "3":
        answerInt = 1
    elif answer == "4":
        answerInt = 0.1
    else:
        continue

    for dataFromFile in data.dataMatrix:
        if finalQuestionsReferences[topic][i] in dataFromFile[0]:
            for country in dataFromFile[1]:
                index = -1
                for tmpCnt, countryName in enumerate(data.countries):
                    if country[0] in countryName or country[0] == countryName:
                        index = tmpCnt
                if finalQuestionshigherBetter[topic][i] == 1:
                    data.scores[index][0] += (float(country[-1])*answerInt)
                else:
                    data.scores[index][0] -= (float(country[-1]) * answerInt)
                data.scores[index][1] = country[0]

    myPrint(data.scores)
    counter += 1

myPrint(data.scores)
