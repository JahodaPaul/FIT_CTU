import socket
import sys

UDP_SERVER_IP_ADDRESS = "127.0.0.1"
UDP_SERVER_PORT_NUMBER = 10000

arguments = []

def main():
    arguments = sys.argv
    print(arguments)

    #  AF_INET refers to addresses from the internet, IP addresses specifically. SOCK_DGRAM states that we will use UDP
    my_socket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

    try:
        # Send data
        sent = my_socket.sendto("MESSAGE", UDP_SERVER_IP_ADDRESS)

        # Receive response
        data, server = my_socket.recvfrom(4096)
    except Exception as exc:
        pass

if __name__ == '__main__':
    main()