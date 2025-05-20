#include <Arduino.h>
byte customChar[] = {
  B00000,
  B00000,
  B00100,
  B00110,
  B11111,
  B00110,
  B00100,
  B00000
};
void setup()
{
 lcd.createChar(0, setaEsquerda);

}

void loop()
{
}