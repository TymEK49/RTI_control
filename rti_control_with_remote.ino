//  Have fun! Greetings from Tymek Be
//  Whole tutorial and 'how to' on
//  https://github.com/TymEK49/RTI_control
//
//  Connectors: 
//  RX  -> 5 pin RTI
//  TX  -> 4 pin RTI
//  GND -> 7 pin RTI


#include <EEPROM.h>
//EEPROM index: 0 RTI mode, 1 default brightness, 2 enter key brightness, 3 back key brightness

String ab[10];
String data;
String sectionData;
int a;
int b;
int stringData;
int last_RTI_mode;
int last_RTI_brightness;
int last_enter_brightness;
int last_back_brightness;
int index_brightness;
int index_enter;
int index_back;
const int BUFFER_SIZE = 4;
const long DEBOUNCE_TIME_MILS = 750;
char remote_signal[BUFFER_SIZE];
char last_signal[BUFFER_SIZE];
long last_signal_time = 0;
char screen_state[]       = {0x40, 0x45, 0x4C, 0x46}; // RTI_RGB, RTI_PAL, RTI_NTSC, RTI_OFF
char codes_state[]        = {0x72, 0x70, 0x6E, 0x6F}; //keys r, p, n, o
char screen_brightness[]  = {0x20, 0x61, 0x62, 0x23, 0x64, 0x25, 0x26, 0x67, 0x68, 0x29, 0x2A, 0x6B, 0x2C, 0x6D, 0x6E, 0x2F}; // brightness from 0 to 15
char codes_brightness[]   = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66}; //keys 0-9, a, b, c, d, e, f
char up1[BUFFER_SIZE]     = {0xED, 0xAF, 0xBD, 0xFD}; 
char up2[BUFFER_SIZE]     = {0xED, 0xAF, 0xFD, 0xFD}; 
char up3[BUFFER_SIZE]     = {0xED, 0xEF, 0xBD, 0xFD}; 
char down1[BUFFER_SIZE]   = {0xED, 0xAD, 0xAF, 0xFF}; 
char down2[BUFFER_SIZE]   = {0xED, 0xAD, 0xEF, 0xFF}; 
char left1[BUFFER_SIZE]   = {0xED, 0xBD, 0xBD, 0xFD}; 
char left2[BUFFER_SIZE]   = {0xED, 0xBD, 0xFD, 0xFD}; 
char left3[BUFFER_SIZE]   = {0xED, 0xFD, 0xBD, 0xFD}; 
char right1[BUFFER_SIZE]  = {0xED, 0xEF, 0xAF, 0xED}; 
char right2[BUFFER_SIZE]  = {0xED, 0xEF, 0xEF, 0xED}; 
char enter[BUFFER_SIZE]   = {0xED, 0xEF, 0xED, 0xED}; 
char back1[BUFFER_SIZE]   = {0xED, 0xBD, 0xEF, 0xED}; 
char back2[BUFFER_SIZE]   = {0xED, 0xFD, 0xEF, 0xED}; 
char signal_state;
char signal_brightness;


void setup()
{
  Serial.begin(2400);
  checkPowerState();
  checkBrightnessState();
  checkEnterState();
  checkBackState();
}
  
void loop()
{
  Serial.print(signal_state);
  delay(50);
  Serial.print(signal_brightness); // {0x20, 0x61, 0x62, 0x23, 0x64, 0x25, 0x26, 0x67, 0x68, 0x29, 0x2A, 0x2C, 0x6B, 0x6D, 0x6E, 0x2F};
  delay(50);
  Serial.print((char)0x83); // must have, volvo things
  delay(50);
  if (Serial.available() > 0) {
      int rlen = Serial.readBytesUntil('\n', remote_signal, sizeof(remote_signal));
      debounceSignal(remote_signal);
  }
}

void checkPowerState() {
  // check if EEPROM memory is in 10 - 14 range 
  last_RTI_mode = EEPROM.read(0);
  for (b = 10; b < 14; b++){
    if (last_RTI_mode == b){
      last_RTI_mode = b - 10;
      signal_state = screen_state[last_RTI_mode];
      return;
    }
  }
  last_RTI_mode = 2;
  signal_state = screen_state[last_RTI_mode];
  EEPROM.update(0, last_RTI_mode + 10);
}

