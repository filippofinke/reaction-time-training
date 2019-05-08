/**
   a_config
   File di setup e configurazione per tutto il programma.

   @author Filippo Finke
*/
/**
   Libreria Wire.h utilizzata per la comunicazione tra i due arduini.
*/
#include <Wire.h>
/**
   Libreia utilizzata per la gestione del display LCD.
*/
#include <LiquidCrystal_I2C.h>

/**
   Gandezza dell'array contenente i pin dei bottoni e led.
*/
#define SIZE 12
/**
   Grandezza dell'array contenente i pin dei bottoni per le modalità junior.
*/
#define JUNIOR_SIZE 8

/**
   Array che contiene tutti i pin dei bottoni.
*/
int buttonPins[SIZE] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44};

/**
   Array che contiene tutti i pin dei led.
*/
int ledPins[SIZE] =    {23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45};

/**
   Array che contiene tutti i pin dei bottoni junior.
*/
int juniorPins[JUNIOR_SIZE] = {22, 24, 26, 28, 30, 32, 42, 44};

/**
   Array che contiene lo stato di tutti i bottoni.
*/
bool buttonStatus[SIZE] = {false, false, false, false, false, false, false, false, false, false, false, false};

/**
   Pin al quale è collegato il cicalino.
*/
int buzzerPin = 6;

/**
   Variabile utilizzata per interrompere l'eseguzione di un programma.
*/
boolean programRunning = true;

/**
   Istanza del display LCD.
*/
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

/**
   Metodo di setup che si occupa di avviare la connessione seriale, SDA, SCL, impostare il display LCD e i vari pin.
*/
void setup() {
  Wire.begin();
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.backlight();

  pinMode(buzzerPin, OUTPUT);
  for (int i = 0; i < SIZE; i++)
  {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT);
  }
  Serial.println("BATAK 2.0 AVVIATO!");
}
