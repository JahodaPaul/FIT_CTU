## CARLA Chasing dataset

### How to use the dataset
After you have downloaded the dataset. Download [CARLA version 0.9.8](https://carla.org/2020/03/09/release-0.9.8/). Then, copy this directory into a CARLA_0.9.8/PythonAPI directory.

You can then start the process. First you get a new video and call the CARLA server in the directory CARLA_0.9.8
```
./CarlaUE4.sh
```

Afterwards, you open another terminal and call the following command while in directory CARLA_0.9.8/PythonAPI/CARLA drives
```
python3 synchronous_mode.py
```

This will start the first drive of the car chase. The chasing algorithm is not implemented in this file. The chasing car will drive straight.
![Imgur](https://i.imgur.com/d1XOkYX.png)


To test your own algorithm, change the following line:
```
                # Choose approriate steer and throttle here
                steer, throttle = 0, 1
                vehicle.apply_control(carla.VehicleControl(throttle=throttle,steer=steer))
```
I recommend using "bbox" variable (chased car 3D) box, "image_segmentation" that contains the semantic segmentation of the current image and the "img_rgb" that contains rgb image seen from the camera.


### Evaluation
Afterwards, Use the following command to evaluate the dataset
```
python3 AnalyseResults.py
```
It will calculate the percentage how long your system was able to chase another vehicle. You can also find average MAE, RMSE and number of collisions in res/results.txt
![Imgur](https://i.imgur.com/iSdHqDg.jpg)

### Example with our system
[Here](https://youtu.be/mAh8CcaAHgM) you can find an example of our full system chasing another vehicle. The drive is part of the difficult split set of the dataset.

