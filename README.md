# nn-truck
Neural Network Driven RC Truck

This project was inspired by many similar projects published on Youtube and Github.

The vehicle is based on a 1/16 scale radio controlled toy truck. Radio link is based on 2.4GHz channel. 4 switches on radio controller which control forward/reverse and left/right are directly tapped and connected to an Arduino nano. Arduino nano are in turn connected to a PC via serial link. A switch is closed when a digital pin on the Arduino is pulled down, thus sending a command to the vehicle. A Xbox controller connected to PC is used to drive the truck.

A camera module V2 is connected to a Raspberry Pi 3B. Both are mounted on the vehicle. Raspberry Pi streams captured images to PC over WiFi. Images are parsed by OpenCV and saved as numpy array.

A neural network takes the numpy array and forward/reverse/left/right from human driver as inputs, and outputs 3 command. The neural network is trained on PC and inference is alos carried out on PC.

These pieces of code are run on:
Arudino: rc_drive.ino

Raspberry Pi: stream_client.py

PC: stream_server.py, xbox_drive.py

Neural Network code is still in progress.
