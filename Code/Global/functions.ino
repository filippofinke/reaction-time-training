/*
   functions
   This file contains all the functions needed to the program to work correctly.

   @author Filippo Finke
*/

int getRandom(int pins[], int size) {
  return pins[random(0, size + 1)];
}

void resetLeds() {
  for (int i = 0; i < SIZE; i++)
  {
    digitalWrite(ledPins[i], LOW);
  }
}

bool isPressed(int pin)
{
  return !digitalRead(pin);
}

void pinSetup() {
  for (int i = 0; i < SIZE; i++)
  {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT);
  }
}
