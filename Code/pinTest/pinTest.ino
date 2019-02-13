
#define SIZE 12
int buttonPins[SIZE] = {22,24,26,28,30,32,34,36,38,40,42,44};
int ledPins[SIZE] =    {23,25,27,29,31,33,35,37,39,41,43,45};

/*
 * Pari = Bottoni
 * Dispari = LED
 */

bool debounce(int pin)
{
  bool current = !digitalRead(buttonPins[pin]);
  return current;
}

void setup() {
  Serial.begin(9600);
  Serial.println("SETUP PIN");
  int i = 0;
  for(i = 0; i < SIZE; i++)
  {
    Serial.print("I: ");
    Serial.print(i);
    Serial.print(" PIN: ");
    Serial.println(buttonPins[i]);
    pinMode(buttonPins[i], INPUT);
  }
  i = 0;
  for(i = 0; i < SIZE; i++)
  {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
  Serial.println("AVVIO PROGRAMMA");
}

void loop() {
  for(int i = 0; i < SIZE; i++)
  {
    if(debounce(i))
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
