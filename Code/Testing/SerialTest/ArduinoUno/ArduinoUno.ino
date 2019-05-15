/**
   ArduinoUNO
   Programma per testare la comuncazione tra due arduini.

   @author Filippo Finke
*/
/**
   Libreria Wire.h utilizzata per la comunicazione tra i due arduini.
*/
#include <Wire.h>

/**
   Metodo che si occupa di impostare la connessione seriale, SDA, SCL.
*/
void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);
  Serial.println("ArduinoUNO");// start serial for output
}

/**
   Metodo eseguito all'infinito da arduino.
*/
void loop() {
  delay(100);
}

/**
   Funzione eseguita quando si ricevono dei bytes.

   @param howMany il numero di bytes da leggere.
*/
void receiveEvent(int howMany) {
  while (1 < Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
  }
  int x = Wire.read();
  Serial.println(x);
}
