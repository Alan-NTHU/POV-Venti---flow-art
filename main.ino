
void ShowTheFile() {
  Serial.println(F("reading"));
#define MYBMP_BF_TYPE           0x4D42
#define MYBMP_BF_OFF_BITS       54
#define MYBMP_BI_SIZE           40
#define MYBMP_BI_RGB            0L
#define MYBMP_BI_RLE8           1L
#define MYBMP_BI_RLE4           2L
#define MYBMP_BI_BITFIELDS      3L
  unsigned int frame = 0;
  uint16_t bmpType = readInt();
  //uint32_t bmpSize =
  readLong();
  // uint16_t bmpReserved1 =
  readInt();
  // uint16_t bmpReserved2 =
  readInt();
  uint32_t bmpOffBits = readLong();
  bmpOffBits = 54;

  /* Check file header */
  if (bmpType != MYBMP_BF_TYPE || bmpOffBits != MYBMP_BF_OFF_BITS) {
    LightOn(3);
    Serial.println(F("fail@map"));
    return;
  }

  /* Read info header */
  uint32_t imgSize = readLong();
  uint32_t imgWidth = readLong();
  uint32_t imgHeight = readLong();
  uint16_t imgPlanes = readInt();
  uint16_t imgBitCount = readInt();
  uint32_t imgCompression = readLong();
  uint32_t imgSizeImage = readLong();
  // uint32_t imgXPelsPerMeter =
  readLong();
  // uint32_t imgYPelsPerMeter =
  readLong();
  // uint32_t imgClrUsed =
  readLong();
  // uint32_t imgClrImportant =
  readLong();
  uint32_t lineLength = imgWidth * 3;
  unsigned long Time = millis() + 6000;
  int displayWidth = imgWidth;
  int y = imgHeight;
  /* Check info header */
  if ( imgSize != MYBMP_BI_SIZE || imgWidth <= 0 ||
       imgHeight <= 0 || imgPlanes != 1 ||
       imgBitCount != 24 || imgCompression != MYBMP_BI_RGB ||
       imgSizeImage == 0 )
  {
    LightOn(4);
    Serial.println(F("fail@dataform"));
    delay(10);
    //debug=true;
    return;
  }

  if (imgWidth > NUM_LEDS) {
    displayWidth = NUM_LEDS;           //only display the number of led's we have
  }

  /* compute the line length */

  if ((lineLength % 4) != 0) {
    lineLength = (lineLength / 4 + 1) * 4;
  }
  do {
    // Serial.println(F("READING"));
    //FastLED.clear();
    if (y == 0) {
      y = imgHeight;
    }
    //int bufpos = 0;
    //    counter2 = micros();
    for (int x = 0; x < displayWidth; x++) {
      uint32_t offset = (MYBMP_BF_OFF_BITS + (((y - 1) * lineLength) + (x * 3))) ;
      if (root.position() != offset) {
        root.seek(offset);
      }
      getRGBwithGamma();
      leds[x].setRGB(r, b, g);
      frame++;
    }
    y--;
    LEDDRAW(frameDelay);

  } while (millis() < Time);
  Serial.print(frame);
  Serial.println(F("  pixels"));
  //Serial.println(m_FileDur[m_FileIndex]);
}



inline void LEDDRAW(int dur) {
  FastLED.show();

}


