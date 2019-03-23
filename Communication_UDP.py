import socket
from Marshalling import *
from DateTime import DateTime
from Flight import Flight

class Communication_UDP:
    def __init__(self, socket, ip, port):
        self.my_socket = socket
        self.ipAddress = ip
        self.port = port

    def EstablishConnection(self):
        while True:
            try:
                # Send data
                str = 'neco'
                intt = 14
                let = Flight(20,'rim','Praha',DateTime('cas'),400,100)
                # [1,3,INT,STR,FLI,intt,str,let]
                self.my_socket.sendto(Pack([1,5,INT,FLI,STR,INT,FLI,intt,let,str,intt,let]), (self.ipAddress, self.port))

                # Receive response
                data, server = self.my_socket.recvfrom(4096)
                if data and data[8] == SYN:
                    self.connectionIdentifier = ConvertBytesToNumber([data[0], data[1], data[2], data[3]])
                    print('Connection established')
                    return True
                if type == 1 and not CheckForInvalidPacket(data, self.connectionIdentifier, self.sequenceNumber):
                    return False

            except socket.timeout as timeout:
                print('timeout')
            except Exception as exc:
                if exc != 'timed out':
                    print(exc)

        return False