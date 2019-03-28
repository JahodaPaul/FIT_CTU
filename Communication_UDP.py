import socket
from Marshalling import *
from DateTime import DateTime
from Flight import Flight
from Config import *
import random
import time

# Class used to send request from the client to the server
# Marshall the data before sending the requests
class Communication_UDP:
    def __init__(self, socket, ip, port, invocation_semantics):
        self.my_socket = socket
        self.ipAddress = ip
        self.port = port
        self.my_socket.settimeout(1)
        self.invocation_semantics = invocation_semantics

        self.simulate_loss_of_packets = False

    def EstablishConnection(self):
        if self.Send([0,self.invocation_semantics]) != False:
            return True
        return False

    def QueryByID(self,id):
        item = self.Send([2,1,INT,id])
        if item != False:
            item = Unpack(item)
            print(item[2].Get_printable_string())
        else:
            print('ERROR MESSAGE: There is no flight with ID:',str(id))

    def QueryNumberOfFlights(self):
        item = self.Send([5,0])
        if item != False:
            item = Unpack(item)
            print('Number of flight currently in the system:',item[2])
        else:
            print("ERROR MESSAGE: There are curently no flights")

    def GiveLike(self, n_of_likes_user_has_given):
        item = self.Send([6,1,INT,n_of_likes_user_has_given])
        if item != False:
            item = Unpack(item)
            print('You have given a like number',item[2])

    def QueryBySourceAndDest(self,source,dest):
        item = self.Send([1,2,STR,STR,source,dest])
        if item != False:
            item = Unpack(item)
            print('There are',item[1],'flights from',source,'to',dest)
            printable_result = 'These flights have ID numbers:'
            for i in range(item[1]):
                printable_result += (' '+str(item[2+i]))
            print(printable_result)
        else:
            print('There are no flight from',source,'to',dest)

    def MakeAReservation(self, flightID, numberOfSeatsToReserve):
        item = self.Send([3,2,INT,INT,flightID,numberOfSeatsToReserve])
        if item != False:
            print('Reservation successfully made')
        else:
            print('Unable to perform reservation')

    def MonitorFlightUpdate(self,flightID,interval):
        self.CallBack([4,2,INT,INT,flightID,interval],interval)


    def CheckResponse(self, request, reply):
        if len(reply) >= 3 and reply[2] == ERROR:
            return False
        return True

    def CheckSendingMessage(self,message):
        return True

    def CallBack(self, message, interval):
        # First, register the callback on the server
        start = self.Send(message)
        start_time = time.process_time()

        # Wait for the updates for the interval duration
        while True:
            try:
                self.my_socket.settimeout(interval)
                data, server = self.my_socket.recvfrom(4096)
                print('New seat availability:\n',Unpack(data)[2].Get_printable_string())

                # If we receive update, reduce the interval timeout for the socket
                # Continue receiving updates from the server until the time interval passed
                time_now = time.process_time()
                interval -= (time_now - start_time)
            except socket.timeout as timeout:
                self.my_socket.settimeout(1) # set the interval back after monitoring is done
                break
        print('Stopped listening for flight updates')

    # Function that sending the request and waits for response from the server
    # If it doesn't receive any data for a duration used as a socket timeout,
    # it retransmits the request again
    def Send(self, message):
        if not self.CheckSendingMessage(message):
            return False

        while True:
            try:
                # Send data
                if self.simulate_loss_of_packets and random.randrange(0, 2) == 0:
                    self.my_socket.sendto(Pack(message), (self.ipAddress, self.port))
                elif self.simulate_loss_of_packets == False:
                    self.my_socket.sendto(Pack(message), (self.ipAddress, self.port))
                # Receive response
                data, server = self.my_socket.recvfrom(4096)
                if self.CheckResponse(message,data):
                    return data
                else:
                    return False

            except socket.timeout as timeout:
                print('timeout')
            except Exception as exc:
                if exc != socket.timeout:
                    print(exc)