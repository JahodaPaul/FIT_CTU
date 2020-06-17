#!/usr/bin/env python3

import sys
import os
import time
import serial
import logging
import struct
import csv
import termios
import tty
from multiprocessing import Process, Manager, Value
from multiprocessing.managers import BaseManager, SyncManager
import signal

import raspberry_data

# Constants
MESSAGE_SIZE_BYTES = raspberry_data.DATA_SIZE  # Message data size in bytes (w/o start bytes)
MESSAGE_START_FRAME = raspberry_data.DATA_START_FRAME

# Data types definition
DATA_STRUCT = raspberry_data.DATA_STRUCT  # Data types list compatible with struct.unpack
DATA_NAMES = raspberry_data.DATA_NAMES

# Logging
logger = logging.getLogger('usart_logger')
logger.setLevel(logging.DEBUG)

sh = logging.StreamHandler(sys.stdout)
sh.setLevel(logging.INFO)

fh = logging.FileHandler('usart.log')
fh.setLevel(logging.DEBUG)

file_formatter = logging.Formatter(
    '[%(asctime)s - -%(name)s - %(levelname)s] %(message)s')
fh.setFormatter(file_formatter)
prompt_formatter = logging.Formatter('[%(levelname)s] %(message)s')
sh.setFormatter(prompt_formatter)

logger.addHandler(fh)
logger.addHandler(sh)

manualCarControlBool = True


def main_loop(serial_ifc, curr_data):
    """
    """
    msg_cntr = 0
    logger.info("Reading from serial started.")

    baud_timer = time.time()
    try:
        while True:
        # Read serial, if connected
            if serial_ifc.isOpen():
                no_data_counter = 0
                if not serial_ifc.in_waiting:
                    no_data_counter += 1
                    if no_data_counter > 10e5:
                        logger.info("No data recieved from serial. Waiting...")
                        no_data_counter = 0
                    continue

                start_bytes = []
                reading = b''
                while True:
                    current_byte = serial_ifc.read(1)
                    if current_byte != b'\xaa':
                        start_bytes = []
                        continue
                    start_bytes.append(current_byte)
                    if start_bytes == MESSAGE_START_FRAME:
                        break

                timestamp = time.time()
                reading = serial_ifc.read(MESSAGE_SIZE_BYTES)
            else:
                logger.warning("Serial port disconnected!")
                break

            if len(reading) < MESSAGE_SIZE_BYTES:
                logging.info("No or corrupted data recieved. "
                             "Data length is {}".format(len(reading)))
                continue

            msg_cntr += len(reading)

            temp_data = process_message(reading, timestamp)

            # Copy data message to shared list
            # TODO: FIXME: rewrite this to a pipe or just one variable!
            curr_data[:] = []
            curr_data.extend(temp_data)


            # Count BaudRate
            if not manualCarControlBool:
                if (time.time() - baud_timer) > 1:
                    baud_timer = time.time()
                    logger.info(f"Current baudrate: {msg_cntr*8} ({msg_cntr*8/MESSAGE_SIZE_BYTES} samples/s)")
                    msg_cntr = 0

    except KeyboardInterrupt:
        print("\n")
        print("Closing DataAcquisition process.")


def process_message(msg, timestamp):
    """ Decodes message and saves values to file.
    """
    logger.debug("Data recieved:\t {}".format(''.join(r'\x'+hex(letter)[2:] for letter in msg)))    
    fmt = DATA_STRUCT
    data = struct.unpack(fmt, msg)
    logger.debug("Data unpacked:\t {}".format(data))
    # with open('data/meas_data.txt', 'a') as data_file:
    with open('/media/ctuxavier/ADATASE730H/meas_data.txt', 'a') as data_file:     # external SSD
        writer = csv.writer(data_file, delimiter=',')
        templist = list(data)
        templist.insert(0, timestamp)
        writer.writerow(templist)
    return data


def getch():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch


