/*
   z_ main
   This is the main program.

   @author Filippo Finke
*/

int waitUser() {
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
  setLcdText("Premi il numero", "del programma");
  bool waiting = true;
  String selected = "";
  int index = 0;
  while (waiting && index <= 1) {
    for (int i = 0; i < SIZE; i++)
    {
      int bpin = buttonPins[i];
      bool lastState = getLastState(bpin);
      bool currentState = isPressed(bpin);
      if (currentState == HIGH && currentState != lastState && bpin != 44)
      {
        digitalWrite(bpin + 1, HIGH);
        if (bpin == 42)
        {
          waiting = false;
        }
        else
        {
          selected = selected + getLabel(bpin);
          Serial.println(selected);
          index++;
          setLcdText("Selezionato: " + selected, "Per uscire #");
        }
      }
    }
    delay(50);
  }
  resetLeds();
  bool ls = LOW;
  for (int i = 0; i < 3; i++)
  {
    ls = !ls;
    digitalWrite(45, ls);
    delay(500);
    setLcdText("Avvio in", String(((3 * 500) - (i * 500)) / 1000) + " secondi");
  }
  resetLeds();
  return atol(selected.c_str());
}

void loop() {
  setLcdText("In attesa...", "Premi @");
  int selected = waitUser();
  setLcdText("Programma", "N: " + String(selected));
  resetButtonsState();
  resets7Segments();
  if (selected == 1)
  {
    cumulative(60000, true);
  }
  else if (selected == 2)
  {
    cumulative(300000, true);
  }
  else if (selected == 3)
  {
    rush(100000, 50, true);
  }
  else if (selected == 4)
  {
    angularStretching(100, 4);
  }
  /*else if(selected == 5)
    {}*/
  else if (selected == 6)
  {
    beepTest();
  }
  else if (selected == 7)
  {
    temporized(50, true);
  }
  else if (selected == 8)
  {
    for (int i = 0; i < 4; i++)
    {
      Serial.print("GIOCATORE: ");
      Serial.println(i + 1);
      cumulative(30000, true);
      long start = millis();
      while (millis() - start <= 5000)
      {
        long elapsed = millis() - start;
        sendData(0, elapsed / 100);
      }
    }
  }
  else if (selected == 9)
  {
    mathsum();
  }
  /*else if(selected == 10)
    {}*/
  else if (selected == 11)
  {
    angularStretching(25, 11);
  }
  else if (selected == 12)
  {
    angularStretching(50, 12);
  }
  else if (selected == 13)
  {
    temporized(25, false);
  }
  else if (selected == 14)
  {
    temporized(50, false);
  }
  else if (selected == 15)
  {
    cumulative(30000, false);
  }
  else if (selected == 16)
  {
    cumulative(60000, false);
  }
  else if (selected == 17)
  {
    rush(100000, 25, false);
  }
  else if (selected == 18)
  {
    rush(100000, 50, false);
  }
  else if (selected == 19)
  {
    cumulative(180000, false);
  }

  Serial.println("HO FINITO");
}
