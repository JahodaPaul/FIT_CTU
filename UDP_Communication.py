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
        self.SequenceNumbers = [-1 for i in range(W//256 + 1)]

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
        while True:
            try:
                # Receive response
                data, server = self.my_socket.recvfrom(4096)
                if not CheckForInvalidPacket(data,self.connectionIdentifier,self.sequenceNumber):
                    return False #TODO sent RST

                

                # Send data
                sent = self.my_socket.sendto(bytes([0, 0, 0, 0, 0, 0, 0, 0, 0 | SYN, type]),(UDP_SERVER_IP_ADDRESS, UDP_SERVER_PORT_NUMBER))
            except socket.timeout as timout:
                print('timeout')
            except Exception as exc:
                if exc != 'timed out':
                    print(exc)
                    return False
