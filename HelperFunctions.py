from Config import *

def ExtractData(DataWithAdditionalStuff,connection):
    DataWithAdditionalStuff = DataWithAdditionalStuff.decode('utf-8')
    print(DataWithAdditionalStuff)
    data = ''
    if DataWithAdditionalStuff == '':
        return data,0
    counter = 0
    while DataWithAdditionalStuff[len(DataWithAdditionalStuff) - 2] != '\a' and DataWithAdditionalStuff[len(DataWithAdditionalStuff) - 1] != '\b':
        tmp = connection.recv(100)
        tmp = tmp.decode('utf-8')
        DataWithAdditionalStuff += tmp
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
    sum = 0
    for myChar in name:
        sum+=ord(myChar)

    sum *= 1000
    myHash = sum%65536
    sum += SERVER_KEY
    sum %= 65536
    sum = EncapsulateMessage(sum)
    return sum, myHash

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
