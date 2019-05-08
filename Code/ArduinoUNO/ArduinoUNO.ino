/**
   ArduinoUNO
   Programma che gestisce le richieste da parte dell'ArduinoMega.

   @author Filippo Finke
*/
/**
   Libreria Wire.h utilizzata per la comunicazione tra i due arduini.
*/
#include <Wire.h>
/**
   Libreria AdaFruit utilizzata per la gestione dei display sette segmenti.
*/
#include <Adafruit_GFX.h>
/**
   Libreria AdaFruit utilizzata per la gestione dei display sette segmenti.
*/
#include "Adafruit_LEDBackpack.h"
/**
   Libreria SevenSeg utilizzata per la gestione dei display sette segmenti.
*/
#include "SevSeg.h"

/**
   Istanza di un display sette segmenti.
*/
SevSeg sevenSeg;

/**
   Istanza di un display sette segmenti.
*/
Adafruit_7segment matrix = Adafruit_7segment();

/**
   Variabile nel quale viene salvato il tempo ricavato dall'ArduinoMega.
*/
long tempo = 0;

/**
   Variabile nel quale vengono salvati i punti ricavati dall'ArduinoMega.
*/
long points = 0;

/**
   Variabile che definisce se si devono aggiornare o no i sette segmenti.
*/
boolean updateNeeded = true;

/**
   Metodo che si occupa di impostare la connessione seriale, SDA, SCL, inizializzare i sette segmenti.
*/
void setup() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  Serial.println("ArduinoUNO Avviato!");
  matrix.begin(0x70);
  int displayType = COMMON_CATHODE;

  int digit1 = 10;
  int digit2 = 11;
  int digit3 = 12;
  int digit4 = 13;

  int segA = 6;
  int segB = 8;
  int segC = 2;
  int segD = 5;
  int segE = 4;
  int segF = 7;
  int segG = 3;
  int segDP = 5;

  int numberOfDigits = 4;

  sevenSeg.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, segDP);

  sevenSeg.SetBrightness(100);

}

/**
   Metodo che aggiorna i valori dei sette segmenti.
*/
void loop() {
  if (updateNeeded) {
    matrix.writeDigitNum(0, (tempo / 1000), false);
    matrix.writeDigitNum(1, (tempo / 100) % 10, false);
    matrix.writeDigitNum(3, (tempo / 10) % 10, true);
    matrix.writeDigitNum(4, tempo % 10, false);
    matrix.writeDisplay();
    updateNeeded = false;
    Serial.print("Seg1 :");
    Serial.println(tempo);
    Serial.print("Seg2: ");
    Serial.println(points);
  }
  char tempString[10];
  sprintf(tempString, "%04d", points);
  sevenSeg.DisplayString(tempString, 3);
  delay(10);
}

/**
   Metodo chiamato quando si ricevono dati dalla connessione SDA e SCL.

   @param bytes i bytes letti dalla connessione.
*/
void receiveEvent(int bytes) {
  int value;
  byte s, a, b, c, d;
  s = Wire.read();
  a = Wire.read();
  b = Wire.read();
  c = Wire.read();
  d = Wire.read();

  value = a;
  value = (value << 8) | b;
  value = (value << 8) | c;
  value = (value << 8) | d;
  if (s == 0)
  {
    tempo = value;
  }
  else if (s == 1)
  {
    points = value;
  }
  updateNeeded = true;
}
