# RTI_control
## THIS IS AND OLD INSTRUCTION FOR PREVIOUS CODE

## IF YOU ARE LOOKING FOR NEW CODE WITH REMOTE SUPPORT CHECK HERE

Controll RTI screen using arduino and android

Head unit on photo is from facebook group [Legend Volvo XC90 CAR AUDIO](https://www.facebook.com/groups/2444546715858068)
![screen1](https://github.com/TymEK49/RTI_control/blob/main/pictures/Finished_work.jpg)

tip: Do not try to pry with a screwdriver or anything from above. You will damage the material around the navigation, it's too fragile. It is better to remove the airflow below and push the rti cover out from the bottom

Unscrew 5 torx20 and disconnect gray cable. 

copy code from ```app.ino```, compile it and upload on arduino (I prefer arduino nano)
connect arduino TX to RTI 4 pin
connect AV output to RTI 10 pin
connect arduino GND and AV ground to RTI 7 pin
Wiring scheme below

![wiring](https://github.com/TymEK49/RTI_control/blob/main/pictures/arduino_RTI.drawio.png)


Defaut settings after power up are: NTSC and full brightest. You can change it editing line 19 and 20. 
For example, if you don't want the screen to pop up automatically after startup change line 19 to ```signal_state = screen_state[3];```

USB serial commands to control screen:

```ntsc``` - set video format to ntsc, in my opinion best setting

```pal``` - set video format to pal

```rbg``` - set video format to rgb, this setting is default for oryginal navigation

```off``` - turn off and hide screen

```0``` - The darkest screen

```1```

```2```

...

```14```

```15``` - The brightest screen

Commands like ```ntsc,8``` are also supported

## How to control RTI from android/legend unit?

Developing app with simple GUI in progress. If someone has a experience in Android developing app feel free to contact :D
For now I recommend to download this [app](https://play.google.com/store/apps/details?id=de.kai_morich.serial_usb_terminal) and change Receive and Send Newline to '''NUL'''. Just like screenshot ![screen1](https://github.com/TymEK49/RTI_control/blob/main/screenshots/screen1.png)
Press connect in the right corner, wait few second and then you will be able to send commands. You can also set macros below
![screen1](https://github.com/TymEK49/RTI_control/blob/main/screenshots/screen4.png)
![screen1](https://github.com/TymEK49/RTI_control/blob/main/screenshots/screen3.png)
![screen1](https://github.com/TymEK49/RTI_control/blob/main/screenshots/screen2.png)

More instructions and photos in progress
