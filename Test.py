'''
Light Switch
written by Billy Snyder for Public Domain

This is a simple app for testing serial communication with an Arduino Uno
The final app will be to control a RGB light strip connected to an Arduino Uno
'''

import serial
import serial.tools.list_ports as Port_List
from tkinter import *


def Connect():
    # Scan the ports for an arduino or arduino clone
    Ports = list(Port_List.comports())

    commPort = 'None'

    for P in Ports:
        strPort = str(P)
        if 'Arduino' in strPort or 'CH340' in strPort:
            splitPort = strPort.split(' ')
            commPort = splitPort[0]
            return serial.Serial(commPort, 9600)
    return 'None'


usb = Connect()

def light_on():
    '''
        sends a 1 to the Arduino to turn the light on
    '''
    usb.write('1'.encode())


def light_off():
    '''
        sends a 0 to the Arduino to turn the light off
    '''
    usb.write('0'.encode())


# Setup a basic window and set the title
window = Tk()

window.title("Light Switch")




# Add an on button and a off button to the window and assign their command functions
on_switch = Button(window, text = "On", command = light_on)
off_switch = Button(window, text = "Off", command = light_off)

# Position the buttons on the window
on_switch.grid( row = 2, column = 0)
off_switch.grid( row = 2, column = 1)

# Start the control loop for the main window
window.mainloop()
