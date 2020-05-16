import os
import requests
from zipfile import ZipFile


class DownloadData:
    def __init__(self):
        pass

    def get_confirm_token(self,response):
        for key, value in response.cookies.items():
            if key.startswith('download_warning'):
                return value

        return None

    def save_response_content(self,response, destination):
        CHUNK_SIZE = 32768

        with open(destination, "wb") as f:
            for chunk in response.iter_content(CHUNK_SIZE):
                if chunk:  # filter out keep-alive new chunks
                    f.write(chunk)

    def DownloadDirectory(self,id,destination):
        URL = "https://docs.google.com/uc?export=download"

        if os.path.exists(destination.split('.')[0]):
            print('Files exist')
            return

        session = requests.Session()

        response = session.get(URL, params={'id': id}, stream=True)
        token = self.get_confirm_token(response)

        if token:
            params = {'id': id, 'confirm': token}
            response = session.get(URL, params=params, stream=True)

        self.save_response_content(response, destination)

        print('Done downloading',destination)
        print('Extracting')

        # Create a ZipFile Object and load sample.zip in it
        with ZipFile(destination, 'r') as zipObj:
            # Extract all the contents of zip file in current directory
            zipObj.extractall(destination.split('/')[0])

        os.remove(destination)

        print('Done extracting')


    def DownloadDatasets(self):
        self.DownloadDirectory('11S_b4oPE2NdZ5ppfAqwvligSX56D7soD',os.path.join('CARLA drives','drives.zip'))
        self.DownloadDirectory('1kWtxcX-9xOdNNzcMuUggs5wg3DKRmKKj', os.path.join('Segmentation', 'Segmentation_Data.zip'))
        self.DownloadDirectory('1kaPlx6OJN8ZUCaku9a_NGcwL07fK7lAv', os.path.join('Detection', 'Detection_Data.zip'))
        self.DownloadDirectory('15-jr8n8EiEcF0GufwfG7ljYAad2TinJb', os.path.join('Detection and Segmentation', 'Detection_Segmentation_Data.zip'))

d = DownloadData()
d.DownloadDatasets()