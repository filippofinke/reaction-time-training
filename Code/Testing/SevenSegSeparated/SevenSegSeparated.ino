/**
   SevenSegSeparated

   Programma utilizzato per testare il 7 segmenti con pin separrati.

   @author Filippo Finke
*/

/**
   Libreria SevenSeg utilizzata per la gestione dei display sette segmenti.
*/
#include "SevSeg.h"

/**
   Istanza di un display sette segmenti.
*/
SevSeg sevenSeg;

/**
   Variabile per tenere un contatore.
*/
int x = 0;

/**
 * Varriabile da stamparre sul sette segmenti.
 */
int deciSecond = 0;

/**
 * Metodo che si occupa di istanziare e impostare il sette segmenti.
 */
void setup()
{
  Serial.begin(9600);
  Serial.println("SevenSeg Test");
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
   Metodo che aggiorna i valori del sette segmenti.
*/
void loop()
{
  char tempString[10];
  sprintf(tempString, "%04d", deciSecond);
  sevenSeg.DisplayString(tempString, 3);
  x++;
  if (x % 10000)
  {
    deciSecond++;
  }
}
