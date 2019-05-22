/*
   c_programs
   File che contiene tutte le modalità di gioco.

   @author Filippo Finke
*/

/*
  Programma che serve a verificare che il sistema
  hardware funzioni.
*/
void systemCheck() {
  //Stampa sul display LCD.
  setLcdText("Procedura di test", "Attendi...", "", "BATAK 2.0");
  delay(1000);
  setLcdText("Test buzzer", "1 secondo", "", "BATAK 2.0");
  //Il buzzer emette un suono a frequenza 2000.
  tone(buzzerPin, 2000);
  //Aspetta 1 secondo.
  delay(1000);
  //Fa tacere il buzzer.
  noTone(buzzerPin);
  //Ciclo che scorre tutti i pulsanti del sistema.
  for (int i = 0; i < SIZE && programRunning; i++)
  {
    int pin = buttonPins[i];
    String text = String(getLabel(pin));
    if (text == "10")
    {
      text = "#";
    }
    else if (text == "11")
    {
      text = "@";
    }
    setLcdText("Premi il pulsante", text, "", "BATAK 2.0");
    while (!isPressed(pin) && programRunning) {
      isPressed(44);
    }
    digitalWrite(pin + 1, HIGH);
    setLcdText("Il pulsante dovrebbe", "essere accesso", "", "BATAK 2.0");
    delay(1000);
  }
  setLcdText("Procedura conclusa", "", "", "BATAK 2.0");
  delay(2500);
}

/**
   Programma numero 10: Tabelline, test di velocità

   Vengono proposte 12 tabelline di un numero scelto dall'utente, tempo senza limiti,
   se la risposta è di 2 cifre, si devono premere prima le decine e poi le unità.
*/
void boards() {
  resetLeds();
  resetButtonsState();
  setLcdText("Seleziona una", "tabellina da 2 a 9", "", "BATAK 2.0");
  bool waiting = true;
  int boards = 0;
  while (waiting && programRunning)
  {
    for (int i = 1; i <= SIZE; i++)
    {
      int bpin = buttonPins[i];
      bool lastState = getLastState(bpin);
      bool currentState = isPressed(bpin);
      if (currentState == HIGH && currentState != lastState)
      {
        digitalWrite(bpin + 1, HIGH);
        int label = getLabel(bpin);
        if (label >= 2 && label <= 9)
        {
          boards = label;
          waiting = false;
        }
      }
    }
  }
  setLcdText("Hai selezionato la", "tabellina del " + String(boards), "", "BATAK 2.0");
  long startTime = millis();
  for (int i = 0; i < 12 && programRunning; i++)
  {
    resetLeds();
    int one = boards;
    int two = random(0, 9);
    int sum = one * two;

    setLcdText("Tabellina del " + String(boards), String(one) + " * " + String(two) + " = ?", "", "BATAK 2.0");

    startTime = millis();
    waiting = true;
    while (waiting && programRunning)
    {
      sendData(1, (millis() - startTime) / 100);

      for (int x = 0; x < SIZE; x++)
      {
        int bpin = buttonPins[x];
        bool lastState = getLastState(bpin);
        bool currentState = isPressed(bpin);
        if (currentState == HIGH && currentState != lastState)
        {
          if (getLabel(bpin) == sum)
          {
            digitalWrite(bpin + 1, HIGH);
            waiting = false;
            break;
          }
          else
          {
            if (getLabel(bpin) == sum / 10)
            {
              digitalWrite(bpin + 1, HIGH);
              sum = sum - getLabel(bpin) * 10;
            }
          }
        }
      }
    }
  }

}

