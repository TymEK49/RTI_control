//Have fun! Greetings from Tymek Be
String ab[10];
String data;
String sectionData;
int a;
int b;
int stringData;

char screen_state[] = {0x40, 0x45, 0x4C, 0x46}; // RTI_RGB, RTI_PAL, RTI_NTSC. RTI_OFF
char screen_brightnes[] = {0x20, 0x61, 0x62, 0x23, 0x64, 0x25, 0x26, 0x67, 0x68, 0x29, 0x2A, 0x2C, 0x6B, 0x6D, 0x6E, 0x2F}; // brightness from 0 to 15

char signal_state;
char signal_brightnes;

void setup()
{
  Serial.begin(2400);
  // default settings after start:
  signal_state = screen_state[2]; // RTI_NTSC
  signal_brightnes = screen_brightnes[15]; // full brightness
}
  

void loop()
{
  Serial.print(signal_state);
  delay(50);
  Serial.print(signal_brightnes); // {0x20, 0x61, 0x62, 0x23, 0x64, 0x25, 0x26, 0x67, 0x68, 0x29, 0x2A, 0x2C, 0x6B, 0x6D, 0x6E, 0x2F};
  delay(50);
  Serial.print((char)0x83); // must have, volvo things
  delay(50);
  
  while (Serial.available() > 0)
  {
    data = Serial.readString();

    for (a = 0; a < data.length() - 1; a++)
    {
      // split data based on comma (,)
      ab[a] = getData(data, ',', a);

      // Signal_type
      if (ab[a] == "rgb")
      {
        signal_state = screen_state[0];
      }   
      if (ab[a] == "pal")
      {
        signal_state = screen_state[1];       
      }
      if (ab[a] == "ntsc")
      {
        signal_state = screen_state[2];
      }   
      if (ab[a] == "off")
      {
        signal_state = screen_state[3];       
      }

      // Brightness
      for (b = 0; b < 16; b++)
      {
        if (ab[a] == String(b))
        {
          signal_brightnes = screen_brightnes[b];
        }
      }
    }
  }
}

//Read data from serial usb
String getData(String data, char delimiter, int sequence)
{
  stringData = 0;
  sectionData = "";

  for (int i = 0; i < data.length() - 1; i++)
  {
    if (data[i] == delimiter)
    {
      stringData++;
    }
    else if (stringData == sequence)
    {
      sectionData.concat(data[i]);
    }
    else if (stringData > sequence)
    {
      return sectionData;
      break;
    }
  }

  return sectionData;
}
