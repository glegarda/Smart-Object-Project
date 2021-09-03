import socket
import sys
import time


#message: first number = color, 1 -> red, 2 -> green, 3 -> blue
# second number = full or halfs, 1 -> all leds light up, 2 -> half of leds, 3 -> other half
# last 3 digits are for brightness. example: 255 -> full brightness, 0 -> led's off.
#The brightness takes any value in between 0 and 255.
#Examples: color red, all leds, full brightness: 11255
#color blue, half of leds, brightness = 80: 3280
#color green, other half of leds, brightness = 120: 23120

# Create a TCP/IP socket
sock = socket.create_connection(("192.168.4.1", 3500))

try:
    
    # Send data
    message_type = '3'
    message = '310'  #message to send
    sock.sendall(message_type.encode('ascii'))
    sock.sendall(message.encode('ascii'))
finally:
    print('closing socket')
    sock.close()
