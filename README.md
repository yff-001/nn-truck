# Neural Network Driven RC Truck

This project was inspired by many similar projects published on internet, especially <a href = 'https://github.com/hamuchiwa/AutoRCCar'>this one</a>.

The vehicle is based on a 1/16 scale radio controlled toy truck. 

<p align="center">
  <img src="https://github.com/yff-001/nn-truck/blob/master/IMG_2239.JPG" width="1000" title="1/16 RC Truck">
</p>

Radio link is based on 2.4GHz channel. 4 switches on radio controller which control forward/reverse and left/right are directly tapped and connected to a STM32 development board which is in turn connected to a PC via serial link. 

<p align="center">
  <img src="https://github.com/yff-001/nn-truck/blob/master/IMG_2181.JPG" width="1000" title="RC Truck Tx">
</p>

A switch is closed when a digital pin on the STM32 is pulled down, thus sending a command to the vehicle. A Xbox controller connected to PC is used to drive the truck.

<p align="center">
  <img src="https://github.com/yff-001/nn-truck/blob/master/IMG_2213.jpg" width="1000" title="STM32 Connected to PC via FTDI">
</p>

A camera module V2 is connected to a Raspberry Pi 3B. Both are mounted on the vehicle. Raspberry Pi streams captured images to PC over WiFi. Images are parsed by OpenCV and saved as numpy array.

A neural network takes the numpy array and forward/reverse/left/right from human driver as inputs, and outputs 3 commands. The neural network is trained on PC and inference is alos carried out on PC.

These pieces of code are run on:

Arudino: rc_drive.ino

Raspberry Pi: picamera_stream_client.py

PC: picamera_stream_server.py, xbox_drive.py

**Neural Network code is still in progress.