/**
   Programma numero: 23, Reazione veloce 10 schemi.

   Il programma propone 10 schemi riempiti da un numero di pulsanti definito dall'utente.
   I pulsanti accessi casualmente restano accesi fino a quando l'utente li preme.
   Il giocatore determina la velocità del gioco.
*/
void fastreaction() {
  int schemes = 10;
  resetLeds();
  setLcdText("Seleziona un numero", "di pulsanti per", "schema (Da 1 a 11)", "BATAK 2.0");
  bool waiting = true;
  int buttons = 0;
  while (waiting && programRunning)
  {
    for (int i = 1; i <= SIZE; i++)
    {
      int bpin = buttonPins[i];
      bool lastState = getLastState(bpin);
      bool currentState = isPressed(bpin);
      if (currentState == HIGH && currentState != lastState)
      {
        digitalWrite(bpin + 1, HIGH);
        int label = getLabel(bpin);
        if (label >= 1 && label <= 11)
        {
          buttons = label;
          waiting = false;
        }
      }
    }
  }
  int buttonseq[buttons];
  long startTime = millis();
  int points = 0;
  for (int i = 0; i < schemes && programRunning; i++)
  {
    resetLeds();
    setLcdText("Schema: " + String(i + 1) + "/" + String(schemes), "Pulsanti: " + String(buttons), "", "BATAK 2.0");
    for (int a = 0; a < buttons; a++)
    {
      bool random = true;
      int rndpin = 0;
      while (random)
      {
        rndpin = getRandom(buttonPins, SIZE);
        bool contain = false;
        for (int j = 0; j < 6; j++)
        {
          if (buttonseq[j] == rndpin) {
            contain = true;
          }
        }
        if (!contain)
        {
          break;
        }
      }
      buttonseq[a] = rndpin;
      digitalWrite(rndpin + 1, HIGH);
    }
    resetButtonsState();
    int pressed = 0;
    bool insideLevel = true;
    resetButtonsState();
    while (insideLevel && programRunning)
    {
      sendData(0, (millis() - startTime) / 100);
      for (int b = 0; b < SIZE && insideLevel && programRunning; b++)
      {
        int pin = buttonPins[b];
        bool presslastState = getLastState(pin);
        bool presscurrentState = isPressed(pin);
        if (presslastState == HIGH && presslastState != presscurrentState)
        {
          for (int x = 0; x < buttons; x++) {
            if (buttonseq[x] == pin) {
              digitalWrite(pin + 1, LOW);
              pressed += 1;
              points += 1;
              sendData(1, points);
              if (pressed == buttons)
              {
                insideLevel = false;
              }
              buttonseq[x] = -1;
            }
          }
        }
      }
    }
  }
}

