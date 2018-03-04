import os
import glob
import flightradar24
import ast
import time
import math
import numpy as np
import random
from ShowWorld import ShowWorld
from Show3D import Show3D


time = time.time()
airline = 'CSA' # Turkish Airlines
fr = flightradar24.Api()
flights = fr.get_flights(airline)
#print(flights)
#print(flights[list(flights)[0]])


#flight_id = 'OK630' # Turkish Airlines' Istanbul - New York flight
#fr = flightradar24.Api()
#flight = fr.get_flight(flight_id)

def f2(arr):
    str1 = str(arr)
    arr2 = str1.split(',')
    for item in arr2:
        if 'status' in item and 'color' in item:#('gray' in item or 'green' in item or 'yellow' in item or 'red' in item):
            print(item)


#f(flight)
#print(flight)
#f2(flight)

#fr = flightradar24.Api()



def Update(arr,what):
    for key, value in arr.items():
        if key == 'version':
            if not os.path.exists(what):
                os.makedirs(what)
            if not os.path.exists('./'+what+'/'+str(value)):
                files = glob.glob('./'+what+'/*')
                for f in files:
                    os.remove(f)
                with open(what+'/'+str(value),'w') as myFile:
                    for item in arr['rows']:
                        myFile.write("{}\n".format(item))

def UpdateCurrentFlights():
    if not os.path.exists('flights'):
        os.makedirs('flights')
    with open('airlines/'+os.listdir('airlines')[0]) as airlinesFile:
        airlinesList = [ast.literal_eval(line.rstrip()) for line in airlinesFile]

    with open('flights/'+str(time),'a') as myFile:
        for counter,item in enumerate(airlinesList):
            airline = item['ICAO']
            flights = fr.get_flights(airline)
            print(counter)
            for key,value in flights.items():
                if (not 'version' in key) and (not 'stats' in key) and (not 'full_count' in key):
                    myFile.write("{}\n".format(value))





airports = fr.get_airports()
Update(airports,'airports')

airlines = fr.get_airlines()
Update(airlines,'airlines')

#UpdateCurrentFlights()



with open('flights/1520002314.082513','r') as f:
    f = [ast.literal_eval(line.rstrip()) for line in f.readlines()]

fromPrague = []
for item in f:
    if 'EZY' in item[-2]:
        fromPrague.append(item)


sequence_containing_x_vals = []
sequence_containing_y_vals = []
sequence_containing_z_vals = []

lats = []
lons = []

for airplane in fromPrague:
    latInRadians = airplane[1] * math.pi / 180
    lonInRadians = airplane[2] * math.pi / 180
    lats.append(airplane[1])
    lons.append(airplane[2])
    sequence_containing_x_vals.append(math.sin(math.pi/2-latInRadians) * math.cos(lonInRadians))
    sequence_containing_y_vals.append(math.sin(math.pi/2-latInRadians) * math.sin(lonInRadians))
    sequence_containing_z_vals.append(math.cos(math.pi/2-latInRadians))




world = ShowWorld(lats=lats,lons=lons)
# world.Show()

world3D = Show3D()
world3D.TestShow(sequence_containing_x_vals,sequence_containing_y_vals,sequence_containing_z_vals)