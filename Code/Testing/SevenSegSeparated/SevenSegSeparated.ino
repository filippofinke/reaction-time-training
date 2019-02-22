
#include "SevSeg.h"

SevSeg sevenSeg;

int deciSecond = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("SevenSeg Test");
  int displayType = COMMON_CATHODE;

  int digit1 = 10; //Pin 12 on my 4 digit display
  int digit2 = 11; //Pin 9 on my 4 digit display
  int digit3 = 12; //Pin 8 on my 4 digit display
  int digit4 = 13; //Pin 6 on my 4 digit display

  int segA = 6; //Pin 11 on my 4 digit display
  int segB = 8; //Pin 7 on my 4 digit display
  int segC = 2; //Pin 4 on my 4 digit display
  int segD = 5; //Pin 2 on my 4 digit display
  int segE = 7; //Pin 1 on my 4 digit display
  int segF = 4; //Pin 10 on my 4 digit display
  int segG = 3; //Pin 5 on my 4 digit display
  int segDP= 5; //Pin 3 on my 4 digit display

  int numberOfDigits = 4;

  sevenSeg.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, segDP);
  
  sevenSeg.SetBrightness(100);
}

void loop()
{
  char tempString[10]; 
  sprintf(tempString, "%04d", deciSecond);
  sevenSeg.DisplayString(tempString, 3);
}
