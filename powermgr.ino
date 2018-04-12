//----for charger
#define Vbatpin  A5 // Battery Voltage, shorted to Operating Voltage when device is on
#define Voppin   A6 // Always on, Operating voltage.
#define V_ERROR    10  // error existed in Voltage detection

void ifCharge() {
  //#define Vbatpin  A0 //  Always on,
  // A5,A6 for realone
  //#define Voppin   A2
  analogRead(Voppin);
  analogRead(Vbatpin);
  delay(5);
  analogRead(Voppin);
  analogRead(Vbatpin);
  delay(5);
  Serial.print(F("V oppin:\t"));
  Serial.println(analogRead(Voppin));
  Serial.print(F("V batpin:\t"));
  Serial.println(analogRead(Vbatpin));
  delay(5);
  int Vop = analogRead(Voppin);
  int Vbat = analogRead(Vbatpin);
  Serial.print(F("V difference::\t"));
  Serial.println(Vop - Vbat);
  if ((Vop - Vbat) > V_ERROR) {
    delay(10);
    Vop = analogRead(Voppin);
    Vbat = analogRead(Vbatpin);
    Serial.print(F("V oppin2:\t"));
    Serial.println(Vop);
    Serial.print(F("V batpin2:\t"));
    Serial.println(Vbat);
    Serial.println(F("Possible_charging_1"));
    if ((Vop - Vbat) > V_ERROR + 3) {
      delay(10);
      Vop = analogRead(Voppin);
      Vbat = analogRead(Vbatpin);
      Serial.print(F("V oppin3:\t"));
      Serial.println(Vop);
      Serial.print(F("V batpin3:\t"));
      Serial.println(Vbat);

      Serial.println(F("Possible_charging_2"));
      if ((Vop - Vbat) > V_ERROR + 5) {

        Serial.println(F("Charging_confirmed"));
        FastLED.setBrightness(200);
        while (true) {
          //ShowVolt();
          //Rest();
        }
      } else
      { Serial.println(F("Chargingdenied_2"));
      }
    } else
    { Serial.println(F("Chargingdenied_1"));
    }
  }
  Serial.println(F("Not_Charging"));

  //ShowVolt();
}

