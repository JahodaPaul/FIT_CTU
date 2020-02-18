import numpy as np

class SemanticSegmentation:
    def __init__(self):
        self.counter = 0

    def IsThereACarInThePicture(self,segmImage):
        array = np.frombuffer(segmImage.raw_data, dtype=np.dtype("uint8"))
        array = np.reshape(array, (segmImage.height, segmImage.width, 4))
        for i in range(0,segmImage.height,30):
            for j in range(0,segmImage.width,30):
                if array[i][j][2] == 10:
                    return True

        for i in range(0,segmImage.height,10):
            for j in range(0,segmImage.width,2):
                if array[i][j][2] == 10:
                    return True
        return False

    def ObjectInFrontOfChasedCar(self, segmImage, bbox):
        if self.counter > 30:
            if len(bbox) != 0:
                xCoordTo = (int(bbox[1, 0]) + int(bbox[2, 0])) // 2
                yCoordTo = int(bbox[1, 1])
                print('using bbox')
            else:
                xCoordTo = segmImage.width//2
                yCoordTo = segmImage.height//2

            # print(segmImage.raw_data)
            array = np.frombuffer(segmImage.raw_data, dtype=np.dtype("uint8"))
            array = np.reshape(array, (segmImage.height, segmImage.width, 4))
            # carDetected = False
            for i in range(segmImage.height - yCoordTo):
                if array[segmImage.height-i-1][xCoordTo][2] == 10:
                    # carDetected = True
                    # print('CAR DETECTED')
                    return False, ''
                elif array[segmImage.height-i-1][xCoordTo][2] == 1 or array[segmImage.height-i-1][xCoordTo][2] == 2 or array[segmImage.height-i-1][xCoordTo][2] == 4 or \
                        array[segmImage.height-i-1][xCoordTo][2] == 11 or array[segmImage.height-i-1][xCoordTo][2] == 12:
                    print('BUILDING, CAREFUL')
                    for j in range(segmImage.width//2-1):
                        if array[segmImage.height-i-1][xCoordTo+j][2] != 1 and array[segmImage.height-i-1][xCoordTo+j][2] != 2 and array[segmImage.height-i-1][xCoordTo+j][2] != 4 and \
                                array[segmImage.height-i-1][xCoordTo+j][2] != 11 and array[segmImage.height-i-1][xCoordTo+j][2] != 12:
                            print('GO RIGHT')
                            return True, 'RIGHT'
                        elif array[segmImage.height-i-1][xCoordTo-1][2] != 1 and array[segmImage.height-i-1][xCoordTo-1][2] != 2 and array[segmImage.height-i-1][xCoordTo-1][2] != 4 and \
                                array[segmImage.height-i-1][xCoordTo-1][2] != 11 and array[segmImage.height-i-1][xCoordTo-1][2] != 12:
                            print('GO LEFT')
                            return True, 'LEFT'
        else:
            self.counter += 1
        return False, ''
                # return True
                # break
        # print('TEEEST',array[0][400][2])