/**
   Programma numero: 21 e 22, Flash test, 5 schemi e Anti flash test.

   Il sistema accende 6 pulsanti per 5 schemi.
   L'utente sceglie la durata da 1 - 8 secondi.
   Quando il tempo termina vengono emessi due beep.
   Ogni schema incrementa il punteggio.

   @param onButtons True programma 22, False 21
*/
void flashtest(bool onButtons) {
  resetLeds();
  setLcdText("Scegli un tempo per", "spegnere tutti i", "pulsanti (1-8)", "BATAK 2.0");
  bool waiting = true;
  int selectedtime = 0;
  while (waiting && programRunning)
  {
    for (int i = 1; i <= SIZE; i++)
    {
      int bpin = buttonPins[i];
      bool lastState = getLastState(bpin);
      bool currentState = isPressed(bpin);
      if (currentState == HIGH && currentState != lastState)
      {
        digitalWrite(bpin + 1, HIGH);
        int label = getLabel(bpin);
        if (label >= 1 && label <= 8)
        {
          selectedtime = label * 1000;
          waiting = false;
        }
      }
    }
  }
  setLcdText("Hai scelto: " + String(selectedtime / 1000) + " s", "", "", "BATAK 2.0");
  resetLeds();
  int points = 0;
  bool playing = true;
  delay(200);
  for (int i = 0; i < 5 && playing && programRunning; i++)
  {
    resetLeds();
    sendData(1, i + 1);
    setLcdText("Schema: " + String(i + 1) + "/5", "", "", "BATAK 2.0");
    int sequence[6];
    if (onButtons)
    {
      for (int i = 0; i < SIZE; i++)
      {
        digitalWrite(buttonPins[i] + 1, HIGH);
      }
    }
    for (int i = 0; i < 6; i++)
    {
      bool random = true;
      int rndpin = 0;
      while (random)
      {
        rndpin = getRandom(buttonPins, SIZE);
        bool contain = false;
        for (int j = 0; j < 6; j++)
        {
          if (sequence[j] == rndpin) {
            contain = true;
          }
        }
        if (!contain)
        {
          break;
        }
      }
      sequence[i] = rndpin;
      if (onButtons)
      {
        digitalWrite(rndpin + 1, LOW);
      }
      else
      {
        digitalWrite(rndpin + 1, HIGH);
      }
    }
    tone(buzzerPin, 2000);
    delay(250);
    noTone(buzzerPin);
    delay(100);
    tone(buzzerPin, 2000);
    delay(250);
    noTone(buzzerPin);
    long startTime = millis();
    int pressed = 0;
    bool insideLevel = true;
    resetButtonsState();
    while (insideLevel && programRunning)
    {
      if (millis() - startTime >= selectedtime)
      {
        playing = false;
        break;
      }
      for (int b = 0; b < SIZE && insideLevel && playing && programRunning; b++)
      {
        int pin = buttonPins[b];
        bool presslastState = getLastState(pin);
        bool presscurrentState = isPressed(pin);
        if (presslastState == HIGH && presslastState != presscurrentState)
        {
          bool edited = false;
          for (int x = 0; x < 6; x++) {
            if (sequence[x] == pin) {
              edited = true;
              if (onButtons)
              {
                digitalWrite(pin + 1, HIGH);
              }
              else
              {
                digitalWrite(pin + 1, LOW);
              }
              pressed += 1;
              points += 1;
              sendData(0, points);
              if (pressed == 6)
              {
                insideLevel = false;
              }
              sequence[x] = -1;
            }
          }
          if (!edited)
          {
            playing = false;
            insideLevel = false;
            setLcdText("Hai sbagliato a", "premere un pulsante!", "", "BATAK 2.0");
            delay(1000);
          }
          delay(150);
        }
      }
    }
  }
}


/**
   Programma numero: 20, Semplice gioco: Simon

   Il sistema propone una sequenza di pulsanti che l'utente deve
   ricreare correttamente.
*/
void simon() {
  int buttons = 20;
  int sequence[buttons];
  for (int i = 0; i < buttons; i++)
  {
    int rndpin = getRandom(buttonPins, SIZE);
    sequence[i] = rndpin;
  }

  int toShow = 4;
  int pressed = 0;
  boolean playing = HIGH;
  bool insideLevel = HIGH;
  int points = 0;
  for (int i = 0; i < 17 && playing && programRunning; i++)
  {
    sendData(1, (i + 1));
    setLcdText("Livello:" + String(i + 1), "Osserva la sequenza", "", "BATAK 2.0");
    for (int x = 0; x < toShow; x++)
    {
      for (int y = 0; y < 3; y++)
      {
        digitalWrite(sequence[x] + 1, HIGH);
        delay(100);
        digitalWrite(sequence[x] + 1, LOW);
        delay(100);
      }
      delay(500);
    }
    tone(buzzerPin, 2000);
    delay(250);
    noTone(buzzerPin);
    delay(100);
    tone(buzzerPin, 2000);
    delay(250);
    noTone(buzzerPin);
    setLcdText("Ripeti la sequenza", "", "", "BATAK 2.0");
    resetButtonsState();
    pressed = 0;
    toShow += 1;
    insideLevel = true;
    while (insideLevel && playing && programRunning)
    {
      for (int b = 0; b < SIZE && playing && insideLevel && programRunning; b++)
      {
        int pin = buttonPins[b];
        bool presslastState = getLastState(pin);
        bool presscurrentState = isPressed(pin);
        if (presscurrentState == HIGH && presslastState == LOW)
        {
          if (pin == sequence[pressed])
          {
            digitalWrite(pin + 1, HIGH);
            pressed += 1;
            points += 1;
            sendData(0, points);
            if (pressed == toShow - 1)
            {
              insideLevel = false;
            }
            break;
          }
          else
          {
            playing = false;
            setLcdText("Hai sbagliato a", "ripetere la sequenza", "", "BATAK 2.0");
            delay(1000);
          }
        }
      }
    }
    resetLeds();
  }
}

