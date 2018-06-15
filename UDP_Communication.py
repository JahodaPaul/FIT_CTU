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
    def __init__(self,socket):
        self.connectionIdentifier = -1
        self.my_socket = socket
        self.my_socket.settimeout(0.1)

        self.WBytes = [0 for i in range(W)]
        self.SequenceNumbers = [[-1] for i in range(W//255 + (W%255 > 0) )]

        self.sequenceNumber = 0

    def EstablishConnection(self,type): #not a TCP connection
        while True:
            try:
                # Send data
                sent = self.my_socket.sendto(bytes([0, 0, 0, 0, 0, 0, 0, 0, 0 | SYN, type]),(UDP_SERVER_IP_ADDRESS, UDP_SERVER_PORT_NUMBER))

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


    def DownloadPicture(self):
        with open('resultPhoto.png','ab') as photoFile:
            while True:
                try:
                    # Receive response
                    data, server = self.my_socket.recvfrom(4096)
                    if not CheckForInvalidPacket(data,self.connectionIdentifier,self.sequenceNumber):
                        return False #TODO sent RST

                    currentSequenceNumber = ConvertBytesToNumber([data[4], data[5]])
                    length = len(data) - 9
                    print('Received',currentSequenceNumber)

                    # Received data you need, check by how much you can move sliding window
                    if currentSequenceNumber == self.sequenceNumber:
                        for i in range(9,len(data)):
                            self.WBytes[i-9] = int(data[i])
                            #photoFile.write(data[i])

                        for i in range(len(self.SequenceNumbers)):
                            if self.SequenceNumbers[i] == [-1]:
                                self.SequenceNumbers[i] = [currentSequenceNumber,currentSequenceNumber+length]
                                break

                        self.SequenceNumbers.sort()
                        newSequenceNumber = self.sequenceNumber
                        for counter, item in enumerate(self.SequenceNumbers):
                            if item[0] == newSequenceNumber:
                                for j in range(item[0]-self.sequenceNumber,item[1]-self.sequenceNumber):
                                    photoFile.write(bytes([self.WBytes[j]]))
                                newSequenceNumber = item[1]
                                self.SequenceNumbers[counter] = [-1]

                        #move sliding window
                        for i in range(newSequenceNumber-self.sequenceNumber,W):
                            self.WBytes[i-(newSequenceNumber-self.sequenceNumber)] = self.WBytes[i]
                        self.sequenceNumber = newSequenceNumber

                    else: #store data for later use
                        #TODO solve overflow
                        if currentSequenceNumber > self.sequenceNumber and currentSequenceNumber <= self.sequenceNumber + (W-255):
                            for i in range(currentSequenceNumber-self.sequenceNumber,currentSequenceNumber-self.sequenceNumber+length):
                                self.WBytes[i] = int(data[i - (currentSequenceNumber-self.sequenceNumber) + 9])
                            for counter, item in enumerate(self.SequenceNumbers):
                                if item == [-1]:
                                    self.SequenceNumbers[counter] = [currentSequenceNumber,currentSequenceNumber+length]
                                    break


                    arrayToSend = []
                    arrayToSend.extend(ConvertNumberIntoArrayOfBytes(self.connectionIdentifier,4))
                    arrayToSend.extend(ConvertNumberIntoArrayOfBytes(0,2))
                    arrayToSend.extend(ConvertNumberIntoArrayOfBytes(self.sequenceNumber,2))
                    arrayToSend.extend(ConvertNumberIntoArrayOfBytes(0,1))

                    print('Sending confirmation of sequence number:',self.sequenceNumber)
                    # Send data
                    sent = self.my_socket.sendto(bytes(arrayToSend),(UDP_SERVER_IP_ADDRESS, UDP_SERVER_PORT_NUMBER))
                except socket.timeout as timout:
                    print('timeout')
                except Exception as exc:
                    if exc != 'timed out':
                        print(exc)
                        return False
