/*
  Basic demo for HT16D35A
  By: John Tito
  Date: 06/19, 2022
  License: BSD 3 Clause
*/

#include <Arduino.h>
#include <pins_arduino.h>

void setup()
{

  Serial.begin(115200);
  Serial.setDebugOutput(true);

  Serial.printf(" init done\n");
}

void loop()
{
  while (1)
  {
    delay(1000);
  }
}
