## Description
This application contains drivers and a control software for the device called Smart-Object.
Tcp-connection -> Ip address and port number: `192.168.4.1 3500`.
The configuration string has always a length of up to 8 chars.
Colors mapping: "1" -> red, "2" -> green, "3" -> blue


### Test the display color by the device.
1. Connect to the wi-fi network called "esp32" (no password required).
2. Send "4" over the tcp-connection.
3. Send the configuration.
Format of the configuration for testing:
Length: 5 chars. First char specifies the color. Second char specifies which sector will light up (1 -> all sectors, 2 -> three sectors, 3 -> four sectors)
The last three chars specify the intensity of the color (0 -> led's off, 255 -> full brightness).
Colors mapping: "1" -> red, "2" -> green, "3" -> blue
Example: "11255" -> red color on all LEDs with a full brightness.


### Launch a mission.
The device is configured for 3 different missions. 
To launch a mission, follow these steps:
1. Connect to the wi-fi network called "esp32" (no password required).
2. Send "5" over the tcp-connection.
3. -To launch the mission 1: Send "1x" where x is a char representing the color to initially display.
   -To launch the mission 2: Send "2".
   -To launch the mission 3: Send "3".
   -To stop the mission in progress: Send "4".


### Calibrate the ground sensor.
1. For the white/black color, place the device on the white/black floor.
2. Connect to the wi-fi network called "esp32" (no password required).
3. Send "5" over the tcp-connection.
4. For the white, send "5". For the black, send "6".


### Calibrate the accelerometer.
The calibration of the accelerometer is done automatically before the start of the mission 
involving the accelerometer sensor.


### Python scripts
Python script called "client.py" contains the client where different configurations can be set
and send to the server.


## Build and Flash

To build and flash the project to the board, first set up ESP-IDF environment (instructions for Linux taken from [ESP-IDF Programming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html)) (_Note: if you have already set up your environment and just need a refresher to know how to build and flash your code, skip to the end of the section_):
1. Download prerequisites:
```
sudo apt install git wget flex bison gperf python3 python3-pip python3-setuptools cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0
```

2. Make sure the user has access to the serial ports (reboot afterwards for the changes to take effect):
```
sudo usermod -a -G dialout $USER
```

3. Download ESP-IDF:
```
mkdir -p ~/esp
cd ~/esp
git clone --recursive https://github.com/espressif/esptool.git
```

4. Set up tools (if argument `esp32` is given, as per the documentation, step #5 will fail)
```
cd ~/esp/esp-idf
./install.sh
```

5. Set alias in `.bashrc` to quickly set up all environment variables in this and future sessions:
```
echo "alias get_idf='. $HOME/esp/esp-idf/export.sh'" >> ~/.bashrc
source ~/.bashrc
```

6. Set up environment variables. This must be done **every time** a new terminal session is started to work with ESP-IDF:
```
get_idf
```

The following command needs to be executed only once to start a new project:
```
idf.py set-target esp32
```

Then, to build the project:
```
idf.py build
```
A successful build should end with message like:
```
Project build complete. To flash, run this command:
[...]
or run 'idf.py -p (PORT) flash'
```
where [...] contains a long command.

Finally, flash onto device (assuming `PORT` is `/dev/ttyUSB0`). **IMPORTANT**: if the following command fails with "A fatal error occurred: Failed to connect to ESP32: Wrong boot mode detected (0x13)! The chip needs to be in download mode.", try holding the BOOT button on the board while running the command before looking at the Troubleshooting section of the documentation:
```
idf.py -p /dev/ttyUSB0 flash
```
A successful flash should end with message like:
```
Leaving...
Hard resetting via RTS pin...
Done
```

To monitor the serial output, run:
```
idf.py -p /dev/ttyUSB0 monitor
```
To then quit the monitor tool, type `Ctrl + ]`.

Building, flashing and monitoring can all be done with a single command:
```
idf.py -p /dev/ttyUSB0 flash monitor
```

In the future, to modify and flash an project, just open a new terminal session and run the following commands:
```
get_idf
idf.py -p /dev/ttyUSB0 flash monitor
```
