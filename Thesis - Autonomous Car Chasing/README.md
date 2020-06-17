# Autonomous car chase
The repository presents a system that can autonomously chase another vehicle - i.e., goal is to maintain a determined distance between two cars. It has been tested in a CARLA simulator and with a RC cars. [Full video can be found here](https://www.youtube.com/watch?v=SxDJZUTOygA).

|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![Video of the car chase](https://i.imgur.com/RHbzHUF.gif)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|-------|


## Main contributions
* Functional autonomous driving system capable of chasing another vehicle based on information from a singel RGB camera. The full system is found in [src](/Thesis%20-%20Autonomous%20Car%20Chasing/src). The simplified version used with the RC cars can be found in [RC_Version](/Thesis%20-%20Autonomous%20Car%20Chasing/RC_Version).
* [Dual-task neural](/Thesis%20-%20Autonomous%20Car%20Chasing/dual-task%20network) network that can concurrently detect objects and perform coarse image segmentation.
 
Detection             |  Segmentation 2019
:-------------------------:|:-------------------------:
![detection](https://i.imgur.com/1y7BDH2.png)  |  ![segmentation](https://i.imgur.com/fMWX081.png)
* Three datasets (car chase dataset in CARLA, object detection dataset and semantic segmentation dataset) found in [datasets](/Thesis%20-%20Autonomous%20Car%20Chasing/datasets) 
* [Bachelor thesis](/Thesis%20-%20Autonomous%20Car%20Chasing/Autonomous_Car_Chasing.pdf) about the project.
