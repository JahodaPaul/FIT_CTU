# Pavel (Paul) Jahoda

import socket
import sys
from Config import *
from UDP_Communication import UDP_Communication

arguments = []

def EstablishConnection(communication,my_socket, type):
    success = communication.EstablishConnection(type)

    if not success:
        print('Connection not established')
        my_socket.close()
    return success

def main():
    arguments = sys.argv

    #  AF_INET refers to addresses from the internet, IP addresses specifically. SOCK_DGRAM states that we will use UDP
    my_socket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

    ip = UDP_SERVER_IP_ADDRESS if len(arguments) < 2 else arguments[1]
    communication = UDP_Communication(my_socket,ip)


    if len(arguments) < 3: # arguments do not contain path to firmware - user has chosen to download image
        success = EstablishConnection(communication,my_socket,1)

        if not success:
            return

        success = communication.DownloadPicture()

        if not success:
            print('Picture not downloaded')
            my_socket.close()
            return

        print('Success, picture downloaded.')
        my_socket.close()

    else: # Upload firmware
        success = EstablishConnection(communication, my_socket, 2)

        if not success:
            return

        success = communication.UploadFirmware(arguments[2])

        if not success:
            print('firmware not uploaded')
            my_socket.close()
            return

        print('Success, firmware uploaded.')
        my_socket.close()


if __name__ == '__main__':
    main()