#!/usr/bin/env python

# Copyright (c) 2019 Computer Vision Center (CVC) at the Universitat Autonoma de
# Barcelona (UAB).
#
# This work is licensed under the terms of the MIT license.
# For a copy, see <https://opensource.org/licenses/MIT>.

import glob
import os
import sys
from CarDetector import CarDetector
from DrivingControl import DrivingControl
from VizualizeDrivingPath import VizualizeDrivingPath
from PurePursuitAlgorithm import PurePursuitAlgorithm
from SemanticSegmentation import SemanticSegmentation
from DrivingControlAdvanced import DrivingControlAdvanced
import math
import pickle

try:
    sys.path.append(glob.glob('../carla/dist/carla-*%d.%d-%s.egg' % (
        sys.version_info.major,
        sys.version_info.minor,
        'win-amd64' if os.name == 'nt' else 'linux-x86_64'))[0])
except IndexError:
    pass

import carla

import random

try:
    import pygame
except ImportError:
    raise RuntimeError('cannot import pygame, make sure pygame package is installed')

try:
    import numpy as np
except ImportError:
    raise RuntimeError('cannot import numpy, make sure numpy package is installed')

try:
    import queue
except ImportError:
    import Queue as queue


class CarlaSyncMode(object):
    """
    Context manager to synchronize output from different sensors. Synchronous
    mode is enabled as long as we are inside this context

        with CarlaSyncMode(world, sensors) as sync_mode:
            while True:
                data = sync_mode.tick(timeout=1.0)

    """

    def __init__(self, world, *sensors, **kwargs):
        self.world = world
        self.sensors = sensors
        self.frame = None
        self.delta_seconds = 1.0 / kwargs.get('fps', 20)
        self._queues = []
        self._settings = None

    def __enter__(self):
        self._settings = self.world.get_settings()
        self.frame = self.world.apply_settings(carla.WorldSettings(
            no_rendering_mode=False,
            synchronous_mode=True,
            fixed_delta_seconds=self.delta_seconds))

        def make_queue(register_event):
            q = queue.Queue()
            register_event(q.put)
            self._queues.append(q)

        make_queue(self.world.on_tick)
        for sensor in self.sensors:
            make_queue(sensor.listen)
        return self

    def tick(self, timeout):
        self.frame = self.world.tick()
        data = [self._retrieve_data(q, timeout) for q in self._queues]
        assert all(x.frame == self.frame for x in data)
        return data

    def __exit__(self, *args, **kwargs):
        self.world.apply_settings(self._settings)

    def _retrieve_data(self, sensor_queue, timeout):
        while True:
            data = sensor_queue.get(timeout=timeout)
            if data.frame == self.frame:
                return data


def draw_image(surface, image, image2,location1, location2, blend=False, record=False,driveName=''):
    # if image2.frame%20 == 0:
    #     dirName = os.path.join('test')
    #     if not os.path.exists(dirName):
    #         os.mkdir(dirName)
    #     image2.save_to_disk(dirName + '/%07d' % image2.frame)
    if record:#image.frame % 10 == 0:
        driveName = driveName.split('/')[1]
        dirName = os.path.join('output',driveName)
        if not os.path.exists(dirName):
            os.mkdir(dirName)
        image.save_to_disk(dirName+'/%07d' % image.frame)#_%f_%f_%f_%f_%f_%f_%f_%f_%f_%f_%f_%f.png' % (image.frame,location1.location.x,location1.location.y,location1.location.z, location1.rotation.pitch,location1.rotation.yaw, location1.rotation.roll,location2.location.x,location2.location.y,location2.location.z, location2.rotation.pitch,location2.rotation.yaw, location2.rotation.roll ))
        #image2.save_to_disk('output2/%07d_%f_%f_%f_%f_%f_%f_%f_%f_%f_%f_%f_%f.png' % (image2.frame,location1.location.x,location1.location.y,location1.location.z, location1.rotation.pitch,location1.rotation.yaw, location1.rotation.roll
        #                                                    ,location2.location.x,location2.location.y,location2.location.z, location2.rotation.pitch,location2.rotation.yaw, location2.rotation.roll ))
    array = np.frombuffer(image.raw_data, dtype=np.dtype("uint8"))
    array = np.reshape(array, (image.height, image.width, 4))
    array = array[:, :, :3]
    array = array[:, :, ::-1]
    image_surface = pygame.surfarray.make_surface(array.swapaxes(0, 1))
    if blend:
        image_surface.set_alpha(100)
    surface.blit(image_surface, (0, 0))


