#from Config import *
from HelperFunctions import *
from Robot import Robot
import socket
from threading import Thread


class TCP_Server:
    def __init__(self):
        # stage = 0
        # myHash = 0
        # robot = Robot()
        # multipleMessages = False
        # recharge = False
        self.listOfThreads = []

    def Communicate(self,mySocket):
        while True:

            # Wait for a connection
            print('waiting for a connection')
            connection, client_address = mySocket.accept()
            connection.settimeout(1)
            t1 = Thread(target = self.CommunicateSingleThread, args = (mySocket,connection,client_address))
            t1.start()
            self.listOfThreads.append(t1)
    
    
    def CommunicateSingleThread(self,mySocket,connection,client_address):
        myHash = 0
        stage = 0
        recharge = False
        multipleMessages = False
        robot = Robot()
        data = ''
        counter = 0
        cnt = 0
        try:
            print('connection from', client_address)

            # Receive the data
            while True:
                if not multipleMessages:
                    data = connection.recv(1000)
                    print('Received {!r}'.format(data))
                    temporaryData, cnt = ExtractData(data, connection, stage,
                                                     robot.previouslyPickedUpTreasure)
                if cnt:
                    multipleMessages = True
                    data = temporaryData[counter]
                    counter += 1
                    cnt -= 1
                    if not cnt:
                        counter = 0
                        multipleMessages = False
                else:
                    data = temporaryData

                if data == SERVER_SYNTAX_ERROR or not CheckLengthAndSyntax(data, stage,
                                                                           robot.previouslyPickedUpTreasure):
                    connection.sendall(SERVER_SYNTAX_ERROR)
                    counter = 0
                    multipleMessages = False
                    cnt = 0
                    stage = 0
                    break

                if data == 'RECHARGING':
                    connection.settimeout(5)
                    recharge = True
                    continue
                if data == 'FULL POWER':
                    recharge = False
                    connection.settimeout(1)
                    continue

                if recharge:
                    connection.sendall(SERVER_LOGIC_ERROR)
                    counter = 0
                    multipleMessages = False
                    cnt = 0
                    stage = 0
                    recharge = False
                    break

                if stage == 0:
                    SERVER_CONFIRMATION, myHash = ConfirmationFromServer(data)
                    connection.sendall(SERVER_CONFIRMATION)
                    stage += 1
                elif stage == 1:
                    if CompareHashes(int(data), myHash):
                        connection.sendall(SERVER_OK)
                        connection.sendall(robot.Move(999999, 999999))
                        stage += 1
                    else:
                        connection.sendall(SERVER_LOGIN_FAILED)
                        stage = 0
                        break
                elif stage == 2:
                    if data != '' and data[0] == 'O' and data[1] == 'K' and data[2] == ' ':
                        x, y = ExtractCoordinates(data)
                        connection.sendall(robot.Move(x, y))
                    else:
                        if data == '':
                            connection.sendall(
                                robot.Move(robot.previousCoordinates[0], robot.previousCoordinates[1]))
                        else:
                            connection.sendall(SERVER_LOGOUT)
                            stage = 0
                            break
                else:
                    if data:
                        print('sending data back to the client')
                        connection.sendall(data)
                    else:
                        print('no data from', client_address)
                        break
        except socket.timeout:
            print('Caught timeout')
            counter = 0
            multipleMessages = False
            cnt = 0
            stage = 0
            recharge = False
        finally:
            # Clean up the connection
            connection.close()