# Neural Network Drives a Model Truck

This project was inspired by many similar projects published on internet, especially <a href = 'https://github.com/hamuchiwa/AutoRCCar'>this one</a>.

The vehicle is built based on a 1/16 scale radio controlled toy truck. 

<p align="center">
  <img src="https://github.com/yff-001/nn-truck/blob/master/images/IMG_2239.JPG" width="1000" title="1/16 RC Truck">
</p>

This truck came with a 2.4GHz encoder/decoder module. There are 4 switches on encoder side which control forward/reverse and left/right. When a switch is closed, the pin it connects to on the encoder is pulled down, a signal is sent to decoder over radio frequency. A corresponding pin on decoder side is also pulled down. 4 wires are soldered to the switches and connect them to A4:0 pins on a STM32 development board. The STM32 communicates with PC through a serial link. STM32 was selected because it's 3.3V logic level is compatible with logic levels that are on the encoder module.

<p align="center">
  <img src="https://github.com/yff-001/nn-truck/blob/master/images/IMG_2181.JPG" width="1000" title="RC Truck Tx">
</p>

A Xbox controller connected to PC is used to manually drive the truck. Control inputs are passed to a Python script using pyserial and pygame.

<p align="center">
  <img src="https://github.com/yff-001/nn-truck/blob/master/images/IMG_2213.jpg" width="1000" title="STM32 Connected to PC via FTDI">
</p>

A camera module V2 is connected to a Raspberry Pi 3 B. Both are mounted on the vehicle. Raspberry Pi streams captured images to PC over WiFi. Images are parsed by OpenCV and saved as numpy array.

A neural network takes the numpy array and forward/reverse/left/right from human driver as inputs, and outputs 3 commands. The neural network is trained on PC and inference is alos carried out on PC.

These pieces of code are run on:

STM32: rc_drive.ino

Raspberry Pi: picamera_stream_client.py

PC: picamera_stream_server.py, xbox_drive.py

**Neural Network code is still in progress.
