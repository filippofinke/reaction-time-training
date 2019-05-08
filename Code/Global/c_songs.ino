/**
   c_songs
   File che permette di eseguire una canzoncina attraverso l'utilizzo del cicalino.

   @author Filippo Finke

   La versione corrente è una versione modificata e adattata da Filippo Finke
   della versione originale di @nicksort.
   Versione originale: https://gist.github.com/nicksort/4736535
*/

/**
   Costanti che rappresentano le varie note.
*/
const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;

/**
   Metodo che emette la nota passata come parametro per la durata desiderata.

   @param note nota da emettere.
   @param duration durata dell'emissione della nota.
*/
void beep(int note, int duration)
{
  tone(buzzerPin, note);
  delay(duration);
  noTone(buzzerPin);

}

/**
   Metodo che compone con una sequenza di note una canzone.
*/
void winSong()
{
  beep(a, 500);
  beep(a, 500);
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
}
