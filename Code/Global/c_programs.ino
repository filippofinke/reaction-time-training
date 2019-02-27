/*
   c_programs

   @author Filippo Finke
*/

void temporized() {
  int timeout = 1000;

  long start = millis();
  long startButton = millis();
  long elapsed = 0;
  int pressedButtons = 0;

  int currentPin = getRandom(buttonPins, SIZE);
  digitalWrite(currentPin + 1, HIGH);
  
  while(pressedButtons <= 50)
  {
    elapsed = millis() - startButton; 
    sendData(0, elapsed / 100);
    if(elapsed > timeout)
    {
      Serial.print("Timeout: ");
      Serial.println(currentPin);
      digitalWrite(currentPin + 1, LOW);
      currentPin = getRandom(buttonPins, SIZE);
      startButton = millis();
      Serial.print("Accendo: ");
      Serial.println(currentPin);
      digitalWrite(currentPin + 1, HIGH);
    }
    if (isPressed(currentPin))
    {
      pressedButtons++;
      sendData(1, pressedButtons);
      Serial.print("Premuto: ");
      Serial.println(currentPin);
      digitalWrite(currentPin + 1, LOW);
      currentPin = getRandom(buttonPins, SIZE);
      startButton = millis();
      Serial.print("Accendo: ");
      Serial.println(currentPin);
      digitalWrite(currentPin + 1, HIGH);
    }
    for(int i = 0; i < SIZE; i++)
    {
      int pin = buttonPins[i];
      if(pin == currentPin)
      {
        continue;
      }
      if(isPressed(pin))
      {
        timeout -= 50;
        Serial.print("Hai sbagliato, nuovo timeout: ");
        Serial.println(timeout);
      }
    }
  }
  Serial.print("Fine modalità!");
}

void angularStretching(int maxbuttons) {
  #define ANGULAR_STRETCHING_SIZE 7
  int timeout = 1000;
  
  int angularPins[ANGULAR_STRETCHING_SIZE] = {22,42,24,30,32,38,40};
  Serial.print("MAXBUTTONS: ");
  Serial.println(maxbuttons);
  long start = millis();
  long startButton = millis();
  long elapsed = 0;
  int leftButtons = maxbuttons;

  int currentPin = getRandom(angularPins, ANGULAR_STRETCHING_SIZE);
  digitalWrite(currentPin + 1, HIGH);
  
  while(leftButtons > 0)
  {
    elapsed = (millis() - start); 
    sendData(0, elapsed / 100);
    if(millis() - startButton > timeout)
    {
      Serial.print("Timeout: ");
      Serial.println(currentPin);
      digitalWrite(currentPin + 1, LOW);
      currentPin = getRandom(angularPins, ANGULAR_STRETCHING_SIZE);
      startButton = millis();
      Serial.print("Accendo: ");
      Serial.println(currentPin);
      digitalWrite(currentPin + 1, HIGH);
    }
    if (isPressed(currentPin))
    {
      leftButtons--;
      sendData(1, leftButtons);
      Serial.print("Premuto: ");
      Serial.println(currentPin);
      digitalWrite(currentPin + 1, LOW);
      currentPin = getRandom(angularPins, ANGULAR_STRETCHING_SIZE);
      startButton = millis();
      Serial.print("Accendo: ");
      Serial.println(currentPin);
      digitalWrite(currentPin + 1, HIGH);
    }
    for(int i = 0; i < SIZE; i++)
    {
      int pin = buttonPins[i];
      if(pin == currentPin)
      {
        continue;
      }
      if(isPressed(pin))
      {
        timeout -= 50;
        Serial.print("Hai sbagliato, nuovo timeout: ");
        Serial.println(timeout);
      }
    }
  }
  Serial.print("Fine modalità!");
}

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
