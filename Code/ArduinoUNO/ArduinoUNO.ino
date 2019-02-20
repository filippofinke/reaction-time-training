#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  Serial.println("ArduinoUNO Avviato!");
  matrix.begin(0x70);
}
int num = 0;
void loop() {

  Serial.println(num);
  matrix.writeDigitNum(0, (num / 1000), false);
  matrix.writeDigitNum(1, (num / 100) % 10, false);
  matrix.writeDigitNum(3, (num / 10) % 10, true);
  matrix.writeDigitNum(4, num % 10, false);
  matrix.writeDisplay();
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
    num = value;
  }
}
