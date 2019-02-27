/*
   a_config
   Configuration file for the main program.

   @author Filippo Finke
*/
#include <Wire.h>
#define SIZE 12
#define JUNIOR_SIZE 8
int buttonPins[SIZE] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44};
int ledPins[SIZE] =    {23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45};
int juniorPins[JUNIOR_SIZE] = {22, 24, 26, 28, 30, 32, 42, 44};

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinSetup();
  Serial.println("BATAK 2.0 AVVIATO!");
}
