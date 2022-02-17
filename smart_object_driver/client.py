import socket
import sys
import time

# Script to test the color display of the smart objects

# message: first number = color, 1 -> red, 2 -> green, 3 -> blue
# second number = full or halfs, 1 -> all leds light up, 2 -> half of leds, 3 -> other half
# last 3 digits are for brightness. example: 255 -> full brightness, 0 -> led's off.
# The brightness takes any value in between 0 and 255.
# Examples:
#   color red, all leds, full brightness: 11255
#   color blue, half of leds, brightness = 80: 3280
#   color green, other half of leds, brightness = 120: 23120

# Default arguments
message_type = '4' # clear mission
message = '11255' # red, fully lit

# Process command line arguments
if len(sys.argv > 0):
	message = sys.argv[1]

# Create a TCP/IP socket
sock = socket.create_connection(("192.168.4.1", 3500))

try:
    sock.sendall(message_type.encode('ascii'))
    sock.sendall(message.encode('ascii'))
finally:
    print('closing socket')
    sock.close()