def get_font():
    fonts = [x for x in pygame.font.get_fonts()]
    default_font = 'ubuntumono'
    font = default_font if default_font in fonts else fonts[0]
    font = pygame.font.match_font(font)
    return pygame.font.Font(font, 14)


def should_quit():
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            return True
        elif event.type == pygame.KEYUP:
            if event.key == pygame.K_ESCAPE:
                return True
    return False

try:
    import pygame
    from pygame.locals import KMOD_CTRL
    from pygame.locals import KMOD_SHIFT
    from pygame.locals import K_0
    from pygame.locals import K_9
    from pygame.locals import K_BACKQUOTE
    from pygame.locals import K_BACKSPACE
    from pygame.locals import K_COMMA
    from pygame.locals import K_DOWN
    from pygame.locals import K_ESCAPE
    from pygame.locals import K_F1
    from pygame.locals import K_LEFT
    from pygame.locals import K_PERIOD
    from pygame.locals import K_RIGHT
    from pygame.locals import K_SLASH
    from pygame.locals import K_SPACE
    from pygame.locals import K_TAB
    from pygame.locals import K_UP
    from pygame.locals import K_a
    from pygame.locals import K_c
    from pygame.locals import K_d
    from pygame.locals import K_h
    from pygame.locals import K_m
    from pygame.locals import K_p
    from pygame.locals import K_q
    from pygame.locals import K_r
    from pygame.locals import K_s
    from pygame.locals import K_w
    from pygame.locals import K_MINUS
    from pygame.locals import K_EQUALS
except ImportError:
    raise RuntimeError('cannot import pygame, make sure pygame package is installed')

class ManualControl(object):
    def __init__(self):
        #self.vehicle = vehicle
        self.history = []
        self._control = carla.VehicleControl()
        self._steer_cache = 0.0
        self.fileName = 'test.p'
        self.startRecording = False
        #self.display = pygame.display.set_mode(
        #    (200, 200),
        #    pygame.HWSURFACE | pygame.DOUBLEBUF)

    def _parse_vehicle_keys(self, keys, milliseconds):
        self._control.throttle = 1.0 if keys[K_UP] or keys[K_w] else 0.0
        self._control.reverse=False
        if keys[K_DOWN] or keys[K_s]:
            self._control.throttle = 1
            self._control.reverse=True
        steer_increment = 8e-4 * milliseconds
        if keys[K_LEFT] or keys[K_a]:
            self._steer_cache -= steer_increment
        elif keys[K_RIGHT] or keys[K_d]:
            self._steer_cache += steer_increment
        else:
            self._steer_cache = 0.0
        self._steer_cache = min(0.5, max(-0.5, self._steer_cache))
        self._control.steer = round(self._steer_cache, 1)
        #self._control.brake = 1.0 if keys[K_DOWN] or keys[K_s] else 0.0
        self._control.hand_brake = keys[K_SPACE]

        if keys[K_r]:
            self.startRecording = True
    
    def Run(self):
        clock = pygame.time.Clock()
        while True:
            clock.tick_busy_loop(30)
            #pygame.event.get()
            self._parse_vehicle_keys(pygame.key.get_pressed(), clock.get_time())
            self.vehicle.apply_control(self._control)
            pygame.display.flip()

    def SaveCarPosition(self,location):
        if self.startRecording:
            self.history.append([location.location.x, location.location.y, location.location.z, location.rotation.pitch, location.rotation.yaw, location.rotation.roll])

    def SaveHistoryToFile(self):
        if len(self.history) > 0:
            pickle.dump(self.history,  open(self.fileName, "wb"))


