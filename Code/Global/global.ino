#define SIZE 12
#define JUNIOR_SIZE 8
int buttonPins[SIZE] = {22,24,26,28,30,32,34,36,38,40,42,44};
int ledPins[SIZE] =    {23,25,27,29,31,33,35,37,39,41,43,45};

int juniorPins[JUNIOR_SIZE] = {22,24,26,28,30,32,42,44};


int getRandom(int pins[], int size) {
  return pins[random(0,size + 1)];
}


void waitUser() {
  bool state = false;
  int counter = 0;
  while(!state)
  {
    if(counter>= 1000)
    {
      counter = 0;
      int ledPin = getRandom(ledPins, SIZE);
      bool ledState = digitalRead(ledPin);
      digitalWrite(ledPin, !ledState);
    }
    counter++;
    digitalWrite(45, HIGH);
    state = !digitalRead(44);
  }
  resetLeds();
  bool ls = LOW;
  for(int i = 0; i < 3; i++)
  {
    ls = !ls;
    digitalWrite(45, ls);
    delay(500);
  }
  resetLeds();
}

void resetLeds() {
  for(int i = 0; i < SIZE; i++)
  { 
    digitalWrite(ledPins[i], LOW);
  }
}

bool isPressed(int pin)
{
  return !digitalRead(pin);
}

void pinSetup() {
  for(int i = 0; i < SIZE; i++)
  { 
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT);
  }
}

void cumulative(long duration, bool senior) {
  long start = millis();
  long reactionTime = 0;
  long time = 0;
  int currentPin;
  if(senior)
  {
    currentPin = getRandom(buttonPins, SIZE);
  }
  else
  {
    currentPin = getRandom(juniorPins, JUNIOR_SIZE);
  }
  int pressedButtons = 0;
  digitalWrite(currentPin + 1, HIGH);
  
  while(time <= duration)
  {
    time = (millis() - start);
    if(time % 1000 == 0)
    {
      Serial.print("Tempo rimanente: ");
      Serial.println((duration - time) / 1000);
    }
    if(isPressed(currentPin))
    {
      pressedButtons++;
      Serial.print("Premuto: ");
      Serial.println(currentPin);
      digitalWrite(currentPin + 1, LOW);
      if(senior)
      {
        currentPin = getRandom(buttonPins, SIZE);
      }
      else
      {
        currentPin = getRandom(juniorPins, JUNIOR_SIZE);
      }
      reactionTime = millis();
      Serial.print("Accendo: ");
      Serial.println(currentPin);
      digitalWrite(currentPin + 1, HIGH);
    }
  }
  Serial.print("Fine modalità! Punteggio: ");
  Serial.println(pressedButtons);
}

void setup() {
  Serial.begin(9600);
  pinSetup();
  Serial.println("BATAK 2.0 AVVIATO!");
}

void loop() {
  waitUser();
  Serial.println("AVVIO PROGRAMMA");
  cumulative(10000, false);
  Serial.println("HO FINITO");
}
