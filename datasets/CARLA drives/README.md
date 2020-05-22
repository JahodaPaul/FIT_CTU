## CARLA Chasing dataset

### How to use the dataset
After you have downloaded the dataset. Download CARLA version 0.9.8
Then, copy this directory into a CARLA_0.9.8/PythonAPI directory.

You can then start the process by calling synchronous_mode.py
```
python3 synchronous_mode.py
```

This will start the first drive of the car chase. The chasing algorithm is not implemented in this file. The chasing car will drive straight.


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


