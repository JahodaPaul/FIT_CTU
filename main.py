# Pavel (Paul) Jahoda

import socket
import sys
from Config import *
from UDP_Communication import UDP_Communication

arguments = []

def main():
    arguments = sys.argv

    #  AF_INET refers to addresses from the internet, IP addresses specifically. SOCK_DGRAM states that we will use UDP
    my_socket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

    ip = UDP_SERVER_IP_ADDRESS if len(arguments) < 2 else arguments[1]
    communication = UDP_Communication(my_socket,ip)

    success = communication.EstablishConnection(1)

    if not success:
        print('Connection not established')
        my_socket.close()
        return

    success = communication.DownloadPicture()

    if not success:
        print('Picture not downloaded')
        my_socket.close()
        return

    print('Success, picture downloaded.')
    my_socket.close()


if __name__ == '__main__':
    main()