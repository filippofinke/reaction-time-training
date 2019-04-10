/*
 * c_programs
 *
 * @author Filippo Finke
 */

void systemCheck() {
  setLcdText("Avvio procedura", "di test");
  setLcdText("Test buzzer", "1 secondo");
  tone(buzzerPin, 2000);
  delay(1000);
  noTone(buzzerPin);
  for (int i = 0; i < SIZE; i++)
  {
    int pin = buttonPins[i];
    String text = String(getLabel(pin));
    if (text == 10)
    {
      text = "#";
    }
    else if (text == 11)
    {
      text = "@";
    }
    setLcdText("Premi il tasto", text);
    while (!isPressed(pin)) {
    }
    digitalWrite(pin + 1, HIGH);
    setLcdText("Led del tasto", "acceso");
    delay(1000);
  }
  setLcdText("Fine", "Procedura");
  delay(2500);
}

void flashtest() {
  resetLeds();
  setLcdText("Seleziona tempo", "1 - 8 s");
  bool waiting = true;
  int selectedtime = 0;
  while (waiting)
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
  setLcdText("Selezionato:", String(selectedtime / 1000) + " s");
  resetLeds();
  int points = 0;
  bool playing = true;
  delay(200);
  for (int i = 0; i < 5 && playing; i++)
  {
    resetLeds();
    sendData(1, i + 1);
    setLcdText("Schema:", String(i + 1) + "/5");
    int sequence[6];
    for (int i = 0; i < 6; i++)
    {
      int rndpin = getRandom(buttonPins, SIZE);
      sequence[i] = rndpin;
      digitalWrite(rndpin + 1, HIGH);
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
    while (insideLevel)
    {
      if (millis() - startTime >= selectedtime)
      {
        playing = false;
        break;
      }
      for (int b = 0; b < SIZE && insideLevel && playing; b++)
      {
        int pin = buttonPins[b];
        bool presslastState = getLastState(pin);
        bool presscurrentState = isPressed(pin);
        if (presslastState == HIGH && presslastState != presscurrentState)
        {
          bool edited = false;
          for (int x = 0; x < 6; x++) {
            if (sequence[x] == pin) {
              Serial.println(String(sequence[x]) + " " + String(pin));
              edited = true;
              digitalWrite(pin + 1, LOW);
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
            setLcdText("Hai sbagliato", "");
            delay(1000);
          }
          delay(150);
        }
      }
    }
  }
}

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
  for (int i = 0; i < 17 && playing; i++)
  {
    sendData(1, (i + 1));
    setLcdText("Livello:" + String(i + 1), "Osserva");
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
    setLcdText("Ripeti la", "sequenza");
    resetButtonsState();
    pressed = 0;
    toShow += 1;
    insideLevel = true;
    while (insideLevel && playing)
    {
      for (int b = 0; b < SIZE && playing && insideLevel; b++)
      {
        int pin = buttonPins[b];
        bool presslastState = getLastState(pin);
        bool presscurrentState = isPressed(pin);
        if (presslastState == HIGH && presslastState != presscurrentState)
        {
          Serial.println("Premuto:");
          Serial.println(pin);
          Serial.println("Aspettato:");
          Serial.println(sequence[pressed]);
          Serial.println("################");
          if (pin == sequence[pressed])
          {
            digitalWrite(pin + 1, HIGH);
            pressed += 1;
            points += 1;
            sendData(0, points);
            delay(150);
            if (pressed == toShow - 1)
            {
              insideLevel = false;
            }
          }
          else
          {
            playing = false;
            setLcdText("Hai sbagliato", "la sequenza");
            delay(1000);
          }
        }
      }
    }
    resetLeds();
  }
}

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

  while (pressedButtons < maxbuttons)
  {
    elapsed = millis() - startButton;
    sendData(0, (timeout - elapsed) / 100);
    if (elapsed > timeout)
    {
      Serial.print("Timeout: ");
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
      startButton = millis();
      Serial.print("Accendo: ");
      Serial.println(currentPin);
      digitalWrite(currentPin + 1, HIGH);
    }
    bool presslastState = getLastState(currentPin);
    bool presscurrentState = isPressed(currentPin);
    if (presslastState == HIGH && presslastState != presscurrentState)
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
      startButton = millis();
      Serial.print("Accendo: ");
      Serial.println(currentPin);
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
        Serial.print("Hai sbagliato, nuovo timeout: ");
        Serial.println(timeout);
      }
    }
  }
  Serial.print("Fine modalità!");
}