/**
   Programma numero: 13 e 14, Pulsanti temporizzati.

   Pulsanti casuali con il tempo per premerli di 1 secondo.

   @param maxbuttons numero di bottoni da premere.
   @param senior se usare array senior o junior.
*/
void temporized(int maxbuttons, boolean senior) {
  int timeout = 1000;

  long start = millis();
  long startButton = millis();
  long elapsed = 0;
  int pressedButtons = 0;
  int currentPin;
  if (senior)
  {
    currentPin = getRandom(buttonPins, SIZE);
  }
  else
  {
    currentPin = getRandom(juniorPins, JUNIOR_SIZE);
  }
  digitalWrite(currentPin + 1, HIGH);

  while (pressedButtons < maxbuttons && programRunning)
  {
    elapsed = millis() - startButton;
    sendData(0, (timeout - elapsed) / 100);
    if (elapsed > timeout)
    {
      digitalWrite(currentPin + 1, LOW);
      if (senior)
      {
        currentPin = getRandom(buttonPins, SIZE);
      }
      else
      {
        currentPin = getRandom(juniorPins, JUNIOR_SIZE);
      }
      startButton = millis();
      digitalWrite(currentPin + 1, HIGH);
    }
    bool presslastState = getLastState(currentPin);
    bool presscurrentState = isPressed(currentPin);
    if (presslastState == HIGH && presslastState != presscurrentState)
    {
      pressedButtons++;
      sendData(1, pressedButtons);
      digitalWrite(currentPin + 1, LOW);
      if (senior)
      {
        currentPin = getRandom(buttonPins, SIZE);
      }
      else
      {
        currentPin = getRandom(juniorPins, JUNIOR_SIZE);
      }
      startButton = millis();
      digitalWrite(currentPin + 1, HIGH);
    }
    for (int i = 0; i < SIZE; i++)
    {
      int pin = buttonPins[i];
      if (pin == currentPin)
      {
        continue;
      }
      bool lastState = getLastState(pin);
      bool currentState = isPressed(pin);
      if (currentState == HIGH && currentState != lastState)
      {
        timeout -= 100;
        if (timeout < 200)
        {
          timeout = 200;
        }
        setLcdText("Hai sbagliato,", "diminuisco il delay", "", "BATAK 2.0");
      }
    }
  }
}

/**
   Programma numero: 4, 11 e 12 Stretching angolare

   Vengono accessi per 1 secondo pulsanti agli estremi del telaio, quando
   l'utente preme un pulsante sbagliato il tempo per premerlo diminuisce.

   @param maxbuttons numero massimo di bottoni da premere.
   @program 4 per il programma 4, 11 per l'11 e 12 per il 12.
*/
void angularStretching(int maxbuttons, int program) {
#define ANGULAR_STRETCHING_SIZE 7
  int timeout = 1000;
  int angularPins[ANGULAR_STRETCHING_SIZE] = {22, 42, 24, 30, 32, 38, 40};
  long start = millis();
  long startButton = millis();
  long elapsed = 0;
  int leftButtons = maxbuttons;

  int currentPin = getRandom(angularPins, ANGULAR_STRETCHING_SIZE);
  digitalWrite(currentPin + 1, HIGH);

  while (leftButtons > 0 && programRunning)
  {
    elapsed = (millis() - start);
    if (program == 4)
    {
      sendData(0, elapsed / 100);
    }
    if (millis() - startButton > timeout)
    {
      digitalWrite(currentPin + 1, LOW);
      currentPin = getRandom(angularPins, ANGULAR_STRETCHING_SIZE);
      startButton = millis();
      digitalWrite(currentPin + 1, HIGH);
    }
    bool presslastState = getLastState(currentPin);
    bool presscurrentState = isPressed(currentPin);
    if (presslastState == HIGH && presslastState != presscurrentState)
    {
      leftButtons--;
      sendData(1, leftButtons);
      if (program != 4)
      {
        sendData(0, maxbuttons - leftButtons);
      }
      digitalWrite(currentPin + 1, LOW);
      currentPin = getRandom(angularPins, ANGULAR_STRETCHING_SIZE);
      startButton = millis();
      digitalWrite(currentPin + 1, HIGH);
    }
    for (int i = 0; i < SIZE; i++)
    {
      int pin = buttonPins[i];
      if (pin == currentPin)
      {
        continue;
      }
      bool lastState = getLastState(pin);
      bool currentState = isPressed(pin);
      if (currentState == HIGH && currentState != lastState)
      {
        timeout -= 100;
        if (timeout < 200)
        {
          timeout = 200;
        }
        setLcdText("Hai sbagliato,", "diminuisco il delay", "", "BATAK 2.0");
      }
    }
  }
}

