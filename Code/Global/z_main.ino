/**
   z_ main
   This is the main program.

   @author Filippo Finke
*/

/**
   Metodo che attende che l'utente inserisca nel sistema un numero di programma
   valido.
*/
int waitUser() {
  setLcdText("Per iniziare premi", "il pulsante @", "", "BATTAK 2.0");

  bool state = false;
  int counter = 0;

  //animazione
  while (!state)
  {
    if (counter >= 1000)
    {
      counter = 0;
      int ledPin = getRandom(ledPins, SIZE);
      //leggo lo stato del led
      bool ledState = digitalRead(ledPin);
      digitalWrite(ledPin, !ledState);
    }
    counter++;
    digitalWrite(45, HIGH);
    state = isPressed(44);
  }

  resetLeds();
  //menù delle modalità
  bool waiting = true;
  String selected = "";
  int index = 0;
  setLcdText("Scegli un programma", "cliccando uno o piu", "pulsanti, da 0 a 23", "BATTAK 2.0");

  //legge e controlla se il programma esiste
  while (waiting && index <= 1 && programRunning) {
    for (int i = 0; i < SIZE && programRunning; i++)
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
          setLcdText("Numero selezionato:", selected , "Per confermare premi", "il pulsante #");
        }
      }
    }
    delay(50);
  }
  resetLeds();
  bool ls = LOW;
  int sel = atol(selected.c_str());

  if (((sel >= 0 && sel <= 23) || sel == 99) && selected != "") {
    setLcdText("Avvio il programma", "tieniti pronto!", "Aspetta 3 secondi", "BATTAK 2.0");
    delay(2000);
    setLcdText("Manca 1 secondo!", "preparati!!", "", "BATTAK 2.0");
    delay(1000);
  }
  resetLeds();
  return sel;
}

/**
   Metodo principale in cui viene svolto l'intero programma.
*/
void loop() {
  programRunning = true;
  //aspetto che l'utente scelga il programma
  int selected = waitUser();
  setLcdText("Programma attuale:" + String(selected), "", "", "BATTAK 2.0");
  //resetto lo stato dei bottoni
  resetButtonsState();
  //resetto il dispaly 7 segmenti
  resets7Segments();
  if (selected == 1)
  {
    //eseguo il programma cumulativo 60 secondi, senior
    cumulative(60000, true);
  }
  else if (selected == 2)
  {
    //eseguo il programma maratona 5 minuti senior
    cumulative(300000, true);
  }
  else if (selected == 3)
  {
    //eseguo il programma corsa 50 pulsanti senior
    rush(100000, 50, true);
  }
  else if (selected == 4)
  {
    //eseguo il programma stretching angolare 100 pulsanti senior
    angularStretching(100, 4);
  }
  /*else if(selected == 5)
    {}*/
  else if (selected == 6)
  {
    //eseguo il programma beep test senior
    beepTest();
  }
  else if (selected == 7)
  {
    //eseguo il programma 50 pulsanti temporizzati senior
    temporized(50, true);
  }
  else if (selected == 8)
  {
    //eseguo il programma staffetta 4 giocatori senior
    for (int i = 0; i < 4 && programRunning; i++)
    {
      cumulative(30000, true);
      long start = millis();
      while (millis() - start <= 5000 && programRunning)
      {
        long elapsed = millis() - start;
        sendData(0, elapsed / 100);
      }
    }
  }
  else if (selected == 9)
  {
    //eseguo il programma della somma matematica
    mathsum();
  }
  else if (selected == 10)
  {
    //eseguo il programma delle tabelline
    boards();
  }
  else if (selected == 11)
  {
    //eseguo il programma dello strtching angolare 25 punsanti
    angularStretching(25, 11);
  }
  else if (selected == 12)
  {
    //eseguo il programma dello strtching angolare 50 pulsanti
    angularStretching(50, 12);
  }
  else if (selected == 13)
  {
    //eseguo il programma 25 pulsanti temporizzati junior
    temporized(25, false);
  }
  else if (selected == 14)
  {
    //eseguo il programma 50 pulsanti temporizzati junior
    temporized(50, false);
  }
  else if (selected == 15)
  {
    //eseguo il programma cumulativo 30 secondi junior
    cumulative(30000, false);
  }
  else if (selected == 16)
  {
    //eseguo il programma cumulativo 60 secondi junior
    cumulative(60000, false);
  }
  else if (selected == 17)
  {
    //eseguo il programma corsa 25 pulsanti junior
    rush(50000, 25, false);
  }
  else if (selected == 18)
  {
    //eseguo il programma corsa 50 pulsanti junior
    rush(100000, 50, false);
  }
  else if (selected == 19)
  {
    //eseguo il programma maratona 3 minuti junior
    cumulative(180000, false);
  }
  else if (selected == 20)
  {
    //eseguo il programma simon
    simon();
  }
  else if (selected == 21)
  {
    //eseguo il programma flash test, 5 schemi
    flashtest(false);
  }
  else if (selected == 22)
  {
    //eseguo il programma anti flash test
    flashtest(true);
  }
  else if (selected == 23)
  {
    //eseguo il programma reazione veloce, 10 schemi
    fastreaction();
  }
  else if (selected == 99)
  {
    //eseguo la procedura di check
    systemCheck();
  }
}
