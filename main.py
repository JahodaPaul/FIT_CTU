# Pavel (Paul) Jahoda

import socket
import sys
from Config import *
from UDP_Communication import UDP_Communication

arguments = []

def main():
    arguments = sys.argv
    print(arguments)

    #  AF_INET refers to addresses from the internet, IP addresses specifically. SOCK_DGRAM states that we will use UDP
    my_socket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

    communication = UDP_Communication(my_socket)

    success = communication.EstablishConnection(1)

    if not success:
        print('Connection not established')
        return

    success = communication.DownloadPicture()

    if not success:
        print('Picture not downloaded')
        return


if __name__ == '__main__':
    main()