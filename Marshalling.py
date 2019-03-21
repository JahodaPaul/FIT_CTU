# 0 - initial sequence
# 1 - int
# 2 - string
# 3 - date-time
# 4 - floating point
# 5 - flight

import math
from Flight import Flight
from DateTime import DateTime

def Pack(obj):
    packed = None
    if obj is None:
        packed = Pack_Initial_Sequence(obj)
    elif type(obj) is int:
        packed = Pack_int(obj)
    elif type(obj) is str:
        packed = Pack_string(obj)
    elif type(obj) is DateTime:
        packed = Pack_datetime(obj)
    elif type(obj) is float:
        packed = Pack_floating_point(obj)
    elif type(obj) is Flight:
        packed = Pack_Flight(obj)

    return bytes(packed)

def Unpack(obj):
    if obj[0] == 0:
        return Unpack_Initial_Sequence(obj[1:])
    elif obj[0] == 1:
        return Unpack_int(obj[1:])
    elif obj[0] == 2:
        return Unpack_string(obj[1:])
    elif obj[0] == 3:
        return Unpack_datetime(obj[1:])
    elif obj[0] == 4:
        return Unpack_floating_point(obj[1:])
    elif obj[0] == 5:
        return Unpack_Flight(obj[1:])


def Pack_Initial_Sequence(obj):
    return [0]

def Unpack_Initial_Sequence(obj):
    return None

def Pack_int(number):
    resultList = []
    for i in range(4):
        resultList.append(number % 256)
        number = number // 256

    resultList.append(1)
    resultList = resultList[::-1]
    return resultList


def Unpack_int(obj):
    resultNumber = 0
    for counter, number in enumerate(obj):
        resultNumber += (number * int(math.pow(256, len(obj) - counter - 1)))

    return resultNumber

def Pack_string(obj):
    arr = [0 for i in range(len(obj)+1)]
    arr[0] = len(obj) + 1
    for i in range(len(obj)):
        arr[i+1] = ord(obj[i])
    return [2] + arr

def Unpack_string(obj):
    print(obj)
    length_of_string = obj[0]
    str = ''
    for i in range(1,length_of_string):
        str += chr(obj[i])
    return str

def Pack_datetime(obj):
    str = obj.Get_string()
    return [3] + Pack_string(str)[1:]

def Unpack_datetime(obj):
    str = Unpack_string(obj)
    return DateTime(str)

def Pack_floating_point(obj):#TODO implement packing of floating points
    return [4] + Pack_int(obj)[1:]

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

    return [5] + [len(arr) + 1] + arr

def Unpack_Flight(obj):
    print(obj)
    current = 1
    id = Unpack(obj[current:5+current])
    current += 5
    source = Unpack(obj[current:obj[current+1]+current+1])
    current += obj[current+1] + 1
    destination = Unpack(obj[current:obj[current+1]+current+1])
    current += obj[current+1] + 1
    departure_time = Unpack(obj[current:obj[current+1]+current+1])
    current += obj[current+1] + 1
    airfare = Unpack(obj[current:5+current])
    current += 5
    number_of_seats_available = Unpack(obj[current:5+current])
    current += 5
    return Flight(id,source,destination,departure_time,airfare,number_of_seats_available)