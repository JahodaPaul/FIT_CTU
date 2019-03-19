import os
import sys
import socket
from Communication_UDP import Communication_UDP

class Client:
    def __init__(self):
        self.UDP_SERVER_IP_ADDRESS = "localhost" #"127.0.0.1"
        self.UDP_SERVER_PORT_NUMBER = 10000


    def EstablishConnection(self, communication, my_socket):
        success = communication.EstablishConnection()

        if not success:
            print('Connection not established')
            my_socket.close()

        return success

    def Run(self):
        self.UDP_SERVER_IP_ADDRESS = self.UDP_SERVER_IP_ADDRESS if len(sys.argv) < 2 else sys.argv[1]
        self.UDP_SERVER_PORT_NUMBER = self.UDP_SERVER_PORT_NUMBER if len(sys.argv) < 3 else sys.argv[2]

        #  AF_INET refers to addresses from the internet, IP addresses specifically. SOCK_DGRAM states that we will use UDP
        my_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

        communication = Communication_UDP(my_socket, self.UDP_SERVER_IP_ADDRESS, self.UDP_SERVER_PORT_NUMBER)

        success = self.EstablishConnection(communication, my_socket)


        while(1):
            # os.system("clear")
            # print(self.UDP_SERVER_IP_ADDRESS)
            print("Welcome to flight information system.")
            print("Press:\n1 - query flights by source and destination of the flight\n2 - query flights by ID\n"
              "3 - make an reservation\n4 - monitor flight updates\n5 - Exit")

            user_choice = input()
            print(user_choice)
            if user_choice == "1":
                pass
            elif user_choice == "2":
                pass
            elif user_choice == "3":
                pass
            elif user_choice == "4":
                pass
            elif user_choice == "5":
                return
            else:
                print("You have entered incorrect request, please write a number between 1 and 5")

client = Client()
client.Run()