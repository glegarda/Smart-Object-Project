# Describtion
This application contains drivers and a control software for the device called Smart-Object.
Tcp-connection -> Ip address and port number: `192.168.4.1 3500`.
The configuration string has always a length of 8 chars.
Colors mapping: "1" -> red, "2" -> green, "3" -> blue


## Test the display color by the device.

1. Connect to the wi-fi network called "esp32" (no password required).
2. Send "4" over the tcp-connection.
3. Send the configuration.
Format of the configuration for testing:
Length: 5 chars. First char specifies the color. Second char specifies which half of LEDs to light up. 
The last three chars specify the intensity of the color (0 -> led's off, 255 -> full brightness).
Colors mapping: "1" -> red, "2" -> green, "3" -> blue
Example: 11255 -> red color on all LEDs with a full brightness.
The configuration should be sent as a string of 8 chars. First 5 chars are reserved for the configuration. The other
3 are reserved for a future use. The example above should be sent as "11255000".


## Launch a mission.
The device is configured for 3 different missions. 
To launch a mission, follow these steps:
1. Connect to the wi-fi network called "esp32" (no password required).
2. Send "5" over the tcp-connection.
3. -To launch the mission 1: Send "1x000000" where x is a char representing the color to initially display.
   -To launch the mission 2: Send "20000000".
   -To launch the mission 3: Send "30000000".
   -To stop the mission in progress: Send "40000000".

## Calibrate the ground sensor.
1. For the white/black color, place the device on the white/black floor.
2. Connect to the wi-fi network called "esp32" (no password required).
3. Send "5" over the tcp-connection.
4. For the white, send "50000000". For the black, send "60000000".

## Calibrate the accelerometer.
The calibration of the accelerometer is done automatically before the start of the mission 
involving the accelerometer sensor.


### Python scripts
Python script called "client.py" contains the client where different configurations can be set
and send to the server.


## Build and Flash

Build the project and flash it to the board, then run monitor tool to view serial output:

```
alias get_idf='. $HOME/esp/esp-idf/export.sh'
get_idf
idf.py -p PORT flash monitor
```

(To exit the serial monitor, type ``Ctrl-]``.)

Command to get the usb PORT:  ls /dev/tty*


