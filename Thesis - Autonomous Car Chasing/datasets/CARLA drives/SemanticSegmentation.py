import numpy as np
import math

class SemanticSegmentation:
    def __init__(self):
        pass

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