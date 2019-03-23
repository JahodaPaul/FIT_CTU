import socket
from threading import Thread
from Marshalling import *


class Server:
    def __init__(self):
        self.address = "localhost" #"127.0.0.1"
        self.port = 10000
        self.Run()

        self.cache = [] # store the 10 last requests and responses for at-most-once invocation semantics

    def Communicate(self):
        while True:
            # Wait for a connection
            print('waiting for a connection')
            data, address = self.mySocket.recvfrom(4096)
            print('Received {!r}'.format(data))
            print(Unpack(data))

            #connection, client_address = self.mySocket.accept()
            #connection.settimeout(1)
            print("NEW CONNECTION'")
            # t1 = Thread(target=self.CommunicateSingleThread, args=(mySocket, connection, client_address))
            # t1.start()

            # self.listOfThreads.append(t1)

    def Run(self):
        # AF_INET refers to addresses from the internet, IP addresses specifically. SOCK_DGRAM states that we will use UDP
        self.mySocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        # Bind the socket to the port
        server_address = (self.address, self.port)
        print('starting up on {} port {}'.format(*server_address))
        self.mySocket.bind(server_address)

        # Listen for incoming connections
        # self.mySocket.listen(1)
        # mySocket.setblocking(0)

        self.Communicate()

server = Server()