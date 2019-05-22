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
        dur = numpy.random.exponential(1/0.009104491560429017) + 10.004
        return dur #shifting the exponential function

    def Generate_direction(self):
        if random.randrange(0,2) == 0:
            return 'RIGHT'
        return 'LEFT'

    def Generate_interArrivalTime(self):
        return numpy.random.exponential(1/0.730024584576294)

    def Generate_Obj(self):
        station = self.Generate_station()
        return Object(self.Generate_duration(),self.Generate_speed(),station,self.Generate_position()+station*2,self.Generate_direction())

    def CalculateHowLongTillNextEvent(self,obj):
        if obj.direction == 'RIGHT':
            kmTillNextEvent = (obj.position // 2)*2 + 2 - obj.position
        else:
            kmTillNextEvent = abs((obj.position // 2)*2 - obj.position)
            if kmTillNextEvent == 0:
                kmTillNextEvent = 2

        return kmTillNextEvent/obj.speed * 3600 # in seconds

    def NextPosition(self,obj):
        if obj.direction == 'RIGHT':
            kmTillNextEvent = (obj.position // 2)*2 + 2 - obj.position
        else:
            kmTillNextEvent = abs((obj.position // 2)*2 - obj.position)
            if kmTillNextEvent == 0:
                kmTillNextEvent = 2

        if obj.direction == 'RIGHT':
            obj.position += kmTillNextEvent
            obj.station += 1
        else:
            obj.position -= kmTillNextEvent
            obj.station -= 1

    def Generate_next_initiation(self):
        return [self.Generate_interArrivalTime(),0,self.Generate_Obj()]

    def Generate_next_handover(self,obj):
        time_untill_next_handover = self.CalculateHowLongTillNextEvent(obj)
        self.NextPosition(obj)
        if obj.duration == min(time_untill_next_handover,obj.duration):
            return [obj.duration,2,obj]

        obj.duration -= time_untill_next_handover
        return [time_untill_next_handover,1,obj]

    def Generate_next_termination(self,obj):
        time_untill_termination = self.CalculateHowLongTillNextEvent(obj)
        self.NextPosition(obj)
        if obj.duration == min(time_untill_termination,obj.duration):
            return [obj.duration,2,obj]

        obj.duration -= time_untill_termination
        return [time_untill_termination,2,obj]