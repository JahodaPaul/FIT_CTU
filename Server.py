import socket
import optparse
from Marshalling import *
from Config import *
from FlightSystem import FlightSystem
import random
import time

class Server:
    def __init__(self):
        self.ipAddress = "localhost"
        self.port = 10000
        self.invocation_semantics = AT_LEAST_ONCE
        self.flightSystem = FlightSystem()

        self.LIMIT = 10

        # ([ip,port,request],reply)
        self.cache = [] # store the last LIMIT requests and responses for at-most-once invocation semantics

        self.simulate_loss_of_packets = False

        # list used to keeping track of user who want to monitor seat availability updates of a certain flight
        # [flight id, ip, port, interval]
        self.monitoring = []


        self.time = time.process_time()

    # Function that either updates the monitor interval of the user or
    # indicates that the monitor interval has ended by deleting the entry from the monitoring list
    def CheckMonitoringTimes(self):
        timeNow = time.process_time()
        result = []
        for i in range(len(self.monitoring)):
            if self.monitoring[i][3] > timeNow-self.time:
                result.append([self.monitoring[i][0],self.monitoring[i][1],self.monitoring[i][2],self.monitoring[i][3]-(timeNow-self.time)])

        self.time = time.process_time()
        self.monitoring = result

    # Function used to perform services requested by the user
    # The function performs the services by calling function in FlightSystem class
    def Execute_Reply_Method(self, request, address):
        obj = Unpack(request)
        if obj[0] == 0:
            return obj

        if obj[0] == 1:
            print('Service 1; Search for flight from',obj[2],'to',obj[3])
            result = self.flightSystem.QueryFlightsBySourceAndDest(obj[2],obj[3])
            if result == False:
                return [obj[0],1,ERROR]
            return_result = [obj[0],result[0]]
            for i in range(result[0]):
                return_result.append(INT)
            for i in range(result[0]):
                return_result.append(result[1+i])

            return return_result

        if obj[0] == 2:
            print('Service 2; ID used to query fligths:',obj[2])
            result = self.flightSystem.QueryFlightByID(obj[2])
            if result == False:
                return [obj[0],1,ERROR]
            return [obj[0], 1, FLI, result]

        if obj[0] == 3:
            print('Service 3; User tries to make an reservation of',obj[3],'seats on a flight ID:',obj[2])

            # update the monitor list before sending a seat availability update to users
            self.CheckMonitoringTimes()
            result = self.flightSystem.MakeAnReservation(obj[2],obj[3])
            if result == False:
                return [obj[0],1,ERROR]
            for item in self.monitoring:
                if item[0] == obj[2]:
                    print('Service 4; Sending update to a user',(item[1],item[2]))
                    self.mySocket.sendto(Pack([4,1,FLI,self.flightSystem.QueryFlightByID(obj[2])]), (item[1],item[2]))
            return [obj[0],1,INT,0]

        if obj[0] == 4:
            print('Service 4; User',address,'wants to monitor seats availability on flight with ID',obj[2],'for',obj[3],'seconds')

            self.CheckMonitoringTimes()
            self.monitoring.append([obj[2],address[0],address[1],obj[3]])
            return [obj[0],1,INT,0]

        if obj[0] == 5:
            print('Service 5; User asked to query number of flights')
            result = self.flightSystem.QueryNumberOfFlights()
            print(result)
            return [obj[0],1,INT,result]

        if obj[0] == 6:
            result = self.flightSystem.GiveUsALike()
            print('Service 6; User gave us a like number',result)
            return [obj[0],1,INT,result]

    # At-most-once invocation semantics
    def Reply_To_Request_At_Most_Once(self, request, address):
        # Check for duplicates
        for item in self.cache:
            if item[0] == [address[0],address[1],request]:
                if self.simulate_loss_of_packets and random.randrange(0, 2) == 0:
                    self.mySocket.sendto(Pack(item[1]), address)
                elif self.simulate_loss_of_packets == False:
                    self.mySocket.sendto(Pack(item[1]), address)
                return

        reply = self.Execute_Reply_Method(request, address)

        # Keep the last LIMIT number of request from the client in the cache
        if len(self.cache) == self.LIMIT:
            self.cache = self.cache[1:]
        self.cache.append(([address[0],address[1],request],reply))

        if self.simulate_loss_of_packets and random.randrange(0, 2) == 0:
            self.mySocket.sendto(Pack(reply), address)
        elif self.simulate_loss_of_packets == False:
            self.mySocket.sendto(Pack(reply), address)

    # At-least-once invocation semantics
    def Reply_To_Request_At_Least_Once(self, request, address):
        reply = self.Execute_Reply_Method(request, address)
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
            # Wait for a data from a client
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

        self.Communicate()


parser = optparse.OptionParser()

parser.add_option('-i', '--ip_server',
    action="store", dest="ip",
    help="Set the ip address of the server, where the client sends data to", default="localhost")

parser.add_option('-p', '--port',
    action="store", dest="port",
    help="Set the port number of the server, where the client sends data to", default="10000")

server = Server()

options, args = parser.parse_args()

server.ipAddress = str(options.ip)
server.port = int(options.port)

server.Run()