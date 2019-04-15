import pygame, serial

ser = serial.Serial('com7', 115200)

pygame.init()

# !!!IMPORTANT!!! pygame.event doesn't work if a window is not initialized!
size = [250, 250]
screen = pygame.display.set_mode(size)
pygame.display.set_caption("Xbox Controller")

pygame.joystick.init()
joystick = pygame.joystick.Joystick(0)
joystick.init()

clock = pygame.time.Clock()

done = False

deadband = 0.1

a0, a2 = 0, 0

def parseValue(A0, A2):
    if A2 < -deadband:
        if A0 < -deadband:
            ser.write('5'.encode()) # left/forward
        elif A0 > deadband:
            ser.write('7'.encode()) # right/forward
        else:
             ser.write('1'.encode()) # forward

    if A2 > deadband:
        if A0 < -deadband:
            ser.write('4'.encode()) # left/reverse
        elif A0 > deadband:
            ser.write('6'.encode()) # right/reverse
        else:
             ser.write('0'.encode()) # reverse

    if A0 < -deadband:
        if A2 < -deadband:
            ser.write('5'.encode()) # left/forward
        elif A2 > deadband:
            ser.write('4'.encode()) # left/reverse
        else:
            ser.write('2'.encode()) # left

    if A0 > deadband:
        if A2 < -deadband:
            ser.write('7'.encode()) # right/forward
        elif A2 > deadband:
            ser.write('6'.encode()) # right/reverse
        else:
            ser.write('3'.encode()) # right

while done == False:

    # !!!IMPORTANT!!! pygame.event doesn't work if a window is not initialized!
    for event in pygame.event.get():    # all events will be iterated
        if event.type == pygame.QUIT:   # if event is a 'quit'
            done = True # set flag, exit on next loop

        if event.type == pygame.JOYAXISMOTION:  # if event is from joystick
            a0 = joystick.get_axis(0)   # left/right
            a2 = joystick.get_axis(2)   # forward/reverse  
    
    parseValue(a0, a2)  # call function to parse axis values
    
    axisStr = "Axis 0 value: {0:7.3f}, Axis 2 value: {1:7.3f}".format(a0, a2)
    print(axisStr, end = '')
    print('\b' * len(axisStr), end = '', flush = True)

    clock.tick(200) # motor control becomes responsive if this function is called

pygame.quit()
