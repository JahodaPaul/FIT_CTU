import os
import sys
import socket
from Communication_UDP import Communication_UDP
from Config import *
import optparse

class Client:
    def __init__(self):
        self.UDP_SERVER_IP_ADDRESS = "localhost" #"127.0.0.1"
        self.UDP_SERVER_PORT_NUMBER = 10000
        self.number_of_likes_given = 0
        self.semantics_invocation = AT_LEAST_ONCE


    def EstablishConnection(self, communication, my_socket):
        success = communication.EstablishConnection()

        if not success:
            print('Connection not established')
            my_socket.close()

        return success

    def Run(self):
        if self.semantics_invocation == AT_LEAST_ONCE:
            print('Invocation semantics used: at least once')
        else:
            print('Invocation semantics used: at most once')

        #  AF_INET refers to addresses from the internet, IP addresses specifically. SOCK_DGRAM states that we will use UDP
        my_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

        communication = Communication_UDP(my_socket, self.UDP_SERVER_IP_ADDRESS, self.UDP_SERVER_PORT_NUMBER, self.semantics_invocation)

        success = self.EstablishConnection(communication, my_socket)
        if success:
            print('Communication successfully established')

        print("Welcome to flight information system.")

        while(1):
            # os.system("clear")
            # print(self.UDP_SERVER_IP_ADDRESS)

            print("Press:\n1 - query flights by source and destination of the flight\n2 - query flights by ID\n"
              "3 - make an reservation\n4 - monitor flight updates\n5 - Check number of flights\n6 - Give a like\n9 - Exit")

            user_choice = input()
            # print(user_choice)
            if user_choice == "1":
                communication.QueryBySourceAndDest('PRG', 'SIN')
            elif user_choice == "2":
                # os.system('clear')
                print('Choose your flight ID:')
                user_id = input()
                communication.QueryByID(int(user_id))
            elif user_choice == "3":
                pass
            elif user_choice == "4":
                pass
            elif user_choice == "5":
                communication.QueryNumberOfFlights()
            elif user_choice == "6":
                communication.GiveLike(self.number_of_likes_given)
                self.number_of_likes_given += 1
            elif user_choice == "9":
                return
            else:
                print("You have entered incorrect request, please write a number between 1 and 6 or number 9")


parser = optparse.OptionParser()

parser.add_option('-i', '--ip_server',
    action="store", dest="ip",
    help="Set the ip address of the server, where the client sends data to", default="localhost")

parser.add_option('-p', '--port',
    action="store", dest="port",
    help="Set the port number of the server, where the client sends data to", default="10000")

parser.add_option('-s', '--semantics_invocation',
    action="store", dest="invo",
    help="Set the semantics invocation used by the client and server", default="1")

options, args = parser.parse_args()

client = Client()

client.UDP_SERVER_IP_ADDRESS = str(options.ip)
client.UDP_SERVER_PORT_NUMBER = int(options.port)
if options.invo == "1":
    client.semantics_invocation = AT_LEAST_ONCE
elif options.invo == "2":
    client.semantics_invocation = AT_MOST_ONCE

client.Run()