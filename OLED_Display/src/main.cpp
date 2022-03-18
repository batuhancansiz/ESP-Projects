#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include "logo1.h"
Adafruit_SH1106 display(21,22);


void setup()   {                
  Serial.begin(9600);
  /* initialize OLED with I2C address 0x3C */
  display.begin(SH1106_SWITCHCAPVCC, 0x3C); 
  display.clearDisplay();
  display.drawBitmap(0,0,bitmap_takipsan,128,64,WHITE);
  display.display();
}


void loop() { 
  display.print()
}