#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "SevSeg.h"

SevSeg sevenSeg;

Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  Serial.println("ArduinoUNO Avviato!");
  matrix.begin(0x70);
  int displayType = COMMON_CATHODE;

  int digit1 = 10; //Pin 12 on my 4 digit display
  int digit2 = 11; //Pin 9 on my 4 digit display
  int digit3 = 12; //Pin 8 on my 4 digit display
  int digit4 = 13; //Pin 6 on my 4 digit display

  int segA = 6; //Pin 11 on my 4 digit display
  int segB = 8; //Pin 7 on my 4 digit display
  int segC = 2; //Pin 4 on my 4 digit display
  int segD = 5; //Pin 2 on my 4 digit display
  int segE = 4; //Pin 1 on my 4 digit display
  int segF = 7; //Pin 10 on my 4 digit display
  int segG = 3; //Pin 5 on my 4 digit display
  int segDP= 5; //Pin 3 on my 4 digit display

  int numberOfDigits = 4;

  sevenSeg.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, segDP);
  
  sevenSeg.SetBrightness(100);
  
}
long tempo = 0;
long points = 0;
boolean updateNeeded = true;

void loop() {
  if(updateNeeded) {
    matrix.writeDigitNum(0, (tempo / 1000), false);
    matrix.writeDigitNum(1, (tempo / 100) % 10, false);
    matrix.writeDigitNum(3, (tempo / 10) % 10, true);
    matrix.writeDigitNum(4, tempo % 10, false);
    matrix.writeDisplay();
    updateNeeded = false;
    Serial.print("TEMPO :");
    Serial.println(tempo);
    Serial.print("PUNTI: ");
    Serial.println(points);
  }
  char tempString[10]; 
  sprintf(tempString, "%04d", points);
  sevenSeg.DisplayString(tempString, 3);
  delay(10);
}

void receiveEvent(int bytes) {
  int value;
  byte s, a, b, c, d;
  s = Wire.read();
  a = Wire.read();
  b = Wire.read();
  c = Wire.read();
  d = Wire.read();

  value = a;
  value = (value << 8) | b;
  value = (value << 8) | c;
  value = (value << 8) | d;
  if (s == 0)
  {
    tempo = value;
  }
  else if(s==1)
  {
    points = value;
  }
  updateNeeded = true;
}
