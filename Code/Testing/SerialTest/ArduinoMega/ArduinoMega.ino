/**
   ArduinoMega
   Programma per testare la comuncazione tra due arduini.

   @author Filippo Finke
*/
/**
   Libreria Wire.h utilizzata per la comunicazione tra i due arduini.
*/
#include <Wire.h>

/**
   Variabile utilizzata come contatore.
*/
byte x = 0;


/**
   Metodo che si occupa di impostare la connessione seriale, SDA, SCL.
*/
void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("ArduinoMega");
}

/**
   Metodo eseguito all'infinito da arduino.
*/
void loop() {
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  Serial.println("inviato x");
  x++;
  delay(500);
}