/**
   Programma 3, 17 e 18: Corsa

   Il programma accende in modo casuale dei pulsanti per un determinato tempo o massimo.

   @param duation la durata massima del programma.
   @param maxbuttons il numero massimo di bottoni da premere.
   @param senior se usare array senior o junior.
*/
void rush(long duration, int maxbuttons, boolean senior) {
  long start = millis();
  long elapsed = 0;
  int pressedButtons = 0;

  int currentPin;
  if (senior)
  {
    currentPin = getRandom(buttonPins, SIZE);
  }
  else
  {
    currentPin = getRandom(juniorPins, JUNIOR_SIZE);
  }
  digitalWrite(currentPin + 1, HIGH);


  while (elapsed <= duration && pressedButtons < maxbuttons && programRunning)
  {
    isPressed(44);
    elapsed = (millis() - start);
    sendData(0, elapsed / 100);
    bool presslastState = getLastState(currentPin);
    bool presscurrentState = isPressed(currentPin);
    if (presslastState == HIGH && presslastState != presscurrentState)
    {
      pressedButtons++;
      sendData(1, pressedButtons);
      digitalWrite(currentPin + 1, LOW);
      if (senior)
      {
        currentPin = getRandom(buttonPins, SIZE);
      }
      else
      {
        currentPin = getRandom(juniorPins, JUNIOR_SIZE);
      }
      digitalWrite(currentPin + 1, HIGH);
    }
  }
}

/**
   Programma numero: 1,2,8,15,16 e 19: Cumulativo

   Il programma ha una durata massima per il quale conta i pulsanti premuti.

   @param duration la durata massima del programma.
   @param senior se usare array senior o junior.
*/
void cumulative(long duration, boolean senior) {
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

  while (elapsed <= duration && programRunning)
  {
    isPressed(44);
    elapsed = (millis() - start);
    sendData(0, elapsed / 100);
    bool presslastState = getLastState(currentPin);
    bool presscurrentState = isPressed(currentPin);
    if (presslastState == HIGH && presslastState != presscurrentState)
    {
      pressedButtons++;
      sendData(1, pressedButtons);
      digitalWrite(currentPin + 1, LOW);
      if (senior)
      {
        currentPin = getRandom(buttonPins, SIZE);
      }
      else
      {
        currentPin = getRandom(juniorPins, JUNIOR_SIZE);
      }
      digitalWrite(currentPin + 1, HIGH);
    }
  }
  resetButtonsState();
  resetLeds();
}

