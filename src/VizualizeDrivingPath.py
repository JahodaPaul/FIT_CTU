import math
import pickle
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.patches as mpatches

class VizualizeDrivingPath:
    def __init__(self):
        self.speedsChasing = []
        self.filePathChasing = 'chasingLog.p'
        self.speedsChased = []
        self.filePathChased = 'chasedLog.p'
        self.distances = []
        self.filePathDistances = 'distancesLog.p'
        self.angles = []
        self.filePathAngles = 'anglesLog.p'
        self.counter = 0


    def Add(self, velocity3DChasing, velocity3DChased, distance, angleBetweenTwoCars):
        speed1 = 3.6 * math.sqrt(velocity3DChasing.x*velocity3DChasing.x + velocity3DChasing.y*velocity3DChasing.y + velocity3DChasing.z * velocity3DChasing.z)
        speed2 = 3.6 * math.sqrt(velocity3DChased.x*velocity3DChased.x + velocity3DChased.y*velocity3DChased.y + velocity3DChased.z * velocity3DChased.z)

        self.speedsChasing.append(speed1)
        self.speedsChased.append(speed2)

        self.distances.append(distance)
        self.angles.append(angleBetweenTwoCars)
        self.counter += 1
        if self.counter % 200 == 0:
            self.Save()

    def Save(self):
        pickle.dump( self.speedsChasing, open(self.filePathChasing, "wb" ) )
        pickle.dump( self.speedsChased, open(self.filePathChased, "wb" ) )
        pickle.dump( self.distances, open(self.filePathDistances, "wb" ) )
        pickle.dump( self.angles, open(self.filePathAngles, "wb" ) )

    def Load(self):
        self.speedsChasing = pickle.load(open( self.filePathChasing, "rb" ))
        self.speedsChased = pickle.load(open( self.filePathChased, "rb" ))
        self.distances = pickle.load(open( self.filePathDistances, "rb" ))
        self.angles = pickle.load(open( self.filePathAngles, "rb" ))

    def ShowSpeeds(self):
        plt.rc('axes', titlesize=20)
        plt.rc('axes', labelsize=18)
        X = np.arange(len(self.speedsChasing[45:]))

        plt.plot(X,self.speedsChasing[45:],color='green')
        plt.plot(X,self.speedsChased[45:],color='blue')
        plt.xlabel('Frame number')
        plt.ylabel('Speed km/h')
        plt.title('Speeds of both vehicles in time')
        patchesList = []
        patchesList.append(mpatches.Patch(color='green', label='Chasing car'))
        patchesList.append(mpatches.Patch(color='blue', label='Chased car'))
        plt.legend(handles=patchesList)
        plt.show()

    def ShowDistances(self):
        plt.rc('axes', titlesize=20)
        plt.rc('axes', labelsize=18)
        X = np.arange(len(self.speedsChasing[45:]))

        plt.plot(X,self.distances[45:],color='green')
        plt.xlabel('Frame number')
        plt.ylabel('Distances between cars in meters')
        plt.title('Distances between cars in time')
        plt.show()

    def ShowAngles(self):
        plt.rc('axes', titlesize=20)
        plt.rc('axes', labelsize=18)
        X = np.arange(len(self.speedsChasing[45:]))

        plt.plot(X,self.angles[45:],color='green')
        plt.xlabel('Frame number')
        plt.ylabel('Angles between cars in degrees')
        plt.title('Angles between cars in time')
        plt.show()

# tmp = VizualizeDrivingPath()
# tmp.Load()
# tmp.ShowSpeeds()
# tmp.ShowDistances()
# tmp.ShowAngles()
