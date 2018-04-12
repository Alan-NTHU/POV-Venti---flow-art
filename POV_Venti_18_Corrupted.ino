/*  Arduino328_APA102_SD/ornot POV stick

    designed by Po Ting Chen , NTHU GPC, 2016
    Free for non-commercial use , but should include this declaration in any copy or any edited/or not distribution
    And Should Aware the audience the origin of the POV program

    For commercial use, contact Po Ting, Taiwan, +886979586721
    alans7077@yahoo.com.tw

    SD formatted with FAT16>FAT32 - 16 KBytes gets a slightly faster(5~10%) FPS with
    a average of 34000pixels/s, made it almost 290 frame/s , with 128MB cards


    Debug LightOn() List

   -LightOn(1) = Boot succeeded
   -LightOn(2) = Fail@SD setup
   -LightOn(3) = failure @ mapping
   -LightOn(4) = failure @ dataform
   -LightOn(5) = Fail@Reading file


   for a full white 18 LEDs , FastLED.show()
   costs 888 microseconds(us) w/8-16Mhz ,  928 w/4Mhz, 1016 w/2Mhz, 1760 w/1Mhz

   for a full black 18 LEDs , FastLED.show()
   costs 820 microseconds(us) w/8-16Mhz , 864 w/4Mhz,  944 w/2Mhz, 1696 w/1Mhz


    written at 2016/2/10
*/

#include <FastLED.h>          // Library for the apa102
#include <SD.h>                          // Library for the SD Card
#include <SPI.h>                         // Library for the SPI Interface
//#include <EEPROM.h>                   // not using, for setting storagement.

//-----------for apa102
#define NUM_LEDS    18
#define BRIGHTNESS  127  // 0-255 depends on need,warning! power drain is a trouble above 80 bright.
CRGB leds[NUM_LEDS];
TBlendType    currentBlending;
uint8_t lastSecond = 0 ;
uint8_t  secondHand = 4;

const byte PROGMEM  SDPin = 10;               // SD card CS pin; UNO R3&Nano&Pro micro & TEENSY3.1/LC/++ 11MOSI,12MISO,13SCK
byte g = 0;                                // Variable for the Green Value
byte b = 0;                                // Variable for the Blue Value
byte r = 0;                                // Variable for the Red Value
byte frameDelay = 0;
byte x;
File root;

#define FILELIMIT 40
//String m_CurrentFilename = "";
byte m_NumberOfFiles = 0;
byte m_FileIndex = 0;
//unsigned int m_FileDur[16];  //
String m_FileNames[FILELIMIT] = {};   // could be more, must test before use

boolean SDavail = true;

void setup() {
  analogReference(INTERNAL);
  Serial.begin(9600);
  
  pinMode(2, INPUT);  // le backup for pin 3
  digitalWrite(2, LOW);
  pinMode(5, INPUT);  // le backup for pin 3
  digitalWrite(5, LOW);
  pinMode(9, INPUT);  // le backup for pin 10
  digitalWrite(9, LOW);

  FastLED.addLeds<APA102, 3, 4, BGR, DATA_RATE_MHZ(8)>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  LightOn(1);
  //setupLEDs(); // start signal anyway
  FastLED.clear();
  FastLED.show();
  ifCharge();
  setupSD();
  ClearStrip(1);


  /* le test for showing blank
    long counter=micros();
    FastLED.clear();
    FastLED.show();
    Serial.println("time for blanked show");
    Serial.println(micros()-counter);
  */
}

void loop() {
  while (SDavail) {
    autoshow();
  }
  //while (!SDavail) {
  // constshow();
  //  }
}

void autoshow() {
  for (x = 0; x < m_NumberOfFiles; x++) {
    m_FileIndex = x;
    SendFile(m_FileNames[x]);
  }
}

//for debug

void LightOn(byte y) {
  for (byte m = 0; m < y; m++) {
    for (byte n = 0; n < NUM_LEDS; n++) {
      leds[n].setRGB(255, 255, 255);
    }
    FastLED.show();
    delay(100);
    ClearStrip(100);

    /* le test for showing all white
      for (byte n = 0; n < NUM_LEDS; n++) {
      leds[n].setRGB(255, 255, 255);
      }
      long counter2 = micros();
      FastLED.show();
      Serial.println("time for full white show");
      Serial.println(micros() - counter2);
    */

  }
}

void ClearStrip(int duration) {
  byte m;
  for (m = 0; m < NUM_LEDS; m++) {
    leds[m].setRGB(0, 0, 0);
  }
  FastLED.show();
  delay(duration);
}


