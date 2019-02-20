/*
   global
   This is the main program.

   @author Filippo Finke
*/

void waitUser() {
  bool state = false;
  int counter = 0;
  while (!state)
  {
    if (counter >= 1000)
    {
      counter = 0;
      int ledPin = getRandom(ledPins, SIZE);
      bool ledState = digitalRead(ledPin);
      digitalWrite(ledPin, !ledState);
    }
    counter++;
    digitalWrite(45, HIGH);
    state = isPressed(44);
  }
  resetLeds();
  bool ls = LOW;
  for (int i = 0; i < 3; i++)
  {
    ls = !ls;
    digitalWrite(45, ls);
    delay(500);
  }
  resetLeds();
}

void cumulative(long duration, bool senior) {
  long start = millis();
  long reactionTime = 0;
  long time = 0;
  int currentPin;
  if (senior)
  {
    currentPin = getRandom(buttonPins, SIZE);
  }
  else
  {
    currentPin = getRandom(juniorPins, JUNIOR_SIZE);
  }
  int pressedButtons = 0;
  digitalWrite(currentPin + 1, HIGH);

  while (time <= duration)
  {
    time = (millis() - start);
    if (time % 1000 == 0)
    {
      Serial.print("Tempo rimanente: ");
      Serial.println((duration - time) / 1000);
    }
    if (isPressed(currentPin))
    {
      pressedButtons++;
      Serial.print("Premuto: ");
      Serial.println(currentPin);
      digitalWrite(currentPin + 1, LOW);
      if (senior)
      {
        currentPin = getRandom(buttonPins, SIZE);
      }
      else
      {
        currentPin = getRandom(juniorPins, JUNIOR_SIZE);
      }
      reactionTime = millis();
      Serial.print("Accendo: ");
      Serial.println(currentPin);
      digitalWrite(currentPin + 1, HIGH);
    }
  }
  Serial.print("Fine modalità! Punteggio: ");
  Serial.println(pressedButtons);
}

void setup() {
  Serial.begin(9600);
  pinSetup();
  Serial.println("BATAK 2.0 AVVIATO!");
}

void loop() {
  waitUser();
  Serial.println("AVVIO PROGRAMMA");
  cumulative(10000, false);
  Serial.println("HO FINITO");
}