void angularStretching(int maxbuttons, int program) {
#define ANGULAR_STRETCHING_SIZE 7
  int timeout = 1000;

  int angularPins[ANGULAR_STRETCHING_SIZE] = {22, 42, 24, 30, 32, 38, 40};
  Serial.print("MAXBUTTONS: ");
  Serial.println(maxbuttons);
  long start = millis();
  long startButton = millis();
  long elapsed = 0;
  int leftButtons = maxbuttons;

  int currentPin = getRandom(angularPins, ANGULAR_STRETCHING_SIZE);
  digitalWrite(currentPin + 1, HIGH);

  while (leftButtons > 0)
  {
    elapsed = (millis() - start);
    if (program == 4)
    {
      sendData(0, elapsed / 100);
    }
    if (millis() - startButton > timeout)
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
      Serial.print("Premuto: ");
      Serial.println(currentPin);
      digitalWrite(currentPin + 1, LOW);
      currentPin = getRandom(angularPins, ANGULAR_STRETCHING_SIZE);
      startButton = millis();
      Serial.print("Accendo: ");
      Serial.println(currentPin);
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
        Serial.print("Hai sbagliato, nuovo timeout: ");
        Serial.println(timeout);
      }
    }
  }
  Serial.print("Fine modalità!");
}

void rush(long duration, int maxbuttons, boolean senior) {
  Serial.print("DURATA ");
  Serial.println(duration);
  Serial.print("MAXBUTTONS: ");
  Serial.println(maxbuttons);
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


  while (elapsed <= duration && pressedButtons < maxbuttons)
  {
    elapsed = (millis() - start);
    sendData(0, elapsed / 100);
    bool presslastState = getLastState(currentPin);
    bool presscurrentState = isPressed(currentPin);
    if (presslastState == HIGH && presslastState != presscurrentState)
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
    bool presslastState = getLastState(currentPin);
    bool presscurrentState = isPressed(currentPin);
    if (presslastState == HIGH && presslastState != presscurrentState)
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
  for (int l = 0; l < levels && errors <= 2; l++)
  {
    Serial.print("Livello: ");
    Serial.println(l + 1);
    setLcdText("Livello:", String(l + 1));
    while (pressedButtons <= buttons * l && errors <= 2)
    {
      elapsed = (millis() - start);
      sendData(0, elapsed / 100);
      if (millis() - startButton > timeout)
      {
        Serial.print("Timeout: ");
        Serial.println(currentPin);
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
        Serial.print("Accendo: ");
        Serial.println(currentPin);
        digitalWrite(currentPin + 1, HIGH);
      }
      bool presslastState = getLastState(currentPin);
      bool presscurrentState = isPressed(currentPin);
      if (presslastState == HIGH && presslastState != presscurrentState)
      {
        errors = 0;
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
  Serial.print("Fine modalità! Punteggio: ");
  Serial.println(pressedButtons);
}

void mathsum() {

  bool waiting = true;
  int millisec = 0;
  int points = 0;
  setLcdText("Tempo in s", "Scegli tra 2-9");
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
          Serial.print("Ms:");
          Serial.println(millisec);
          waiting = false;
        }
        else
        {
          return;
        }
      }
    }
  }
  setLcdText("Tempo:" + String(millisec / 1000), "Inizio in 3 sec");
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
    setLcdText(String(one) + " + " + String(two) + " = ?", String(points) + "/8");
    Serial.print(one);
    Serial.print(" + ");
    Serial.print(two);
    Serial.print(" = ");
    Serial.println(sum);

    sendData(0, one);
    sendData(1, two);

    startTime = millis();
    waiting = true;
    while (millis() - startTime <= millisec && waiting)
    {
      for (int x = 0; x < SIZE; x++)
      {
        int bpin = buttonPins[x];
        bool lastState = getLastState(bpin);
        bool currentState = isPressed(bpin);
        if (currentState == HIGH && currentState != lastState && getLabel(bpin) == sum)
        {
          Serial.println("Risultato corretto Passo al prossimo!");
          points++;
          setLcdText("Punti (MAX 8)", String(points));
          waiting = false;
        }
      }
    }
  }
  Serial.print("Punti: ");
  Serial.print(points);
  Serial.println("/8");
  if (points == 8)
  {
    setLcdText("Punteggio", "massimo!");
    winSong();
  }
  setLcdText("Finito", String(points) + "/8");
}
