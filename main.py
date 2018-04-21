import sys
import socket

SERVER_CONFIRMATION = ''#<16-bitové číslo v decimální notaci>\a\b	#Zpráva s potvrzovacím kódem. Může obsahovat maximálně 5 čísel a ukončovací sekvenci \a\b.
SERVER_MOVE	= '102 MOVE\a\b'	#Příkaz pro pohyb o jedno pole vpřed
SERVER_TURN_LEFT=	'103 TURN LEFT\a\b'	#Příkaz pro otočení doleva
SERVER_TURN_RIGHT=	'104 TURN RIGHT\a\b'	#Příkaz pro otočení doprava
SERVER_PICK_UP=	'105 GET MESSAGE\a\b'	#Příkaz pro vyzvednutí zprávy
SERVER_LOGOUT=	'106 LOGOUT\a\b'	#Příkaz pro ukončení spojení po úspěšném vyzvednutí zprávy
SERVER_OK=	'200 OK\a\b'	#ladné potvrzení
SERVER_LOGIN_FAILED=	'300 LOGIN FAILED\a\b'	#Nezdařená autentizace
SERVER_SYNTAX_ERROR=	'301 SYNTAX ERROR\a\b'	#Chybná syntaxe zprávy
SERVER_LOGIC_ERROR=	'302 LOGIC ERROR\a\b'

KLIENT_KEY = 45328
SERVER_KEY = 54621

stage = 0

myHash = 0

def ExtractData(DataWithAdditionalStuff):
    print(DataWithAdditionalStuff)
    data = ''
    counter = 0
    while True:
        print(DataWithAdditionalStuff[counter],DataWithAdditionalStuff[counter]=='\a')
        if DataWithAdditionalStuff[counter] == '\a' and DataWithAdditionalStuff[counter+1] == '\b':
            return data
        else:
            data += DataWithAdditionalStuff[counter]
            counter += 1

def EncapsulateMessage(data):
    data = str(data)
    data += '\a\b'
    return data

def ConfirmationFromServer(name):
    sum = 0
    for myChar in name:
        sum+=ord(myChar)

    sum *= 1000
    sum += SERVER_KEY
    sum %= 65536
    myHash = sum
    sum = EncapsulateMessage(sum)
    return sum

def CompareHashes(number):
    number += 65536 - KLIENT_KEY
    if number == myHash:
        return True
    return False

def main():
    mySocket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    # Bind the socket to the port
    server_address = ('192.168.1.3', 10000)
    print('starting up on {} port {}'.format(*server_address))
    mySocket.bind(server_address)

    # Listen for incoming connections
    mySocket.listen(1)

    while True:
        # Wait for a connection
        print('waiting for a connection')
        connection, client_address = mySocket.accept()
        try:
            print('connection from', client_address)

            # Receive the data
            while True:
                data = connection.recv(100)
                print('received {!r}'.format(data))
                data = str(data)
                if stage == 0:
                    SERVER_CONFIRMATION = ConfirmationFromServer(ExtractData(data))
                    connection.sendall(SERVER_CONFIRMATION)
                elif stage == 1:
                    temporary = ExtractData(data)
                    temporary = int(temporary)
                    if CompareHashes(temporary):
                        connection.sendall(SERVER_OK)
                    else:
                        connection.sendall(SERVER_LOGIN_FAILED)
                        break
                else:
                    if data:
                        print('sending data back to the client')
                        connection.sendall(data)
                    else:
                        print('no data from', client_address)
                        break

        finally:
            # Clean up the connection
            connection.close()

if __name__ == "__main__":
    main()