void checkBrightnessState() {
  // check if EEPROM memory is in 10 - 25 range 
  last_RTI_brightness = EEPROM.read(1);
  for (b = 10; b < 26; b++){
    if (last_RTI_brightness == b){
      index_brightness = b - 10;
      signal_brightness = screen_brightness[index_brightness];
      return;
    }
  }
  index_brightness = 15;
  signal_brightness = screen_brightness[index_brightness];
  EEPROM.update(1, index_brightness + 10);
}


void checkEnterState() {
  // check if EEPROM memory is in 10 - 25 range 
  last_enter_brightness = EEPROM.read(2);
  for (b = 10; b < 26; b++){
    if (b == last_enter_brightness){
      index_enter = b - 10;
      // Serial.println(index_enter);
      return;
    }
  }
  index_enter = 15;
  EEPROM.update(2, index_enter + 10);
}

void checkBackState() {
  // check if EEPROM memory is in 10 - 25 range 
  last_back_brightness = EEPROM.read(3);
  for (b = 10; b < 26; b++){
    if (b == last_back_brightness){
      index_back = b - 10;
      return;
    }
  }
  index_back = 3;
  EEPROM.update(3, index_back + 10);
}

void debounceSignal(char signal[4]) {
    if (millis() - last_signal_time < DEBOUNCE_TIME_MILS)
        return;
    memcpy(last_signal, signal, 4);
    last_signal_time = millis();
    handleSignal(remote_signal);
}

void handleSignal(char signal[4]) {
    if (memcmp(signal, up1, 4) == 0 || memcmp(signal, up2, 4) == 0 || memcmp(signal, up3, 4) == 0){
      signal_state = screen_state[2];
      EEPROM.update(0, 12);
    }
    if (memcmp(signal, down1, 4) == 0 || memcmp(signal, down2, 4) == 0) {
      signal_state = screen_state[3];
      EEPROM.update(0, 13);
    }
    if (memcmp(signal, left1, 4) == 0 || memcmp(signal, left2, 4) == 0 || memcmp(signal, left3, 4) == 0){
      if (index_brightness > 0 && index_brightness < 16){
        index_brightness = index_brightness - 1;
        signal_brightness = screen_brightness[index_brightness];
        EEPROM.update(1, index_brightness + 10);
      }
    }
    if (memcmp(signal, right1, 4) == 0 || memcmp(signal, right2, 4) == 0) {
      if (index_brightness >= 0 && index_brightness < 15){
        index_brightness = index_brightness + 1;
        signal_brightness = screen_brightness[index_brightness];
        EEPROM.update(1, index_brightness + 10);
      }
    }
    if (memcmp(signal, enter, 4) == 0) {
      signal_brightness = screen_brightness[index_enter];
      index_brightness = index_enter;
      EEPROM.update(1, index_brightness + 10);
    }
    if (memcmp(signal, back1, 4) == 0 || memcmp(signal, back2, 4) == 0) {
      signal_brightness = screen_brightness[index_back];
      index_brightness = index_back;
      EEPROM.update(1, index_brightness + 10);
    }
    else{
      commandsUSB(signal);
    }
}

void commandsUSB(char signal[4]) {  
  for (b = 0; b < 4; b++){
    if (signal[0] == codes_state[b]){
      signal_state = screen_state[b];
      EEPROM.update(0, b + 10);
    }
  }
  for (b = 0; b < 16; b++){
      if (signal[0] == codes_brightness[b]){
        signal_brightness = screen_brightness[b];
        index_brightness = b;
        EEPROM.update(1, b + 10);
      }
    }
  if (signal[0] == char(0x78)){
  // sending 'x' key will set RTI in off after next boot, this is for android development purpose  
    EEPROM.update(0, 3);
  }
  if (signal[0] == char(0x2B)){
  // sending '+' key will set current brightness as ENTER keylast_RTI_brightness
    index_enter = index_brightness;
    EEPROM.update(2, index_enter + 10);
  }
  if (signal[0] == char(0x2D)){
  // sending '-' key will set current brightness as BACK key  
    index_back = index_brightness;
    EEPROM.update(3, index_back + 10);
  }
}
