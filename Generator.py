from Object import Object
import random
import numpy
import math

#generator class with distribution and parameters based on analyzed input data
class Generator(): #TODO create
    def __init__(self):
        self.dummy_return_value = 0

    def Generate_speed(self):
        return numpy.random.normal(120.07209489999991,math.sqrt(81.33522998709363))

    def Generate_station(self):
        return random.randrange(0,20)

    def Generate_position(self):
        return numpy.random.uniform(0,2)

    def Generate_duration(self):
        return numpy.random.exponential(1/0.009104491560429017) + 10.004 #shifting the exponential function

    def Generate_direction(self):
        return random.randrange(0,2)

    def Generate_interArrivalTime(self):
        return numpy.random.exponential(1/0.730024584576294)

    def Generate_next_initiation(self):
        return Object()

    def Generate_next_handover(self,obj):
        return Object()

    def Generate_next_termination(self,obj):
        return Object()