# Pavel (Paul) Jahoda

import socket
from Config import *
from HelperFunctions import *
from copy import deepcopy

# identifikátor 'spojení'	4B
# sekvenční číslo	        2B
# číslo potvrzení	        2B
# příznak	data            1B
# data				        0-255B

class UDP_Communication:
    def __init__(self,socket,ip):
        self.connectionIdentifier = -1
        self.my_socket = socket
        self.my_socket.settimeout(0.1)

        self.WBytes = [0 for i in range(W)]
        self.SequenceNumbers = [[-1] for i in range(W//255 + (W%255 > 0) )]

        self.sequenceNumber = 0

        self.ipAddress = ip

        self.waitingForConfimation = [[-1] for i in range(W//255 + (W%255 > 0) )]

    def EstablishConnection(self,type): #not a TCP connection
        while True:
            try:
                # Send data
                self.my_socket.sendto(bytes([0, 0, 0, 0, 0, 0, 0, 0, 0 | SYN, type]),(self.ipAddress, UDP_SERVER_PORT_NUMBER))

                # Receive response
                data, server = self.my_socket.recvfrom(4096)
                if data and data[8] == SYN:
                    self.connectionIdentifier = ConvertBytesToNumber([data[0],data[1],data[2],data[3]])
                    print('Connection established')
                    return True
                if type == 1 and not CheckForInvalidPacket(data,self.connectionIdentifier,self.sequenceNumber):
                    return False

            except socket.timeout as timout:
                print('timeout')
            except Exception as exc:
                if exc != 'timed out':
                    print(exc)
                    return False

    def AddSequenceRange(self,fromNumber,toNumber):
        for counter, item in enumerate(self.SequenceNumbers):
            if item == [-1]:
                self.SequenceNumbers[counter] = [fromNumber, toNumber%65536]
                break

    def DownloadPicture(self):
        with open('resultPhoto.png','wb') as photoFile:
            while True:
                try:
                    # Receive response
                    data, server = self.my_socket.recvfrom(4096)
                    if not CheckForInvalidPacket(data,self.connectionIdentifier,self.sequenceNumber):
                        packet = CreatePacket(self.connectionIdentifier,self.sequenceNumber,RST)
                        self.my_socket.sendto(bytes(packet),(self.ipAddress, UDP_SERVER_PORT_NUMBER)) # send maybe more than once
                        return False

                    currentSequenceNumber = ConvertBytesToNumber([data[4], data[5]])
                    length = len(data) - 9
                    print('Received',currentSequenceNumber)
                    # print(self.SequenceNumbers)

                    # Received data you need, check by how much you can move sliding window
                    if currentSequenceNumber == self.sequenceNumber:
                        if int(data[8] == FIN):
                            return True

                        for i in range(9,len(data)):
                            self.WBytes[i-9] = int(data[i])

                        self.AddSequenceRange(currentSequenceNumber,currentSequenceNumber+length)

                        self.SequenceNumbers.sort()
                        newSequenceNumber = self.sequenceNumber
                        for i in range(2):
                            for counter, item in enumerate(self.SequenceNumbers):
                                if item[0] == newSequenceNumber:
                                    myRange = OverFlowDiff(item[0],item[1])
                                    for j in range(myRange):
                                        tmp = j+ OverFlowDiff(self.sequenceNumber,item[0])
                                        photoFile.write(bytes([self.WBytes[tmp]]))
                                    newSequenceNumber = item[1]
                                    self.SequenceNumbers[counter] = [-1]
                            if counter+1 != len(self.SequenceNumbers):
                                break

                        #move sliding window
                        tmpDiff = OverFlowDiff(self.sequenceNumber,newSequenceNumber)
                        for i in range(tmpDiff,W):
                            self.WBytes[i-tmpDiff] = self.WBytes[i]
                        self.sequenceNumber = newSequenceNumber

                    else: #store data for later use

                        #to solve overflow
                        tmp = currentSequenceNumber+65536 if currentSequenceNumber+65536-self.sequenceNumber <= (W-255) else currentSequenceNumber

                        if tmp > self.sequenceNumber and tmp <= self.sequenceNumber + (W-255) and IsNotInTheSequence(self.SequenceNumbers,currentSequenceNumber):
                            tmpDiff = OverFlowDiff(self.sequenceNumber,currentSequenceNumber)
                            for i in range(tmpDiff,tmpDiff+length):
                                self.WBytes[i] = int(data[i - tmpDiff + 9])
                            self.AddSequenceRange(currentSequenceNumber,currentSequenceNumber+length)


                    packet = CreatePacket(self.connectionIdentifier,self.sequenceNumber,0)

                    print('Sending confirmation of sequence number:',self.sequenceNumber)
                    # Send data
                    self.my_socket.sendto(bytes(packet),(self.ipAddress, UDP_SERVER_PORT_NUMBER))
                except socket.timeout as timout:
                    print('timeout')
                except Exception as exc:
                    if exc != 'timed out':
                        print(exc)
                        return False

    def UploadFirmware(self, pathToFirmware):
        currentCounter = 0
        whenRead = 0

        with open(pathToFirmware,'rb') as firmwareFile:
            while True:
                try:

                    sendSomething = False
                    while HowManyWaitingForConfirmation(self.waitingForConfimation) != W//255 + (W%255 > 0):
                        byte = firmwareFile.read(255)
                        print(len(byte))
                        whenRead += 1

                        if len(byte) == 0:
                            print('End of firmware file.')
                            if HowManyWaitingForConfirmation(self.waitingForConfimation) == 0:
                                packet = CreatePacket(self.connectionIdentifier, 0, FIN, currentCounter)
                                self.my_socket.sendto(bytes(packet), (self.ipAddress, UDP_SERVER_PORT_NUMBER))  # send maybe more than once
                                return True
                            break

                        sendSomething = True

                        dataToSend = []
                        # write it into waiting for confirmation array
                        for i in range(len(self.waitingForConfimation)):
                            if self.waitingForConfimation[i][0] == -1:
                                self.waitingForConfimation[i][0] = whenRead
                                self.waitingForConfimation[i].append(currentCounter)
                                for j in range(len(byte)):
                                    self.waitingForConfimation[i].append(int(byte[j]))

                                dataToSend = deepcopy(self.waitingForConfimation[i])
                                break

                        if dataToSend == []:
                            print('problem')

                        for item in self.waitingForConfimation:
                            if len(item) >= 2:
                                print(item[0],item [1], len(item))
                            else:
                                print(item[0], len(item))

                        # send data
                        packet = CreatePacket(self.connectionIdentifier, 0, 0,confirmationNumber=currentCounter)
                        for i in range(2,len(dataToSend)):
                            packet.append(dataToSend[i])

                        print('Send', currentCounter, len(packet))
                        self.my_socket.sendto(bytes(packet), (self.ipAddress, UDP_SERVER_PORT_NUMBER))
                        currentCounter = (currentCounter+ len(byte) ) % 65536

                    # send something waiting for confirmation
                    if not sendSomething:
                        self.waitingForConfimation.sort()
                        for i in range(len(self.waitingForConfimation)):
                            if self.waitingForConfimation[i][0] != -1:
                                packet = CreatePacket(self.connectionIdentifier, 0, 0,confirmationNumber=self.waitingForConfimation[i][1])
                                print('Send again', self.waitingForConfimation[i][1])
                                for j in range(2, len(self.waitingForConfimation[i])):
                                    packet.append(self.waitingForConfimation[i][j])
                                self.my_socket.sendto(bytes(packet), (self.ipAddress, UDP_SERVER_PORT_NUMBER))
                                break #TODO maybe leave this out


                    # Receive data
                    data, server = self.my_socket.recvfrom(4096)
                    # if not CheckForInvalidPacket(data,self.connectionIdentifier,self.sequenceNumber):
                    #     packet = CreatePacket(self.connectionIdentifier,self.sequenceNumber,RST)
                    #     self.my_socket.sendto(bytes(packet),(self.ipAddress, UDP_SERVER_PORT_NUMBER)) # send maybe more than once
                    #     return False

                    confirmationNumber = ConvertBytesToNumber([data[6],data[7]])
                    print('Received confirmation', confirmationNumber)
                    for i in range(len(self.waitingForConfimation)):
                        if self.waitingForConfimation[i][0] != -1:
                            if self.waitingForConfimation[i][1] < confirmationNumber or \
                                    (confirmationNumber < W and W+self.waitingForConfimation[i][1] > 65535):
                                self.waitingForConfimation[i] = [-1]

                except socket.timeout as timeout:
                    print('timeout')
                # except Exception as exc:
                #     if exc != 'timed out':
                #         print(exc)
                #         return False
