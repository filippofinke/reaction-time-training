/**
   b_functions
   File che contiene tutte le funzioni utili.

   @author Filippo Finke
*/

/**
   Variabile utilizzata per tenere conto del tempo per il quale il bottone di
   uscita è stato premuto.
*/
long resetTime = 0;

/**
   Metodo che ritorna un pin casuale dell'array passato come parametro.

   @param pins[] array di pin.
   @param size dimensione dell'array.
   @return pin casuale dell'array passato come parametro.
*/
int getRandom(int pins[], int size) {
  int pin = pins[random(0, size + 1)];
  if (pin >= 22 && pin <= 45)
  {
    return pin;
  }
  return getRandom(pins, size);
}

/**
  Metodo utilizzato per impostare la prima e la seconda linea del display LCD.

  @param firstLine la prima riga.
  @secondLine la seconda riga.
*/
void setLcdText(String firstLine, String secondLine, String thirdLine, String fourthLine)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(firstLine);
  lcd.setCursor(0, 1);
  lcd.print(secondLine);
  lcd.setCursor(0, 2);
  lcd.print(thirdLine);
  lcd.setCursor(0, 3);
  lcd.print(fourthLine);
}

/**
   Metodo che ritorna il numero del pulsante in base al pin.

   @param pin pin di cui si vuole ottenere il numero del bottone.
   @return numero del pulsante.
*/
int getLabel(int pin)
{
  return (pin - 22) / 2;
}

/**
   Metodo utilizzato per inviare un long attraverso i pin SDA e SCL.

   @param type il tipo di display sette segmenti 1 quello a sinistra, 0 quello a destra.
   @param value il valore da inviare.
*/
void sendData(byte type, long value)
{
  Wire.beginTransmission(8);
  byte times[5];
  times[0] = type;
  times[1] = (value >> 24) & 0xFF;
  times[2] = (value >> 16) & 0xFF;
  times[3] = (value >> 8) & 0xFF;
  times[4] = value & 0xFF;
  Wire.write(times, 5);
  Wire.endTransmission();
}

/**
   Metodo che resetta entrambi i sette segmenti.
*/
void resets7Segments()
{
  sendData(0, 0);
  sendData(1, 0);
}

/**
   Metodo che spegne tutti i LED.
*/
void resetLeds() {
  for (int i = 0; i < SIZE; i++)
  {
    digitalWrite(ledPins[i], LOW);
  }
}

/**
   Metodo che reimposta lo stato di tutti i bottoni.
*/
void resetButtonsState()
{
  for (int i = 0; i < SIZE; i++)
  {
    buttonStatus[i] = false;
  }
}

/**
   Metodo che permette di ricavare l'ultimo stato di un bottone.

   @param pin il pin del bottone da controllare.
   @return lo stato precedente del bottone.
*/
bool getLastState(int pin)
{
  int index = getLabel(pin);
  return buttonStatus[index];
}

/**
   Metodo utilizzato per impostare lo stato di un bottone.

   @param pin il pin del bottone.
   @param state lo stato del bottone.
*/
void setLastState(int pin, bool state)
{
  int index = getLabel(pin);
  buttonStatus[index] = state;
  if (state == HIGH && pin == 44)
  {
    if (resetTime != 0)
    {
      long elapsed = millis() - resetTime;
      if (elapsed > 2500)
      {
        programRunning = false;
        resetTime = 0;
        resetLeds();
        setLcdText("Esco dal programma", "", "", "BATAK 2.0");
        delay(1000);
      }
    }
    else
    {
      resetTime = millis();
    }
  }
  else if (state == LOW && pin == 44)
  {
    resetTime = 0;
  }
}

/**
   Metodo che ritorna lo stato di un bottone.

   @return lo stato del pin.
*/
bool isPressed(int pin)
{
  bool state = !digitalRead(pin);
  setLastState(pin, state);
  delay(5);
  return state;
}
