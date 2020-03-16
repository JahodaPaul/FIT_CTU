#!/usr/bin/env python3

import pyzed.sl as sl

import logging
import time
import sys
import imageio

# Logging
logger = logging.getLogger('zed_logger')
logger.setLevel(logging.DEBUG)

sh = logging.StreamHandler(sys.stdout)
sh.setLevel(logging.DEBUG)

fh = logging.FileHandler('zed.log')
fh.setLevel(logging.DEBUG)

file_formatter = logging.Formatter(
    '[%(asctime)s - -%(name)s - %(levelname)s] %(message)s')
fh.setFormatter(file_formatter)
prompt_formatter = logging.Formatter('[%(levelname)s] %(message)s')
sh.setFormatter(prompt_formatter)

logger.addHandler(fh)
logger.addHandler(sh)


def main_loop():
    # Init
    cntr = 0
    fps_timer = time.time()
    logger.info("Reading started...")

    while True:
        # Obtain camera image and get timestamps
        t1 = time.time()
        err = camera.grab(runtime)

        # If grabbing image successfull, save to buffer
        if err == sl.ERROR_CODE.SUCCESS:

            camera.retrieve_image(mat, sl.VIEW.VIEW_SIDE_BY_SIDE)
            cntr += 1

            grab_timestamp = t1
            img_name = '/media/ctu/ADATA SE730H/images/img_{}.jpg'.format(grab_timestamp)

            img = sl.ERROR_CODE.ERROR_CODE_FAILURE

            countdown = 5
            while img != sl.ERROR_CODE.SUCCESS and countdown > 0:

                # Write image and image data to files
                write_timestamp = time.time()
                img = mat.write(img_name)


                # Read half of the image
                im = imageio.imread(img_name)
                im = im[:, :im.shape[1] // 2, :]


                with open('/media/ctu/ADATA SE730H/img_data.txt', 'a') as data_file:   # external SSD
                    data_file.write("{}, {}\n".format(grab_timestamp,
                                                      write_timestamp))

                countdown -= 1
                if img == sl.ERROR_CODE.SUCCESS:
                    break

                logger.debug("Image not written!")

            # Count FPS
            if (time.time() - fps_timer) > 1:
                fps_timer = time.time()
                logger.info(f"Current FPS: {cntr}")
                cntr = 0


if __name__ == "__main__":
    # Init ZED camera parameters
    init = sl.InitParameters()
    init.camera_resolution = sl.RESOLUTION.RESOLUTION_VGA
    init.camera_linux_id = 0
    init.camera_fps = 60

    camera = sl.Camera()
    if not camera.is_opened():
        logger.info("Opening ZED Camera...")
    status = camera.open(init)
    if status != sl.ERROR_CODE.SUCCESS:
        logger.warning(repr(status))

    mat = sl.Mat()

    runtime = sl.RuntimeParameters()
    # Disabling computing depth image significantly improves
    # image obtaining speed
    runtime.enable_depth = False

    with open('/media/ctu/ADATA SE730H/img_data.txt', 'w') as data_file:
        data_file.write("grab_timestamp, write_timestamp\n")

    try:
        main_loop()
    except KeyboardInterrupt:
        logger.info("Keyboard interrupt, reading stopped.")
