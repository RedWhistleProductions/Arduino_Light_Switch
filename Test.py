'''
Light Switch
written by Billy Snyder for Public Domain

This is a simple app for testing serial communication with an Arduino Uno
The final app will be to control a RGB light strip connected to an Arduino Uno
'''

import serial
from tkinter import *

# This may need to be changed from COM3 to the port your Arduino is connected to.
# ToDo: create a GUI to change ports in the compiled version
usb = serial.Serial('COM3', 9600)


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
on_switch.grid( row = 0, column = 0)
off_switch.grid( row = 0, column = 1)

# Start the control loop for the main window
window.mainloop()
