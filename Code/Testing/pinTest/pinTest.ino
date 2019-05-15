/**
   pinTest

   Programma utilizzato per testare i pin e i led.

   @author Filippo Finke
*/

/**
   Gandezza dell'array contenente i pin dei bottoni e led.
*/
#define SIZE 12

/**
   Array che contiene tutti i pin dei bottoni.
*/
int buttonPins[SIZE] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44};

/**
   Array che contiene tutti i pin dei led.
*/
int ledPins[SIZE] =    {23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45};

/**
   Metodo utilizzato per ricavare lo stato di un pulsante.

   @param pin il pulsante da controllare.
*/
bool isPressed(int pin)
{
  bool current = !digitalRead(buttonPins[pin]);
  return current;
}

/**
   Metodo eseguito all'avvio di arduino.
*/
void setup() {
  Serial.begin(9600);
  Serial.println("SETUP PIN");
  int i = 0;
  for (i = 0; i < SIZE; i++)
  {
    Serial.print("I: ");
    Serial.print(i);
    Serial.print(" PIN: ");
    Serial.println(buttonPins[i]);
    pinMode(buttonPins[i], INPUT);
  }
  i = 0;
  for (i = 0; i < SIZE; i++)
  {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
  Serial.println("AVVIO PROGRAMMA");
}

/**
   Metodo principale in cui viene svolto l'intero programma.
*/
void loop() {
  for (int i = 0; i < SIZE; i++)
  {
    if (isPressed(i))
    {
      Serial.println(buttonPins[i]);
      digitalWrite(ledPins[i], HIGH);
    }
    else
    {
      digitalWrite(ledPins[i], LOW);
    }
  }
}
