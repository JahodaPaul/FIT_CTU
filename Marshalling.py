import math
from Flight import Flight
from DateTime import DateTime
from Config import *

# packed object is list of objects; index 0: service ID, index 1: number of objects (n),
# index 2 to (1+n): type of each object, rest of indexes: objects
def Pack(obj):
    packed = []

    if obj[0] == 0:
        packed = Pack_Initial_Sequence()
    else:
        packed.append(obj[0])
        n_of_objects = obj[1]
        print(n_of_objects)
        packed.append(n_of_objects)

        for i in range(2,2+n_of_objects):
            packed.append(obj[i])
            if obj[i] == INT:
                packed.extend(Pack_int(obj[n_of_objects+i]))
            elif obj[i] == STR:
                packed.extend(Pack_string(obj[n_of_objects+i]))
            elif obj[i] == DATE:
                packed.extend(Pack_datetime(obj[n_of_objects+i]))
            elif obj[i] == FP:
                packed.extend(Pack_floating_point(obj[n_of_objects+i]))
            elif obj[i] == FLI:
                packed.extend(Pack_Flight(obj[n_of_objects+i]))

    print(packed)
    return bytes(packed)

def Unpack(obj):
    if obj[0] == 0:
        return Unpack_Initial_Sequence()
    else:
        unpacked = []
        unpacked.append(obj[0])
        n_of_objects = obj[1]
        unpacked.append(n_of_objects)
        currentIndex = 2
        print(obj)
        for i in range(n_of_objects):
            length_of_current_object = obj[currentIndex + 1] + 1
            print(length_of_current_object)
            if obj[currentIndex] == INT:
                unpacked.append(Unpack_int(obj[currentIndex + 1:currentIndex+length_of_current_object]))
            elif obj[currentIndex] == STR:
                unpacked.append(Unpack_string(obj[currentIndex + 1:currentIndex + length_of_current_object]))
            elif obj[currentIndex] == DATE:
                unpacked.append(Unpack_datetime(obj[currentIndex + 1:currentIndex + length_of_current_object]))
            elif obj[currentIndex] == FP:
                unpacked.append(Unpack_floating_point(obj[currentIndex + 1:currentIndex + length_of_current_object]))
            elif obj[currentIndex] == FLI:
                unpacked.append(Unpack_Flight(obj[currentIndex+1:currentIndex + length_of_current_object]))

            currentIndex += length_of_current_object
    return unpacked

def Pack_Initial_Sequence():
    return [0]

def Unpack_Initial_Sequence():
    return [0]

def Pack_int(number):
    resultList = []
    for i in range(4):
        resultList.append(number % 256)
        number = number // 256

    resultList.append(4+1)
    resultList = resultList[::-1]
    return resultList


def Unpack_int(obj):
    length_of_int = obj[0]
    resultNumber = 0
    for i in range(1,length_of_int):
        resultNumber += (obj[i] * int(math.pow(256, len(obj) - i - 1)))

    return resultNumber

def Pack_string(obj):
    arr = [0 for i in range(len(obj)+1)]
    arr[0] = len(obj) + 1
    for i in range(len(obj)):
        arr[i+1] = ord(obj[i])
    return arr

def Unpack_string(obj):
    length_of_string = obj[0]
    str = ''
    for i in range(1,length_of_string):
        str += chr(obj[i])
    return str

def Pack_datetime(obj):
    str = obj.Get_string()
    return Pack_string(str)

def Unpack_datetime(obj):
    str = Unpack_string(obj)
    return DateTime(str)

def Pack_floating_point(obj):#TODO implement packing of floating points
    return Pack_int(obj)

def Unpack_floating_point(obj):#TODO implement unpacking of floating points
    return Unpack_int(obj)

# id, source, destination, departure_time, airfare, number_of_seats_available
def Pack_Flight(obj):
    arr = []
    arr += Pack_int(obj.iD)
    arr += Pack_string(obj.source)
    arr += Pack_string(obj.destination)
    arr += Pack_datetime(obj.departure_time)
    arr += Pack_floating_point(obj.airfare)
    arr += Pack_int(obj.number_of_seats_available)

    return [len(arr) + 1] + arr

def Unpack_Flight(obj):
    current = 1

    id = Unpack_int(obj[current:obj[current]+current])
    current += obj[current]

    source = Unpack_string(obj[current:obj[current]+current])
    current += obj[current]

    destination = Unpack_string(obj[current:obj[current]+current])
    current += obj[current]

    departure_time = Unpack_datetime(obj[current:obj[current]+current])
    current += obj[current]

    airfare = Unpack_floating_point(obj[current:obj[current]+current])
    current += obj[current]

    number_of_seats_available = Unpack_int(obj[current:obj[current]+current])
    current += obj[current]

    return Flight(id,source,destination,departure_time,airfare,number_of_seats_available)