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
  bool waiting = true;
  String selected = "";
  int index = 0;
  while(waiting && index <= 1) {
    for(int i = 0; i < SIZE; i++)
    {
      int bpin = buttonPins[i];
      if(isPressed(bpin) && bpin != 44)
      {
        digitalWrite(bpin + 1, HIGH);
        if(bpin == 42)
        {
          waiting = false;
        }
        else
        {
          selected = selected + getLabel(bpin);
          Serial.println(selected);
          index++;
        }
      }
    }
    delay(100);
  }
  resetLeds();
  Serial.println(selected);
  bool ls = LOW;
  for (int i = 0; i < 3; i++)
  {
    ls = !ls;
    digitalWrite(45, ls);
    delay(500);
  }
  resetLeds();
  return atol(selected.c_str());
}

void loop() {
  int selected = waitUser();
  Serial.print("AVVIO ");
  Serial.println(selected);
  if(selected == 1)
  {
    cumulative(60000, true);
  }
  else if(selected == 2)
  {
    cumulative(300000, true);
  }
  else if(selected == 3)
  {
    rush(100000,2);
  } 
  else if(selected == 4)
  {
    angularStretching(100);
  }
  /*else if(selected == 5)
  {}
  else if(selected == 6)
  {}*/
  else if(selected == 7)
  {
    temporized();
  }
  else if(selected == 8)
  {
    for(int i = 0; i < 4; i++)
    {
      Serial.print("GIOCATORE: ");
      Serial.println(i + 1);
      cumulative(30000, true);
    }
  }
  
  Serial.println("HO FINITO");
}
