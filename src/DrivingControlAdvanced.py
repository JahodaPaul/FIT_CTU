import numpy as np

class DrivingControlAdvanced:
    def __init__(self, optimalDistance,P=0.1,I=0,D=1):
        self.prevDist = 0
        self.distChange = 0
        self.throttle = 0


        self.P_mult = 0.1
        self.I_mult = 0
        self.D_mult = 1
        self.errorsArr = np.array([],dtype=float)
        self.optimalDist = optimalDistance
        self.prevError = 0
        self.distChange = 0

    # goLeftOrRightObj indicates that an object is between the chasing and the chased car and that the chasing car should take different direction
    def PredictSteerAndThrottle(self, distance, angleBetweenCars, secondCarAngle, goLeftOrRightObj=''):
        if goLeftOrRightObj != '':
            if goLeftOrRightObj == 'LEFT':
                steer = -0.1 # random value
            else:
                steer = 0.1 # random value
        else:
            steer = angleBetweenCars/180.0
        self.distChange = distance - self.prevDist
        self.prevDist = distance
        self.throttle = self.PID(distance)

        return steer, self.throttle

    def PID(self, distance):
        error = (distance-self.optimalDist)
        self.errorsArr = np.append(self.errorsArr,error)
        self.errorsArr = self.errorsArr[-300:]


        self.distChange = distance - self.prevDist
        self.prevDist = distance
        P = error*self.P_mult
        I = np.sum(self.errorsArr)*self.I_mult
        D = (error-self.prevError) * self.D_mult
        self.prevError = error
        # print(P,I,D)
        return max(min(P + I + D,1.0),0.0)

