import os
import glob
import flightradar24
import ast
import time
import math
from ShowWorld import ShowWorld
from Show3D import Show3D
from RTree import RTree
from RTreeComponents import Value

# time = time.time()
# airline = 'CSA' # Turkish Airlines
fr = flightradar24.Api()
# flights = fr.get_flights(airline)

#flight_id = 'OK630' # Turkish Airlines' Istanbul - New York flight
#fr = flightradar24.Api()
#flight = fr.get_flight(flight_id)

def f2(arr):
    str1 = str(arr)
    arr2 = str1.split(',')
    for item in arr2:
        if 'status' in item and 'color' in item:#('gray' in item or 'green' in item or 'yellow' in item or 'red' in item):
            print(item)



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
    with open('airlines/'+os.listdir('airlines')[0]) as airlinesFile:
        airlinesList = [ast.literal_eval(line.rstrip()) for line in airlinesFile]

    with open('flights/'+str(time),'a') as myFile:
        for counter,item in enumerate(airlinesList):
            airline = item['ICAO']
            flights = fr.get_flights(airline)
            print('Flights for airline',airline,'were update,',counter,'/',len(airlinesList))
            for key,value in flights.items():
                if (not 'version' in key) and (not 'stats' in key) and (not 'full_count' in key):
                    myFile.write("{}\n".format(value))

def ConvertToXYZ(latInRadians,lonInRadians):
    x = math.sin(math.pi/2-latInRadians) * math.cos(lonInRadians)
    y = math.sin(math.pi/2-latInRadians) * math.sin(lonInRadians)
    z = math.cos(math.pi/2-latInRadians)
    return x,y,z

def ConvertToRadians(latorLon):
    lonOrLatInRadians = latorLon * math.pi / 180
    return lonOrLatInRadians


# default is Prague, distance 2 is whole world
def main(update, showWorld, show3D, latitude = 50.0755381, longitude = 14.4378005, distance = 0.01):
    if not os.path.exists('flights'):
        os.makedirs('flights')

    if not os.path.exists('airports'):
        os.makedirs('airports')

    if not os.path.exists('airlines'):
        os.makedirs('airlines')

    flightDir = os.listdir('flights')
    if update or len(flightDir) == 0:
        airports = fr.get_airports()
        Update(airports,'airports')

        airlines = fr.get_airlines()
        Update(airlines,'airlines')

        UpdateCurrentFlights()

    flightDir = os.listdir('flights')
    flightDir.sort()

    with open('flights/' + flightDir[-1], 'r') as f:
        f = [ast.literal_eval(line.rstrip()) for line in f.readlines()]

    allFlights = []
    for item in f: # 'EZY' in item[-3]:
        allFlights.append(item)

    sequence_containing_x_vals = []
    sequence_containing_y_vals = []
    sequence_containing_z_vals = []

    lats = []
    lons = []
    myTree = RTree(8, 3, 'heuristic')

    for counter, airplane in enumerate(allFlights):
        latInRadians = airplane[1] * math.pi / 180
        lonInRadians = airplane[2] * math.pi / 180
        # lats.append(airplane[1])
        # lons.append(airplane[2])
        x, y, z = ConvertToXYZ(latInRadians, lonInRadians)
        # sequence_containing_x_vals.append(x)
        # sequence_containing_y_vals.append(y)
        # sequence_containing_z_vals.append(z)
        myTree.Insert(Value([x, y, z], counter))

    listOfText = []
    airlineShortcut = {}
    airportShortcut = {}  # countries
    with open('airlines/' + os.listdir('airlines')[0]) as airlinesFile:
        airlinesList = [ast.literal_eval(line.rstrip()) for line in airlinesFile]
        for item in airlinesList:
            airlineShortcut.update({item['ICAO']: item['Name']})

    with open('airports/' + os.listdir('airports')[0]) as airlinesFile:
        airportList = [ast.literal_eval(line.rstrip()) for line in airlinesFile]
        for item in airportList:
            airportShortcut.update({item['iata']: item['country']})

    x, y, z = ConvertToXYZ(ConvertToRadians(latitude), ConvertToRadians(longitude))
    resultL = myTree.SearchCloseKDist(Value([x, y, z], 0), distance)
    resultLons = []
    resultLats = []
    badCounter = 0

    for item in resultL:
        try:
            airplane = allFlights[item.index]
            # print(airplane)
            latInRadians = airplane[1] * math.pi / 180
            lonInRadians = airplane[2] * math.pi / 180
            resultLats.append(airplane[1])
            resultLons.append(airplane[2])

            shortAirline = airplane[-1]
            fromShort = airplane[-8]
            toShort = airplane[-7]
            airplaneType = airplane[8]
            temporaryText = airlineShortcut[shortAirline] + ' flight from ' + airportShortcut[fromShort] + ' to ' + \
                            airportShortcut[toShort] + ' (' + airplaneType + ')'
            listOfText.append(temporaryText)
        except Exception as ex:
            badCounter += 1

    print(100 * badCounter / float(len(resultL)), 'percent error (bad data)')

    if showWorld:
        world = ShowWorld(lats=resultLats, lons=resultLons, text=listOfText)
        world.Show()

    if show3D:
        world3D = Show3D()
        for i in range(len(resultLats)):
            x, y, z = ConvertToXYZ(resultLats[i], resultLons[i])
            sequence_containing_x_vals.append(x)
            sequence_containing_y_vals.append(y)
            sequence_containing_z_vals.append(z)

        world3D.TestShow(sequence_containing_x_vals, sequence_containing_y_vals, sequence_containing_z_vals)




if __name__ == "__main__":
    main(False,True, False) #update, showWorld, show3D, latitude, longitude, distance