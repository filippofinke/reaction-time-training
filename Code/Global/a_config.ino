/**
   a_config
   Configuration file for the main program.

   @author Filippo Finke
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SIZE 12
#define JUNIOR_SIZE 8
//array contenente i pin utilizzati dai pulsanti
int buttonPins[SIZE] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44};

//array contenente i pin utilizzati dai led
int ledPins[SIZE] =    {23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45};

//array contenente i pin utilizzati dai pulsanti, junior)
int juniorPins[JUNIOR_SIZE] = {22, 24, 26, 28, 30, 32, 42, 44};

//array contenente lo stato dei pulsanti
bool buttonStatus[SIZE] = {false, false, false, false, false, false, false, false, false, false, false, false};

//pin del buzzer
int buzzerPin = 6;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

boolean programRunning = true;

void setup() {
  Wire.begin();
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.backlight();

  pinMode(buzzerPin, OUTPUT);
  for (int i = 0; i < SIZE; i++)
  {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT);
  }
  Serial.println("BATAK 2.0 AVVIATO!");
}
