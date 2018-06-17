# Pavel (Paul) Jahoda

import math
from Config import *

def ConvertBytesToNumber(array):
    resultNumber = 0
    for counter, number in enumerate(array):
        resultNumber += ( number * int(math.pow(256,len(array)-counter-1)) )
    return resultNumber

def ConvertNumberIntoArrayOfBytes(number,nofBytes):
    resultList = []
    for i in range(nofBytes):
        resultList.append(number%256)
        number = number//256

    resultList = resultList[::-1]
    return resultList

def CheckForInvalidPacket(data, identifier, sequenceNumber):
    if data:
        if identifier != -1 and ConvertBytesToNumber([data[0],data[1],data[2],data[3]]) != identifier:
            return False
        if data[8] == RST:
            return False
        if data[8] == SYN and (len(data) != 10 or data[9] != 1 or data[9] != 2):
            return False
        if data[8] | SYN & 7 == 7 or data[8] | RST & 7 == 7 or data[8] | FIN & 7 == 7: # vice priznaku najednou
            return False
        if data[8] & FIN and len(data) >= 10:
            return False
        #TODO check for invalid sequence number (consider overflow)

        return True
    return True


def IsNotInTheSequence(sequence,number):
    for item in sequence:
        if item[0] == number:
            return False
    return True


def OverFlowDiff(firstNumber,secondNumber):
    return secondNumber - firstNumber if secondNumber >= firstNumber else 65536-firstNumber+secondNumber

def CreatePacket(connectionIdentifier,sequenceNumber,flag,confirmationNumber = 0):
    packet = []
    packet.extend(ConvertNumberIntoArrayOfBytes(connectionIdentifier, 4))
    packet.extend(ConvertNumberIntoArrayOfBytes(confirmationNumber, 2))
    packet.extend(ConvertNumberIntoArrayOfBytes(sequenceNumber, 2))
    packet.extend(ConvertNumberIntoArrayOfBytes(flag, 1))
    return packet

def HowManyWaitingForConfirmation(array):
    counter = 0
    for item in array:
        if item[0] != -1:
            counter += 1
    return counter