def setCarRPM(serial_ifc, rpmPWM):
    serial_ifc.write((struct.pack('>B', 0)))                        # send ZERO as code for setRPM
    serial_ifc.write((struct.pack('i', rpmPWM)))


def setCarDistance(serial_ifc, meters, speed):
    meters = meters * 300
    tachometer_Vesc_goal = tachometer_Vesc.value + meters
    setCarRPM(serial_ifc, speed)
    while tachometer_Vesc_goal > tachometer_Vesc.value:
        print("current:", tachometer_Vesc.value, "goal:", tachometer_Vesc_goal)
        continue
    print("Braking")
    #setCarRPM(0)


def setCarSteer(serial_ifc, steerPWM):
    serial_ifc.write((struct.pack('>B', 1)))                        # send ONE as code for setRPM
    serial_ifc.write((struct.pack('i', steerPWM)))


def carStop(serial_ifc):
    serial_ifc.write((struct.pack('>B', 2)))                        # send TWO as code for carStop
    print("Car stop initiated!")


def carStopABS(serial_ifc):
    serial_ifc.write((struct.pack('>B', 3)))                        # send THREE as code for carStopABS
    print("Car ABS stop initiated!")


def setAbsK(serial_ifc, abs_k):
    try:
        last_abs_k = 0
        while True:
            with abs_k:
                abs_k_val = abs_k.value
            if abs_k_val != last_abs_k:
                serial_ifc.write((struct.pack('>B', 4)))                        # send FOUR as code for change of abs_k
                serial_ifc.write((struct.pack('f', abs_k_val)))
                last_abs_k = abs_k_val
            # time.sleep(0.1)
    except KeyboardInterrupt:
        print("Closing abs_k process.")


def carSetAutopilot(serial_ifc, autopilot_on=True):
    serial_ifc.write((struct.pack('>B', 5)))                        # send 5 as code for carSetAutopilot
    serial_ifc.write((struct.pack('i', int(autopilot_on))))
    print(f"Autopilot set on {autopilot_on}.")


# handle SIGINT from SyncManager object
def mgr_sig_handler(signal, frame):
    return None


# initilizer for SyncManager
def mgr_init():
    signal.signal(signal.SIGINT, mgr_sig_handler)
    print('Initialized mananger.')


def manualCarControl(serial_ifc):
    manualCarControlBool = True
    throttle = 0
    steer = 0
    while 1:
        command = getch()
        if command == "w":
            if throttle == 100:
                continue
            throttle += 10
            setCarRPM(serial_ifc, throttle)
        elif command == "s":
            if throttle == -100:
                continue
            throttle -= 10
            setCarRPM(serial_ifc, throttle)
        elif command == "d":
            if steer == 100:
                continue
            steer += 5
            setCarSteer(serial_ifc, steer)
        elif command == "a":
            if steer == -100:
                continue
            steer -= 5
            setCarSteer(serial_ifc, steer)
        elif command == "q":
            throttle = 0
            setCarRPM(serial_ifc, throttle)
            steer = 0
            setCarSteer(serial_ifc, steer)
            time.sleep(0.2)
            print("Exiting manual car control!")
            exit(0)
        else:
            throttle = 0
            steer = 0
            setCarRPM(serial_ifc, throttle)
            setCarSteer(serial_ifc, steer)
        print("CAR RPM %:", throttle)
        print("CAR steer %:", steer)


def CarControl(serial_ifc):
    try:
        setCarSteer(serial_ifc, 1440)
        time.sleep(3)
        setCarRPM(serial_ifc, 1700)
        time.sleep(2.0)
        carStop(serial_ifc)
        setCarSteer(serial_ifc, 1820)
        setCarRPM(serial_ifc, 1520)
    except KeyboardInterrupt:
        print("Closing CarControl process.")

