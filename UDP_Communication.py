# Pavel (Paul) Jahoda

import socket
from Config import *
from HelperFunctions import *

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
