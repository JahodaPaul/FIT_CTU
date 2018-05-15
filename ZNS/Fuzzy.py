import os

class Fuzzy:
    def __init__(self):
        self.countries = ['"ESP"', '"GRC"', '"HUN"', '"FRA"', '"ISR"', '"CAN"', '"DNK"', '"LUX"', '"LVA"', '"CZE"',
                          '"NOR"', '"DEU"', '"NLD"', '"AUT"', '"POL"', '"ITA"', '"SVN"', '"SWE"', '"FIN"', '"USA"',
                          '"AUS"', '"PRT"']
        self.scores = [0 for i in range(len(self.countries))]

        # 0 - sunny; 1 - beautiful nature; 2 - great food
        self.fuzzyMatrix = [
            [0.9, 0.9, 0.45, 0.5, 1, 0.5, 0.1, 0.55, 0.2, 0.4,
                          0.3, 0.4, 0.3, 0.6, 0.3, 0.85, 0.5, 0.25, 0.25, 0.5,
                          0.95, 0.95],
            [0.9, 0.8, 0.6, 0.7, 0.4, 1, 0.4, 0.7, 0.2, 0.65,
             0.8, 0.6, 0.2, 0.8, 0.5, 0.75, 0.6, 0.7, 0.7, 0.6,
             1, 0.8],
            [1, 1, 0.7, 0.8, 0.8, 0.5, 0.3, 0.4, 0.3, 0.5,
                          0.3, 0.7, 0.3, 0.6, 0.4, 1, 0.45, 0.3, 0.3, 0.5,
                          0.6, 0.85]
        ]

    def startFuzzySystem(self,selectedArr):
        for i in range(len(self.countries)):
            self.scores[i] = self.fuzzyMatrix[selectedArr[0]][i] if self.fuzzyMatrix[selectedArr[0]][i] < self.fuzzyMatrix[selectedArr[1]][i] else self.fuzzyMatrix[selectedArr[1]][i]

        for i in range(len(self.scores)):
            self.scores[i] *= 2
            self.scores[i] = self.scores[i] * self.scores[i] #concentration


    # points, name of country
    def addPointsToMainSystem(self,arr,countries):
        for i in range(len(countries)):
            arr[i][1] = countries[i]

        for i in range(len(countries)):
            for j in range(len(self.countries)):
                if self.countries[j] == countries[i]:
                    arr[i][0] = self.scores[j]