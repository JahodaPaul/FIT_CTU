#from Config import *
from HelperFunctions import *
from Robot import Robot

class TCP_Server:
    def __init__(self):
        self.stage = 0
        self.myHash = 0
        self.robot = Robot()
        self.multipleMessages = False

    def Communicate(self,mySocket):
        while True:
            self.robot = Robot()
            data = ''
            counter = 0
            # Wait for a connection
            print('waiting for a connection')
            connection, client_address = mySocket.accept()
            try:
                print('connection from', client_address)

                # Receive the data
                while True:
                    if not self.multipleMessages:
                        data = connection.recv(100)
                        print('Received {!r}'.format(data))
                        temporaryData, cnt = ExtractData(data,connection)
                    if cnt:
                        self.multipleMessages = True
                        data = temporaryData[counter]
                        counter += 1
                        cnt -= 1
                        if not cnt:
                            counter = 0
                            self.multipleMessages = False
                    else:
                        data = temporaryData

                    if self.stage == 0:
                        SERVER_CONFIRMATION, self.myHash = ConfirmationFromServer(data)
                        connection.sendall(SERVER_CONFIRMATION)
                        self.stage += 1
                    elif self.stage == 1:
                        if CompareHashes(int(data),self.myHash):
                            connection.sendall(SERVER_OK)
                            connection.sendall(self.robot.Move(999999,999999))
                            self.stage += 1
                        else:
                            connection.sendall(SERVER_LOGIN_FAILED)
                            self.stage = 0
                            break
                    elif self.stage == 2:
                        if data != '' and data[0] == 'O' and data[1] == 'K' and data[2] == ' ':
                            x, y = ExtractCoordinates(data)
                            connection.sendall(self.robot.Move(x, y))
                        else:
                            if data == '':
                                connection.sendall(self.robot.Move(self.robot.previousCoordinates[0],self.robot.previousCoordinates[1]))
                            else:
                                connection.sendall(SERVER_LOGOUT)
                                self.stage = 0
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
