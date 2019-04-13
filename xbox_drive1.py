# !!!IMPORTANT!!! pygame.event doesn't work if a window is not initialized!
# this is a more refined version than xbox.py

import pygame, serial

ser = serial.Serial('com4', 9600)

pygame.init()

size = [250, 250]
screen = pygame.display.set_mode(size)
pygame.display.set_caption("Xbox Controller")

pygame.joystick.init()
joystick = pygame.joystick.Joystick(0)
joystick.init()

clock = pygame.time.Clock()

done = False

deadband = 0.1

x = 0

while done == False:
    
    for event in pygame.event.get(): # User did something
        if event.type == pygame.QUIT: # If user clicked close
            done=True # Flag that we are done so we exit this loop

        if event.type == pygame.JOYAXISMOTION:
            a0 = joystick.get_axis(0)
            a2 = joystick.get_axis(2)

            # this pyserial part requires a program on arduino
            if a0 < -deadband and a2 > deadband:
                ser.write('4'.encode()) # left/reverse

            if a0 < -deadband and a2 < -deadband:
                ser.write('5'.encode()) # left/forward

            if a0 > deadband and a2 > deadband:
                ser.write('6'.encode()) # right/reverse

            if a0 > deadband and a2 < -deadband:
                ser.write('7'.encode()) # right/forward

            if a2 < -deadband:
                ser.write('1'.encode()) # this encodes unicode 1 to ascii 1, forward command

            if a2 > deadband:
                ser.write('0'.encode()) # reverse command

            if a0 < -deadband:
                ser.write('2'.encode()) # left command

            if a0 > deadband:
                ser.write('3'.encode()) # right command, this axis can't really return to centre, a large value selected to avoid sending command when in centre
    
            axisStr = "Axis 0 value: {0:7.3f}, Axis 2 value: {1:7.3f}".format(a0, a2)
            print(axisStr, end = '')
            print('\b' * len(axisStr), end = '', flush = True)
            print('event inside happened')
    
    clock.tick(10)
    print('event happened {}'.format(x))    # these lines are excuted every frame, thus also controlled by clock.tick()    
    x = x + 1

pygame.quit()