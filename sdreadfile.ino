
void SendFile(String Filename) {
  Serial.print(F("trying to read : N."));
  Serial.print(x);
  Serial.print(F("\t"));
  Serial.println(Filename);
  String temp2 = Filename + F(".BMP");
  char temp[14];
  temp2.toCharArray(temp, 14);
  root = SD.open(temp);
  // if the file is available
  if (root) {
    ShowTheFile();
    root.close();
  }
  else {
    LightOn(5);
    Serial.println(F("fail@read"));

    return;
  }
}

inline int readByte() {
  int retbyte = -1;
  while (retbyte < 0) retbyte = root.read();
  return retbyte;
}

inline void getRGBwithGamma() {
  g = readByte();
  b = readByte();
  r = readByte();
}


uint32_t readLong() {
  uint32_t retValue;
  byte incomingbyte;

  incomingbyte = readByte();
  retValue = (uint32_t)((byte)incomingbyte);

  incomingbyte = readByte();
  retValue += (uint32_t)((byte)incomingbyte) << 8;

  incomingbyte = readByte();
  retValue += (uint32_t)((byte)incomingbyte) << 16;

  incomingbyte = readByte();
  retValue += (uint32_t)((byte)incomingbyte) << 24;

  return retValue;
}

uint16_t readInt() {
  byte incomingbyte;
  uint16_t retValue;

  incomingbyte = readByte();
  retValue += (uint16_t)((byte)incomingbyte);

  incomingbyte = readByte();
  retValue += (uint16_t)((byte)incomingbyte) << 8;

  return retValue;
}


