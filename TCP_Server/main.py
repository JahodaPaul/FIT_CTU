import sys
import socket
from TCP_server import TCP_Server

def main():
    myServer = TCP_Server()
    mySocket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    # Bind the socket to the port
    server_address = ('192.168.0.20', 10000)
    print('starting up on {} port {}'.format(*server_address))
    mySocket.bind(server_address)

    # Listen for incoming connections
    mySocket.listen(1)
    # mySocket.setblocking(0)

    myServer.Communicate(mySocket)


if __name__ == "__main__":
    main()