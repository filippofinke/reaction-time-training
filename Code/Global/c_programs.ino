/*
   c_cumulative

   @author Filippo Finke
*/
void rush(long duration, int maxbuttons) {
  Serial.print("DURATA ");
  Serial.println(duration);
  Serial.print("MAXBUTTONS: ");
  Serial.println(maxbuttons);
  long start = millis();
  long elapsed = 0;
  int pressedButtons = 0;

  int currentPin = getRandom(buttonPins, SIZE);
  digitalWrite(currentPin + 1, HIGH);

  
  while(elapsed <= duration && pressedButtons < maxbuttons)
  {
    elapsed = (millis() - start); 
    sendData(0, elapsed / 100);
    if (isPressed(currentPin))
    {
      pressedButtons++;
      sendData(1, pressedButtons);
      Serial.print("Premuto: ");
      Serial.println(currentPin);
      digitalWrite(currentPin + 1, LOW);
      currentPin = getRandom(buttonPins, SIZE);
      Serial.print("Accendo: ");
      Serial.println(currentPin);
      digitalWrite(currentPin + 1, HIGH);
    }
  }
  Serial.print("Fine modalità! Punteggio: ");
  Serial.println(pressedButtons);
}

void cumulative(long duration, boolean senior) {
  Serial.print("DURATA ");
  Serial.println(duration);
  Serial.println(senior);
  long start = millis();
  long elapsed = 0;
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

  while (elapsed <= duration)
  {
    elapsed = (millis() - start);
    sendData(0, elapsed / 100);
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
      Serial.print("Accendo: ");
      Serial.println(currentPin);
      digitalWrite(currentPin + 1, HIGH);
    }
  }
  Serial.print("Fine modalità! Punteggio: ");
  Serial.println(pressedButtons);
}
