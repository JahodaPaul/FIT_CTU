from Config import *

def ExtractData(DataWithAdditionalStuff,connection,stage,treasureMessage):
    DataWithAdditionalStuff = DataWithAdditionalStuff.decode('utf-8')
    data = ''
    if DataWithAdditionalStuff == '':
        return data,0
    counter = 0
    while DataWithAdditionalStuff[len(DataWithAdditionalStuff) - 2] != '\a' or DataWithAdditionalStuff[len(DataWithAdditionalStuff) - 1] != '\b':
        if '\a\b' not in DataWithAdditionalStuff and not CheckOnlyLength(DataWithAdditionalStuff,stage,treasureMessage):
            return DataWithAdditionalStuff, 0
        if '\0' in DataWithAdditionalStuff:
            break
        connection.settimeout(1)
        tmp = connection.recv(1000)
        tmp = tmp.decode('utf-8')
        DataWithAdditionalStuff += tmp
    if DataWithAdditionalStuff[len(DataWithAdditionalStuff) - 2] != '\a' or DataWithAdditionalStuff[len(DataWithAdditionalStuff) - 1] != '\b':
        return ['2','youreallydontwannaknowwhatthisdoestrustme'], 2

    while True:
        if DataWithAdditionalStuff[counter] == '\a' and DataWithAdditionalStuff[counter+1] == '\b':
            if counter == len(DataWithAdditionalStuff) - 2:
                return data,0
            else:#multiple messages
                data = [data]
                anotherData = ''
                counter += 2
                while True:
                    if DataWithAdditionalStuff[counter] == '\a' and DataWithAdditionalStuff[counter + 1] == '\b':
                        if counter == len(DataWithAdditionalStuff) - 2:
                            data.append(anotherData)
                            return data,len(data)
                        else:
                            data.append(anotherData)
                            counter += 2
                            anotherData = ''
                    else:
                        anotherData += DataWithAdditionalStuff[counter]
                        counter += 1
        else:
            data += DataWithAdditionalStuff[counter]
            counter += 1

def EncapsulateMessage(data):
    data = str(data)
    data += '\a\b'
    data = data.encode('utf-8')
    return data

def ConfirmationFromServer(name):
    mySum = 0
    for myChar in name:
        mySum+=ord(myChar)

    mySum *= 1000
    myHash = mySum%65536
    mySum += SERVER_KEY
    mySum %= 65536
    mySum = EncapsulateMessage(mySum)
    return mySum, myHash

def CompareHashes(number,hash):
    number += 65536 - KLIENT_KEY
    number %= 65536
    if number == hash:
        return True
    return False

def ExtractCoordinates(data):
    x = 0
    y = 0
    tmp = data.split(' ')
    x = int(tmp[1])
    y = int(tmp[2])
    return x,y


def CheckOnlyLength(data,stage,treasureMessage):
    myLen = len(data)
    if myLen and data[myLen-1] == '\a':
        myLen -= 1
    if 'RECHARGING' in data or 'FULL POWER' in data:
        return myLen <= CLIENT_RECHARGING_LEN
    if stage == 1:
        return myLen <= CLIENT_CONFIRMATION_LEN
    else:
        if data == '':
            return True
        if stage == 0:
            return myLen <= CLIENT_USERNAME_LEN
        if stage == 2 and not treasureMessage:
            return myLen <= CLIENT_OK_LEN
        return myLen <= CLIENT_MESSAGE_LEN

def CheckLengthAndSyntax(data,stage,treasureMessage):
    if 'RECHARGING' in data or 'FULL POWER' in data:
        return len(data) <= CLIENT_RECHARGING_LEN
    if stage == 1:
        if len(data) <= CLIENT_CONFIRMATION_LEN:
            return not (' ' in data)
        return len(data) <= CLIENT_CONFIRMATION_LEN
    else:
        if data == '':
            return True
        if stage == 0:
            return len(data) <= CLIENT_USERNAME_LEN
        if stage == 2 and not treasureMessage:
            if len(data) <= CLIENT_OK_LEN:
                try:
                    if not (data[0] == 'O' and data[1] == 'K' and data[2] == ' '):
                        return False
                    tmp = data.split(' ')
                    tmp[1] = int(tmp[1])
                    tmp[2] = int(tmp[2])
                    a = tmp[0] + ' ' + str(tmp[1]) + ' ' + str(tmp[2])
                    if a != data:
                        return False
                except Exception as ex:
                    return False
            return len(data) <= CLIENT_OK_LEN
        return len(data) <= CLIENT_MESSAGE_LEN