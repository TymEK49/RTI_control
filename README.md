# RTI Control

<details>
<summary>Standat disclaimer notice</summary>

I am not taking any resposibility for bricked arduino, damaged RTI or any other damaged thing in your car. Always remember to cover metal pieces from arduino to avoid any electric damage. 
</details>

  

I'm happy to present to you my updated code for taking control over Volvo RTI satnav screen.
![screen1](https://github.com/TymEK49/RTI_control/blob/main/pictures/Finished_work.jpg)
Head unit on photo is from facebook group [Legend Volvo XC90 CAR AUDIO](https://www.facebook.com/groups/2444546715858068)

This mod should work on any P2 Volvo RTI screen (like xc90, xc70, s80 etc). You can connect your navigation screen to any analog video source, like android heaunits, miracast, reverse camera etc. 

[!video](https://youtu.be/I0WuGjVyAK0)

## Code Functions: 
- changing screen mode (rgb, pal, ntsc, off)
- changing brightness
- changing screen modes and brightness via OE remote
- changing screen modes and brightness via Serial USB commands
- saving last states to EEPROM

## What's new? 
I decoded the OE Volvo IR Remote (30657371-1) and set up to control the screen. Also, I added remembering the last state of on/off, brightness and hotkeys.

## How to use the remote?
<ul>
    <li><strong>up</strong> - on (ntsc)</li>
    <li><strong>down</strong> - off</li>
    <li><strong>left</strong> - dim the screen</li>
    <li><strong>right</strong> - brighten the screen</li>
    <li><strong>enter</strong> - brightness hotkey (by default full)</li>
    <li><strong>back</strong> - brightness hotkey (by default 20%)</li>
</ul> 

## How to use the USB serial commands?
<ul>
  <li><strong>n</strong> - ntsc mode (this is default ON option)</li>
  <li><strong>p</strong> - pal mode</li>
  <li><strong>r</strong> - rgb mode (this one OE satnav is using)</li>
  <li><strong>o</strong> - off</li>
  <li><strong>0</strong> - brightness 0 (darkest screen) </li>
  <li><strong>1</strong> - brightness 1</li>
  <li><strong>2</strong> - brightness 2</li>
  <li>...</li>
  <li><strong>9</strong> - brightness 9</li>
  <li><strong>a</strong> - brightness 10</li>
  <li><strong>b</strong> - brighntess 11</li>
  <li>...</li>
  <li><strong>f</strong> - brightness 15 (brightest screen)</li>
  <li><strong>+</strong> - save current brightness as hotkey ENTER</li>
  <li><strong>-</strong> - save current brightness as hotkey BACK</li>
  <li><strong>x</strong> - RTI will stay on, but will be off in next boot (this one is for android app development)</li>
</ul> 

## Parts, tools, skills needed
- arduino (It doesn't really matter which arduino you choose. It doesn't have to be original either. I recommend the cheapest arduino/seeeduino nano you can find.)
- RCA plug (can be with screws for easier installation) or rca cable you can cut and solder
- some dupont wires (standart cables) 
- plastic case or isolation tape to protect arduino and your car from damage
- USB to AV adapter - I know adapters on processor family MS91XX works 
- (optional) arduino screw shield (its easier to connect cables)
- (optional but recommended) soldering iron - it's bteer to solder wires to make connection stronger. Remember - this is analog video signal and can be easly distorted.

## Installation
If you are upgrading your arduino from previos version to current you have to add one wire between RTI pin 5 and RX on arduino. Also, take a look at new USB commands.

### Compile and upload

Download '''rti_control_with_remote.ino''' compile and upload it to your arduino. 
If you are not familiar with arduino IDE don't worry. just download the Arduino IDE for your computer (https://docs.arduino.cc/software/ide-v1) then folow first 7 steps from official guide 'Using the offline IDE 1.x.x' - https://docs.arduino.cc/learn/starting-guide/the-arduino-software-ide. Then navigate to File > Open > select rti_control_with_remote.ino whoch you downloaded and select upload. 
To verify if everything is uloaded correctly open 'Serial monitor' (icon in up-right corner) select 'baud 2400' and see if some code is running. 

#### Troubleshooting:
> I got some errors uploading, what I have to do? 

If you are using Arduino Nano propably you have another processor selected. Go to Tools > Processor and select option with 'older bootloader'

### Getting to RTI

This process is for XC90. 
<details>
<summary>Click to open gallery</summary>

Remove the grid around the rti screen.
tip: Do not try to pry with a screwdriver or anything from above. You will damage the material around the navigation, it's too fragile. It is better to remove the airflow below and push the rti cover out from the 

![01](https://github.com/TymEK49/RTI_control/blob/main/pictures/installation/01.jpg)

![02](https://github.com/TymEK49/RTI_control/blob/main/pictures/installation/02.jpg)

Disconnect cable from hazard lights

![03](https://github.com/TymEK49/RTI_control/blob/main/pictures/installation/03.jpg)

Push RTI cover from below 

![04](https://github.com/TymEK49/RTI_control/blob/main/pictures/installation/04.jpg)

Unscrew 5 torx20 and disconnect GRAY cable from RTI (BLUE is power).

![RTI](https://github.com/TymEK49/RTI_control/blob/main/pictures/RTI_connectors.png)
</details>


### Wiring

Prepare cables like on scheme below

![wiring](https://github.com/TymEK49/RTI_control/blob/main/pictures/RTI_REMOTE_schema.png)

My wires:

Arduino cables:
![09](https://github.com/TymEK49/RTI_control/blob/main/pictures/installation/09.jpg) 
just add here third cable for remote control!

Video cables:
![10](https://github.com/TymEK49/RTI_control/blob/main/pictures/installation/10.jpg) 

You can also connect GND from Arduino to GND Video.

- connect arduino TX to RTI 4 pin
- connect arduino RX to RTI 5 pin
- connect AV output to RTI 10 pin
- connect arduino GND and AV ground to RTI 7 pin
(if you have troubles to connect GND to arduino and AV video output at the same time, you can use RTI metal frame as GND for arduino 😉)

<strong>IMPORTANT! Remember to cover arduino body from any metal of your car! Use some plastic case or even isolation tape!</strong>

![05a](https://github.com/TymEK49/RTI_control/blob/main/pictures/installation/05a.jpg)
My new setup



![05b](https://github.com/TymEK49/RTI_control/blob/main/pictures/installation/05b.jpg) 
This is from previous installtion, please rember to add cable betwen RX and PIN 5 on RTI.

![06](https://github.com/TymEK49/RTI_control/blob/main/pictures/installation/06.jpg)
On this photo serial from remote controll cable is missing, please rember to plug in pin 5 on RTI.
Also, you can see that I forgot to solder GND cables to ech other, so I just used metal frame as GND for arduino. 

If you are installing this mod for Legend Android Head Unit, here is the moment to connect everything to USB hub and hide it.

![07](https://github.com/TymEK49/RTI_control/blob/main/pictures/installation/07.jpg)

![08](https://github.com/TymEK49/RTI_control/blob/main/pictures/installation/08.jpg)

Remember to check if everything works before 

## OPTIONAL - sending commands from android

You don't have to install it to make RTI work, it's optional. 
GUI app in planns. 
For now I recommend to download this [app](https://play.google.com/store/apps/details?id=de.kai_morich.serial_usb_terminal) and load this configuration '''RTI_serial_usb_terminal_cfg.txt'''

![screen05](https://github.com/TymEK49/RTI_control/blob/main/screenshots/screen05.png)

You will got everything set.

Now press connect button ![screen07](https://github.com/TymEK49/RTI_control/blob/main/screenshots/screen07.png) and see the matrix in terminal 😁

Buttons 'Enter key' and 'Back key' will save current brightness to hotkeys. Rest USB commands see in chapter 'How to use the USB serial commands'.

## Thanks

I would like to say thank you to those people:
- Piotr Kamoda for initial code to start RTI, schemas and knowledge
- Sylwester Turski for helping me to manage delays in remote signal
- Liam Sears for tests and ideas
- Alen Osmanovic for tests
- Roman Majdiš for tests and ideas
- Rurik Wolfe for updated RTI connector scheme

This code is free to use but I'll be glad if you buy me coffee or beer 😁

![revolut](https://github.com/TymEK49/RTI_control/blob/main/screenshots/revolut.png)
revolut.de/tymotedz18
