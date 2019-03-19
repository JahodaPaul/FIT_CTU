# 0 - initial sequence
# 1 - int
# 2 - string
# 3 - date-time
# 4 - floating point
# 5 - flight

import math

def Pack(obj):
    if type(obj) is int:
        return Pack_int(obj)
    elif type(obj) is str:
        pass

def Unpack(obj):
    if obj[0] == 1:
        return Unpack_int(obj[1:])


def Pack_int(number):
    resultList = []
    for i in range(4):
        resultList.append(number % 256)
        number = number // 256

    resultList.append(1)
    resultList = resultList[::-1]
    return bytes(resultList)


def Unpack_int(obj):
    resultNumber = 0
    for counter, number in enumerate(obj):
        resultNumber += (number * int(math.pow(256, len(obj) - counter - 1)))

    return resultNumber