# Updated version used for chasing, the previous version can be found in file raspberry_control_prev.py
def AutopilotControl(serial_ifc, throttle_SP, steer_SP, curr_data):
    """ Autopilot interface provides direct control over throttle and steer
    signals going to servo and motor via shared values. Autopilot is to be
    stopped, when negative (breaking) throttle signal is detected.
    """
    end = False

    carSetAutopilot(serial_ifc, True)
    time.sleep(5)


    while not end:
        # Check, if throttle
        interrupt = throttle_SP.value < 1400

        if not interrupt:
            # Set throttle and PWM from setpoints
            throttle_sp_val = throttle_SP.value
            steer_sp_val = steer_SP.value

            # print("Steer: " + str(steer_sp_val) + " Throttle: " + str(throttle_sp_val))
            setCarRPM(serial_ifc, int(throttle_sp_val))
            setCarSteer(serial_ifc, int(steer_sp_val))
            if abs(throttle_SP.value - 1520) <= 3:
                time.sleep(0.1)
            time.sleep(0.005)
        else:
            # Throttle interrupt recieved, stop autopilot
            print("Throttle autopilot interrupt recieved, autopilot interface "
                  "stopped, car stop initiated.")
            carSetAutopilot(serial_ifc, False)
            end = True


def main(abs_k=None, throttle_SP=None, steer_SP=None, autopilot=True):
    serial_port = "/dev/ttyTHS0"
    baudrate = 1000000
    parity = serial.PARITY_EVEN
    stopbits = 2

    # Try to open serial
    try:
        serial_ifc = serial.Serial(
            port=serial_port,
            baudrate=baudrate,
            parity=parity,
            stopbits=stopbits,
            timeout=0.5)
        time.sleep(0.1)
    except:
        logger.warning("Cannot connect to serial '{}'".format(serial_port))
        logger.info("Reading and synchronization stopped.")
        sys.exit()

    # Write first row of data file
    with open('/media/ctuxavier/ADATASE730H/meas_data.txt', 'w') as data_file:
        data_file.write("Time,{}\n".format(','.join(DATA_NAMES)))

    processes = []
    manager = SyncManager()
    manager.start(mgr_init)

    manager = Manager()
    curr_data = manager.list()

    tachometer_Vesc = Value('i', 0)
    accY2 = Value('f', 510)
    DataAcquisition_pr = Process(target=main_loop, args=(serial_ifc, curr_data))
    print("Starting DataAcquisition.")
    DataAcquisition_pr.start()
    processes.append(DataAcquisition_pr)
    time.sleep(0.5)

    # manualCarControl()

    if not manualCarControlBool:
        CarControl_pr = Process(target=CarControl, args=(serial_ifc, ))
        print("Starting CarControl.")
        CarControl_pr.start()
        processes.append(CarControl_pr)

    if autopilot:
        # Autopilot control interface
        # FIXME: problem with serial send! only one serial should
        # transmit at the moment
        AutopilotControl_pr = Process(target=AutopilotControl,
                                      args=(serial_ifc, throttle_SP,
                                            steer_SP, curr_data))

        print("Starting Autopilot Control.")
        AutopilotControl_pr.start()
        processes.append(AutopilotControl_pr)

    # DEBUG: delete this
    #time.sleep(5)
    #with steer_SP.get_lock():
    #    steer_SP.value = 1200
    #with throttle_SP.get_lock():
    #    throttle_SP.value = 1490

    # FIXME: this is commented for debugging!!!
    # abs_k_update = Process(target=setAbsK, args=(serial_ifc, abs_k, ))
    # abs_k_update.start()
    # processes.append(abs_k_update)

    try:
        for process in processes:
            process.join()
    except KeyboardInterrupt:
        if serial_ifc.isOpen():
            setCarRPM(serial_ifc, 1520)               # stop the car
            setCarSteer(serial_ifc, 1220) # was 1420
            serial_ifc.close()
        logger.info("Keyboard interrupt, reading stopped.")


if __name__ == "__main__":
    main()

