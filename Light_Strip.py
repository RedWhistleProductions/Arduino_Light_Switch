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

def serial_out(C):
    '''

    '''
    usb.write(C.encode())

# Setup a basic window and set the title
window = Tk()

window.title("Light Switch")




# Add an on button and a off button to the window and assign their command functions
off_switch = Button(window, text = "Off", command = lambda: serial_out('0')).grid(row=1)
White = Button(window, text = "White", command = lambda: serial_out('1')).grid( row = 2)
Red = Button(window, text = "Red", background = "Red", command = lambda: serial_out('2')).grid( row = 3)
Orange = Button(window, text = "Orange", background = "Orange", command = lambda: serial_out('3')).grid( row=4)
Yellow = Button(window, text = "Yellow", background = "Yellow", command = lambda: serial_out('4')).grid( row =5)
Green = Button(window, text = "Green", background = "Green", command =  lambda: serial_out('5')).grid(row =6)
Blue = Button(window, text = "Blue", background = "Blue", command = lambda: serial_out('6')).grid(row = 7)
Cyan = Button(window, text = "Cyan", background = "Cyan", command = lambda: serial_out('7')).grid(row = 8)
Violet = Button(window, text = "Violet", background = "Purple", command = lambda: serial_out('8')).grid(row = 9)



# Start the control loop for the main window
window.mainloop()
