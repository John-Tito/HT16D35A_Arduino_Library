/*
  HT16D35A.h
  HT16D35A Header File
  By: John Tito
  Date: 06/19, 2022
  License: BSD 3 Clause
*/

#include "Arduino.h"
#include "SPI.h"

#ifndef HT16D35A_H
#define HT16D35A_H
 
class HT16D35A
{
private: // These private functions are not available to Arduino sketches.

public: // These public functions are available to Arduino sketches.
  HT16D35A();
  uint8_t begin(uint8_t address);

};     // HT16D35A class
#endif // HT16D35A_H