/**
   Programma numero: 6, Beep Test

   10 livelli con 30 pulsanti per livello. L'utente deve premere i pulsanti ad
   una determinata frequenza, se sbaglia o non fa in tempo ci sarà un feedback audio.
*/
void beepTest() {
  int levels = 10;
  int buttons = 10;
  int timeout = 1400;

  long elapsed = 0;
  long start = millis();
  long startButton = millis();
  int pressedButtons = 0;
  int errors = 0;
  int currentPin = getRandom(buttonPins, SIZE);
  digitalWrite(currentPin + 1, HIGH);
  for (int l = 0; l < levels && errors <= 2 && programRunning; l++)
  {
    setLcdText("Livello:", String(l + 1), "", "BATAK 2.0");
    while (pressedButtons <= buttons * l && errors <= 2 && programRunning)
    {
      elapsed = (millis() - start);
      sendData(0, elapsed / 100);
      if (millis() - startButton > timeout)
      {
        digitalWrite(currentPin + 1, LOW);
        currentPin = getRandom(buttonPins, SIZE);
        errors++;
        for (int i = 0; i < errors; i++)
        {
          tone(buzzerPin, 2000);
          delay(100);
          noTone(buzzerPin);
          delay(50);
        }
        startButton = millis();
        digitalWrite(currentPin + 1, HIGH);
      }
      bool presslastState = getLastState(currentPin);
      bool presscurrentState = isPressed(currentPin);
      if (presslastState == HIGH && presslastState != presscurrentState)
      {
        errors = 0;
        pressedButtons++;
        sendData(1, pressedButtons);
        digitalWrite(currentPin + 1, LOW);
        currentPin = getRandom(buttonPins, SIZE);
        startButton = millis();
        digitalWrite(currentPin + 1, HIGH);
      }
      for (int i = 0; i < SIZE; i++)
      {
        int pin = buttonPins[i];
        if (pin == currentPin)
        {
          continue;
        }
        bool lastState = getLastState(pin);
        bool currentState = isPressed(pin);
        if (currentState == HIGH && currentState != lastState)
        {
          errors++;
          for (int i = 0; i < errors; i++)
          {
            tone(buzzerPin, 2000);
            delay(100);
            noTone(buzzerPin);
            delay(50);
          }
        }
      }
    }
  }
}

/**
   Programma numero: 9, Somma aritmetica

   Il programma chiede all'utente un tempo massimo per risposta.
   Vengono proposte 8 addizioni.
*/
void mathsum() {

  bool waiting = true;
  int millisec = 0;
  int points = 0;
  setLcdText("Seleziona un tempo", "entro il quale", "rispondere (2 - 9 s)", "BATAK 2.0");
  while (waiting)
  {
    for (int i = 0; i < SIZE; i++)
    {
      int bpin = buttonPins[i];
      bool lastState = getLastState(bpin);
      bool currentState = isPressed(bpin);
      if (currentState == HIGH && currentState != lastState)
      {
        digitalWrite(bpin + 1, HIGH);
        int label = getLabel(bpin);
        if (label >= 2 && label <= 9)
        {
          millisec = label * 1000;
          waiting = false;
        }
        else
        {
          return;
        }
      }
    }
  }
  setLcdText("Hai selezionato: " + String(millisec / 1000), "Inizio in 3 secondi", "", "BATAK 2.0");
  delay(3000);
  resetButtonsState();
  resetLeds();
  long startTime = 0;
  for (int i = 0; i < 8; i++)
  {
    int sum = 10;
    int one = 0;
    int two = 0;
    while (sum >= 10)
    {
      one = random(0, 9);
      two = random(0, 9);
      sum = one + two;
    }
    setLcdText(String(one) + " + " + String(two) + " = ?", "Punti: " + String(points) + "/8", "", "BATAK 2.0");
    sendData(0, one);
    sendData(1, two);

    startTime = millis();
    waiting = true;
    while (millis() - startTime <= millisec && waiting && programRunning)
    {
      for (int x = 0; x < SIZE; x++)
      {
        int bpin = buttonPins[x];
        bool lastState = getLastState(bpin);
        bool currentState = isPressed(bpin);
        if (currentState == HIGH && currentState != lastState && getLabel(bpin) == sum)
        {
          points++;
          setLcdText(String(one) + " + " + String(two) + " = ?", "Punti: " + String(points) + "/8", "", "BATAK 2.0");
          waiting = false;
        }
      }
    }
  }
  if (points == 8)
  {
    setLcdText("Punteggio massimo!", "", "", "BATAK 2.0");
    winSong();
  }
  setLcdText("Hai finito!", "Punti: " + String(points) + "/8", "", "BATAK 2.0");
}
