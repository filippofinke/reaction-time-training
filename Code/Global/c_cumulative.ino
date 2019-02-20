/*
   cumulative

   @author Filippo Finke
*/
void cumulative(int32_t duration, bool senior) {
  int32_t start = millis();
  int32_t reactionTime = 0;
  int32_t time = 0;
  int32_t currentPin;
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
    Wire.beginTransmission(8);
    int32_t dec = time / 100;
    byte times[5];
    times[0] = 0;
    times[1] = (dec >> 24) & 0xFF;
    times[2] = (dec >> 16) & 0xFF;
    times[3] = (dec >> 8) & 0xFF;
    times[4] = dec & 0xFF;
    Wire.write(times,5);
    Wire.endTransmission();
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
