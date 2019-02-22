/*
   cumulative

   @author Filippo Finke
*/
void cumulative(long duration, boolean senior) {
  Serial.print("DURATA ");
  Serial.println(duration);
  Serial.println(senior);
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
    sendData(0, time / 100);
    if (time % 1000 == 0)
    {
      Serial.print("Tempo rimanente: ");
      Serial.println((duration - time) / 1000);
    }
    if (isPressed(currentPin))
    {
      pressedButtons++;
      sendData(1, pressedButtons);
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
