import socket
from threading import Thread
from Marshalling import *
from Config import *
from FlightSystem import FlightSystem
import random


class Server:
    def __init__(self):
        self.ipAddress = "localhost" #"127.0.0.1"
        self.port = 10000
        self.invocation_semantics = AT_LEAST_ONCE
        self.flightSystem = FlightSystem()

        self.LIMIT = 10
        #([ip,port,request],reply)
        self.cache = [] # store the last LIMIT requests and responses for at-most-once invocation semantics

        self.simulate_loss_of_packets = True

        self.Run()

    def Execute_Reply_Method(self, request):
        obj = Unpack(request)
        if obj[0] == 0:
            return obj
        if obj[0] == 2:#TODO
            print('Service 2; ID used to query fligths:',obj[2])
            result = self.flightSystem.QueryFlightByID(obj[2])
            if result == False:
                return [obj[0],1,ERROR]
            return [obj[0], 1, FLI, result]
        if obj[0] == 5:
            print('Service 5; User asked to query number of flights')
            result = self.flightSystem.QueryNumberOfFlights()
            print(result)
            return [obj[0],1,INT,result]
        if obj[0] == 6:
            result = self.flightSystem.GiveUsALike()
            print('Service 6; User gave us a like number',result)
            return [obj[0],1,INT,result]

    def Reply_To_Request_At_Most_Once(self, request, address):
        for item in self.cache:
            if item[0] == [address[0],address[1],request]:
                if self.simulate_loss_of_packets and random.randrange(0, 2) == 0:
                    self.mySocket.sendto(Pack(item[1]), address)
                elif self.simulate_loss_of_packets == False:
                    self.mySocket.sendto(Pack(item[1]), address)
                return

        reply = self.Execute_Reply_Method(request)
        if len(self.cache) == self.LIMIT:
            self.cache = self.cache[1:]
        self.cache.append(([address[0],address[1],request],reply))

        if self.simulate_loss_of_packets and random.randrange(0, 2) == 0:
            self.mySocket.sendto(Pack(reply), address)
        elif self.simulate_loss_of_packets == False:
            self.mySocket.sendto(Pack(reply), address)

    def Reply_To_Request_At_Least_Once(self, request, address):
        reply = self.Execute_Reply_Method(request)
        print(reply)
        # Send data
        if self.simulate_loss_of_packets and random.randrange(0, 2) == 0:
            self.mySocket.sendto(Pack(reply), address)
        elif self.simulate_loss_of_packets == False:
            self.mySocket.sendto(Pack(reply), address)

    def Reply_To_Request(self,request, address):

        if len(request) > 1 and request[0] == 0 and request[1] == AT_MOST_ONCE:
            self.invocation_semantics = AT_MOST_ONCE
            print('Starting using At-most-once invocation semantics')
        elif len(request) > 1 and request[0] == 0 and request[1] == AT_LEAST_ONCE:
            self.invocation_semantics = AT_LEAST_ONCE
            print('Starting using At-least-once invocation semantics')

        if self.invocation_semantics == AT_LEAST_ONCE:
            self.Reply_To_Request_At_Least_Once(request,address)
        else:
            self.Reply_To_Request_At_Most_Once(request,address)

    def Communicate(self):
        while True:
            # Wait for a connection
            print('waiting for data')
            data, address = self.mySocket.recvfrom(4096)
            print('Received data from address:',address)
            print('Received {!r}'.format(data))
            self.Reply_To_Request(data,address)


    def Run(self):
        # AF_INET refers to addresses from the internet, IP addresses specifically. SOCK_DGRAM states that we will use UDP
        self.mySocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

        # Bind the socket to the port
        server_address = (self.ipAddress, self.port)
        print('starting up on {} port {}'.format(*server_address))
        self.mySocket.bind(server_address)

        # Listen for incoming connections
        # self.mySocket.listen(1)
        # mySocket.setblocking(0)

        self.Communicate()

server = Server()