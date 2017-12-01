import os

class Data:
    def __init__(self):
        self.countries = []
        self.scores = []
        self.directoryOFFiles = "./ZNS_DATA"

        self.dataMatrix = []
        self.indexOfCountry = []
        self.indexOfValue = []

        self.OpenFiles()
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