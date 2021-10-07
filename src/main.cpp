#include <Arduino.h>

#define SHIFT_CLOCK 3
#define SHIFT_DATA 13

void setup()
{
  pinMode(SHIFT_CLOCK, OUTPUT);
  pinMode(SHIFT_DATA, OUTPUT);
}

void loop()
{
  digitalWrite(SHIFT_CLOCK, LOW);
  digitalWrite(SHIFT_DATA, HIGH);
  digitalWrite(SHIFT_CLOCK, HIGH);

  delay(1000);

  digitalWrite(SHIFT_CLOCK, LOW);
  digitalWrite(SHIFT_DATA, LOW);
  digitalWrite(SHIFT_CLOCK, HIGH);

  delay(1000);
}