class Evaluation():
    def __init__(self):
        self.sumMAE = 0
        self.sumRMSE = 0
        self.n_of_frames = 0
        self.n_of_collisions = 0
        self.history = []

    def AddError(self, distance, goalDistance):
        self.n_of_frames += 1
        self.sumMAE += abs(goalDistance-distance)
        self.sumRMSE += abs(goalDistance-distance)*abs(goalDistance-distance)

    def WriteIntoFileFinal(self, filename, driveName):
        self.sumMAE = self.sumMAE / float(self.n_of_frames)
        self.sumRMSE = self.sumRMSE / float(self.n_of_frames)

        with open(filename,'a') as f:
            f.write(str(driveName)+', '+str(self.sumMAE)+', '+str(self.sumRMSE)+', '+str(self.n_of_collisions)+'\n')

    def LoadHistoryFromFile(self, fileName):
        self.history = pickle.load( open(fileName, "rb"))

    def CollisionHandler(self,event):
        self.n_of_collisions += 1


import copy
def main(optimalDistance, followDrivenPath, chaseMode, evaluateChasingCar, driveName='',record=False, followMode=False):
    counter = 1

    actor_list = []
    pygame.init()

    carDetector = CarDetector()
    drivingControl = DrivingControl(optimalDistance=optimalDistance)
    drivingControlAdvanced = DrivingControlAdvanced(optimalDistance=optimalDistance)
    visualisation = VizualizeDrivingPath()
    myControl = ManualControl()
    evaluation = Evaluation()
    semantic = SemanticSegmentation()

    lastX, lastY = 0, 0


    lookAheadDistance = 5
    purePursuit = PurePursuitAlgorithm(lookAheadDistance=lookAheadDistance)

    display = pygame.display.set_mode(
        (800, 600),
        pygame.HWSURFACE | pygame.DOUBLEBUF)
    font = get_font()
    clock = pygame.time.Clock()

    client = carla.Client('localhost', 2000)
    client.set_timeout(2.0)

    world = client.get_world()

    vehicleToFollowSpawned = False


    try:
        m = world.get_map()
        # if not followDrivenPath:
        start_pose = random.choice(m.get_spawn_points())
        # else:
            # first = evaluation.history[0]
            # print(first)
            # start_pose = random.choice(m.get_spawn_points())
            # start_pose = carla.Transform(carla.Location(first[0],first[1],first[2]),carla.Rotation(first[3],first[4],first[5]))
        # print('Start pose:',start_pose)

        blueprint_library = world.get_blueprint_library()
        
        vehicle = world.spawn_actor(
            random.choice(blueprint_library.filter('jeep')),
            start_pose)
        actor_list.append(vehicle)
        vehicle.set_simulate_physics(True)
        if followDrivenPath:
            evaluation.LoadHistoryFromFile(driveName)
            first = evaluation.history[0]
            start_pose = carla.Transform(carla.Location(first[0], first[1], first[2]),
                                         carla.Rotation(first[3], first[4], first[5]))
            vehicle.set_transform(start_pose)

        collision_sensor = world.spawn_actor(blueprint_library.find('sensor.other.collision'),
                                             carla.Transform(), attach_to=vehicle)

        collision_sensor.listen(lambda event: evaluation.CollisionHandler(event))
        actor_list.append(collision_sensor)
        # deep copy
        
        # carla.Location(x=1.5, z=1.4,y=-0.3)
        # Find the blueprint of the sensor.
        blueprint = world.get_blueprint_library().find('sensor.camera.rgb')
        # Modify the attributes of the blueprint to set image resolution and field of view.
        blueprint.set_attribute('image_size_x', '800')
        blueprint.set_attribute('image_size_y', '600')
        blueprint.set_attribute('fov', '90')

        camera_rgb = world.spawn_actor(
            blueprint_library.find('sensor.camera.rgb'),
            carla.Transform(carla.Location(x=1.5, z=1.4,y=0.3), carla.Rotation(pitch=0)), #5,3,0 # -0.3
            attach_to=vehicle)
        actor_list.append(camera_rgb)
        # camera_rgb.set(FOV=90.0)
        # camera_rgb.set_image_size(800, 600)

        camera_rgb2 = world.spawn_actor(
            blueprint_library.find('sensor.camera.rgb'),
            carla.Transform(carla.Location(x=-5.5, z=4.4,y=0), carla.Rotation(pitch=0)),
            attach_to=vehicle)
        actor_list.append(camera_rgb2)

        camera_segmentation = world.spawn_actor(
            blueprint_library.find('sensor.camera.semantic_segmentation'),
            carla.Transform(carla.Location(x=1.5, z=1.4,y=0), carla.Rotation(pitch=0)), #5,3,0 # -0.3
            attach_to=vehicle)
        actor_list.append(camera_segmentation)
        
        

        # Create a synchronous mode context.
        with CarlaSyncMode(world, camera_rgb, camera_rgb2, camera_segmentation, fps=30) as sync_mode:

            while True:
                if should_quit():
                    return
                clock.tick(30)

                # Advance the simulation and wait for the data.
                snapshot, image_rgb, image_rgb2, image_segmentation = sync_mode.tick(timeout=2.0)


                
                if not vehicleToFollowSpawned and not followDrivenPath:
                    vehicleToFollowSpawned = True
                    start_pose2 = carla.Transform()
                    start_pose2.rotation = start_pose.rotation

                    start_pose2.location.x = start_pose.location.x
                    start_pose2.location.y = start_pose.location.y
                    start_pose2.location.z = start_pose.location.z
                    #waypoint = m.get_waypoint(start_pose.location)

                    location1 = vehicle.get_transform()
                    rotation1 = location1.rotation
                    print(rotation1.yaw,abs(rotation1.yaw))
                    if abs(rotation1.yaw - 180.0) < 45.0 or abs(rotation1.yaw + 180.0) < 45.0:
                        print('1')
                        start_pose2.location.x = start_pose.location.x - 5
                    elif abs(rotation1.yaw) < 45.0:
                        print('2')
                        start_pose2.location.x = start_pose.location.x + 5
                    elif abs(rotation1.yaw + 90.0) < 45.0:
                        print('3')
                        start_pose2.location.y = start_pose.location.y - 5
                    elif abs(rotation1.yaw - 90.0) < 45.0:
                        print('4')
                        start_pose2.location.y = start_pose.location.y + 5

                    bp = blueprint_library.filter('tesla')[0]
                    bp.set_attribute('color', '204,0,204')
                    vehicleToFollow = world.spawn_actor(
                        bp,
                        start_pose2)

                    actor_list.append(vehicleToFollow)
                    vehicleToFollow.set_simulate_physics(True)
                    vehicleToFollow.set_autopilot(True)
                elif not vehicleToFollowSpawned and followDrivenPath:
                    vehicleToFollowSpawned = True
                    location1 = vehicle.get_transform()
                    newX, newY = carDetector.CreatePointInFrontOFCar(location1.location.x, location1.location.y,
                                                                     location1.rotation.yaw)
                    diffX = newX - location1.location.x
                    diffY = newY - location1.location.y
                    newX = location1.location.x - (diffX*5)
                    newY = location1.location.y - (diffY*5)

                    start_pose.location.x = newX
                    start_pose.location.y = newY

                    vehicle.set_transform(start_pose)

                    start_pose2 = random.choice(m.get_spawn_points())

                    bp = blueprint_library.filter('tesla')[0]
                    bp.set_attribute('color', '204,0,204')
                    vehicleToFollow = world.spawn_actor(
                        bp,
                        start_pose2)

                    start_pose2 = carla.Transform()
                    start_pose2.rotation = start_pose.rotation

                    start_pose2.location.x = start_pose.location.x
                    start_pose2.location.y = start_pose.location.y
                    start_pose2.location.z = start_pose.location.z

                    vehicleToFollow.set_transform(start_pose2)

                    actor_list.append(vehicleToFollow)
                    vehicleToFollow.set_simulate_physics(True)
                    vehicleToFollow.set_autopilot(False)

                if followDrivenPath:
                    if counter >= len(evaluation.history):
                        break
                    tmp = evaluation.history[counter]
                    currentPos = carla.Transform(carla.Location(tmp[0],tmp[1],tmp[2]),carla.Rotation(tmp[3],tmp[4],tmp[5]))
                    vehicleToFollow.set_transform(currentPos)
                    counter += 1

                # Choose the next waypoint and update the car location.
                #waypoint = random.choice(waypoint.next(1.5))
                # vehicle.set_transform(waypoint.transform)

                #image_semseg.convert(carla.ColorConverter.CityScapesPalette)
                fps = round(1.0 / snapshot.timestamp.delta_seconds)
                # Draw the display.

                # manual control
                if not followDrivenPath:
                    myControl._parse_vehicle_keys(pygame.key.get_pressed(), clock.get_time())
                    vehicle.apply_control(myControl._control)


                location1 = vehicle.get_transform()
                location2 = vehicleToFollow.get_transform()

                myControl.SaveCarPosition(location1)

                if chaseMode:
                    carInTheImage = semantic.IsThereACarInThePicture(image_segmentation)
                    bbox, predicted_distance,predicted_angle = carDetector.getDistance(vehicleToFollow, camera_rgb,carInTheImage)

                    newX, newY = carDetector.CreatePointInFrontOFCar(location1.location.x,location1.location.y,location1.rotation.yaw)
                    if len(bbox) != 0:
                        lastX = location2.location.x
                        lastY = location2.location.y
                    angle = carDetector.getAngle([location1.location.x,location1.location.y],[newX,newY],[location2.location.x,location2.location.y])
                    print('real angle:', angle)

                    if True:
                        objectInFront, goLeftOrRight = semantic.ObjectInFrontOfChasedCar(image_segmentation,bbox)
                        steer, throttle = drivingControlAdvanced.PredictSteerAndThrottle(predicted_distance, predicted_angle,None, goLeftOrRight)
                    else:
                        steer, throttle = drivingControl.PredictSteerAndThrottle(predicted_distance,predicted_angle,None)

                    # if followDrivenPath:
                    vehicle.apply_control(carla.VehicleControl(throttle=throttle,steer=steer))

                    if evaluateChasingCar:
                        evaluation.AddError(location1.location.distance(location2.location),optimalDistance)
                elif followMode:
                    angle = 0
                    carInTheImage = semantic.IsThereACarInThePicture(image_segmentation)
                    bbox, predicted_distance, predicted_angle = carDetector.getDistance(vehicleToFollow, camera_rgb,carInTheImage)
                    purePursuit.AddPathPoint(location2.location.x,location2.location.y)
                    newX, newY = carDetector.CreatePointInFrontOFCar(location1.location.x, location1.location.y,
                                                                     location1.rotation.yaw)
                    targetX, targetY = purePursuit.GetNextPoint(location1.location.x,location1.location.y)
                    predicted_angle = carDetector.getAngle([location1.location.x,location1.location.y],[newX,newY],[targetX,targetY])
                    # print('real angle:', angle)
                    steer, throttle = drivingControl.PredictSteerAndThrottle(predicted_distance,predicted_angle,None)

                    # if followDrivenPath:
                    vehicle.apply_control(carla.VehicleControl(throttle=throttle,steer=steer))
                    if evaluateChasingCar:
                        evaluation.AddError(location1.location.distance(location2.location),optimalDistance)

                # transform2 = vehicleToFollow.get_transform()
                # print(camera_rgb2.get_location())
                # # print(vehicleToFollow.bounding_box)
                # # print(vehicleToFollow.bounding_box.transform())
                # # location1.location.x = newX
                # # location1.location.y = newY
                # # print(location1)
                # # vehicle.set_transform(location1)
                # transform = vehicleToFollow.get_transform()
                # bounding_box = vehicleToFollow.bounding_box
                # bounding_box.location += transform.location
                # world.debug.draw_box(bounding_box, transform.rotation)

                velocity1 = vehicle.get_velocity()
                velocity2 = vehicleToFollow.get_velocity()


                print('real dist:',location1.location.distance(location2.location))


                visualisation.Add(velocity1,velocity2,location1.location.distance(location2.location), angle)


                draw_image(display, image_rgb2, image_rgb2,location1, location2,record=record,driveName=driveName)
                display.blit(
                    font.render('% 5d FPS (real)' % clock.get_fps(), True, (255, 255, 255)),
                    (8, 10))
                display.blit(
                    font.render('% 5d FPS (simulated)' % fps, True, (255, 255, 255)),
                    (8, 28))

                if len(bbox) != 0:
                    points = [(int(bbox[i, 0]), int(bbox[i, 1])) for i in range(8)]
                    BB_COLOR = (248, 64, 24)
                    # draw lines
                    # base
                    pygame.draw.line(display, BB_COLOR, points[0], points[1])
                    pygame.draw.line(display, BB_COLOR, points[1], points[2])
                    pygame.draw.line(display, BB_COLOR, points[2], points[3])
                    pygame.draw.line(display, BB_COLOR, points[3], points[0])
                    # top
                    pygame.draw.line(display, BB_COLOR, points[4], points[5])
                    pygame.draw.line(display, BB_COLOR, points[5], points[6])
                    pygame.draw.line(display, BB_COLOR, points[6], points[7])
                    pygame.draw.line(display, BB_COLOR, points[7], points[4])
                    # base-top
                    pygame.draw.line(display, BB_COLOR, points[0], points[4])
                    pygame.draw.line(display, BB_COLOR, points[1], points[5])
                    pygame.draw.line(display, BB_COLOR, points[2], points[6])
                    pygame.draw.line(display, BB_COLOR, points[3], points[7])


                pygame.display.flip()

    finally:
        if evaluateChasingCar:
            evaluation.WriteIntoFileFinal('results.txt',driveName=driveName)
        myControl.SaveHistoryToFile()
        print('destroying actors.')
        for actor in actor_list:
            actor.destroy()

        pygame.quit()
        print('done.')

import os
if __name__ == '__main__':

    try:
        optimalDistance = 8
        followDrivenPath = True
        evaluateChasingCar = True
        record = False
        chaseMode = True
        followMode = False

        drivesDir = 'drives'
        drivesFileNames = os.listdir(drivesDir)
        drivesFileNames.sort()

        drivesFileNames = ['ride10.p']
        if evaluateChasingCar:
            for fileName in drivesFileNames:
                main(optimalDistance=optimalDistance,followDrivenPath=followDrivenPath,chaseMode=chaseMode, evaluateChasingCar=evaluateChasingCar,driveName=os.path.join(drivesDir,fileName),record=record,followMode=followMode)
        else:
            main(optimalDistance=optimalDistance, followDrivenPath=followDrivenPath, chaseMode=chaseMode, evaluateChasingCar=evaluateChasingCar,followMode=followMode)

    except KeyboardInterrupt:
        print('\nCancelled by user. Bye!')
