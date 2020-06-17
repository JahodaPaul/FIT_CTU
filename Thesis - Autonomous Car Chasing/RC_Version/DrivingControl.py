import numpy as np

class DrivingControl:
    def __init__(self, optimalDistance):
        self.prevDist = 0
        self.distChange = 0
        self.throttle = 0


        self.P_mult = 0.25
        self.I_mult = 0#1/3000.0
        self.D_mult = 0.07
        self.errorsArr = np.array([],dtype=float)
        self.optimalDist = optimalDistance
        self.prevError = 0
        self.distChange = 0

    def PredictSteerAndThrottle(self, distance, angleBetweenCars, secondCarAngle=0):
        steer = angleBetweenCars/180.0
        # print('ANGLE',angleBetweenCars)
        # print('STEER',steer)
        # throttle = self.GHRAcceleration(distance)
        # if self.distChange > 0 or distance > 10:
        #     self.throttle = min(1,self.throttle + 0.1)
        # elif self.distChange < 0 or distance < 10:
        #     self.throttle = max(0, self.throttle - 0.1)

        self.distChange = distance - self.prevDist
        self.prevDist = distance
        # print('THROTTLE',self.throttle)
        self.throttle = self.PID(distance)

        return steer, self.throttle

    def PID(self, distance):
        error = (distance-self.optimalDist)
        # if error < 0:
        #     error *= 5
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

