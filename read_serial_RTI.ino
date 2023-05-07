int b;
const int BUFFER_SIZE = 3;
char buf[BUFFER_SIZE];
char screen_brightnes[] = {0x20, 0x61, 0x62, 0x23, 0x64, 0x25, 0x26, 0x67, 0x68, 0x29, 0x2A, 0x2C, 0x6B, 0x6D, 0x6E, 0x2F}; // brightness from 0 to 15

void setup() {
  Serial.begin(2400); // opens serial port, sets data rate to 2400 bps
}

void loop() {
  // check if data is available
  if (Serial.available() > 0) {
    // read the incoming bytes:
    int rlen = Serial.readBytesUntil('\n', buf, BUFFER_SIZE);

    // prints the received data
//    Serial.println("");
    for(int i = 0; i < rlen; i++)
    {
      for (b = 0; b < 16; b++)
      {
        if (buf[i] == screen_brightnes[b])
        {
          Serial.println(b);
        }
      }
    }
  }
}
