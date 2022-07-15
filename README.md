# RTI_control
Controll RTI screen using arduino and android

![wiring](https://github.com/TymEK49/RTI_control/blob/main/arduino_RTI.drawio.png)

copy code, compile it and upload on arduino (I prefer arduino nano)
connect arduino TX to RTI 4 pin
connect AV output to RTI 10 pin
connect arduino GND and AV ground to RTI 7 pin

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

More instructions and photos in progress
