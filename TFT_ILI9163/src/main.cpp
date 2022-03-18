#include "Wire.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>
#include "images.h"

// Color definitions
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF

uint16_t count=0;
char message[30];

#define __CS 5
#define __DC 2
#define __RST 4
TFT_ILI9163C tft = TFT_ILI9163C(__CS, __DC,__RST);


void setup() {
  tft.begin();
  tft.drawBitmap(0,0,takipsan,128,128,WHITE);
  delay(3000);
  tft.fillScreen(WHITE);
  tft.drawBitmap(0,0,wifi,15,15,BLACK);
  tft.drawBitmap(113,0,bluetooth,15,15,BLACK);

  tft.setTextSize(2);
  tft.setTextColor(GREEN);
  tft.setCursor(20, 113);  
  tft.print("TAKIPSAN");
  tft.drawRect(15,50,100,20,BLACK);

  tft.setTextSize(1);
  tft.setTextColor(RED);
}

void loop(){
  tft.setCursor(32, 56);
  sprintf(message,"Count= %d",count);
  tft.print(message);
  delay(200);
  count++; 
  tft.fillRect(22,51,75,16,WHITE);
}



