/*************************************************** 
 Blinkenlights for Ardunio
 Copyright 2013, Alexander von Gluck IV <kallisti5@unixzen.com>
 Licensed under the MIT license.
 
 This will generate a CPU usage graph on an
 Adafruit 8x8 i2c LED display.
 
 Requires:
   Adafruit_GFX Library
   Adafruit_LEDBackpack Library

 Supports 1-8 CPUS

 Wire: Clock to a5, data to a4
 
 A modern and tiny BeBox Blinkenlights
 ****************************************************/

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

void setup() {
  Serial.begin(9600);
  Serial.println("Blinkenlights start");
  
  matrix.begin(0x70);
}


void loop() {
  int8_t cpuCount = 4;
  
  matrix.clear();
  for (int8_t cpuID=0; cpuID < cpuCount; cpuID++) {
    int8_t usage = random(0, 100);
    graphCPU(cpuCount, cpuID, usage);
  }
  delay(100);
}

void graphCPU(int8_t cpuCount, int8_t cpuID, int8_t cpuUsage) {
  
  int8_t linesPerCPU = 0;
  switch(cpuCount) {
    case 8:
    case 6:
      linesPerCPU = 1;
      break;
    case 4:
    case 3:
      linesPerCPU = 2;
      break;
    case 2:
      linesPerCPU = 4;
      break;
    case 1:
      linesPerCPU = 8;
      break;
  }
  

  int8_t usagePoints = (cpuUsage / 0.80) / 10;
  for (int8_t line = 0; line < linesPerCPU; line++) {
    int8_t start = cpuID * linesPerCPU;
    matrix.drawLine(start + line, 0, start + line, usagePoints, LED_ON);
    delay(1);
  }
  matrix.writeDisplay();
}
