#include <Arduino.h>
#include <U8g2lib.h>
#include "max6675.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define leftbutton 4
#define midbutton 16
#define rightbutton 17
char message[30];
int value=0;
int sayfa=1;
int thermoDO = 19;
int thermoCS = 5;
int thermoCLK = 18;
int choosenvalue=0;
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 22, /* data=*/ 21);
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void settings(void)
{
if(digitalRead(leftbutton)==HIGH)  
  {
    while(digitalRead(leftbutton)==HIGH);
    value-=10;
  }
  if(digitalRead(rightbutton)==HIGH)
  {
    while(digitalRead(rightbutton)==HIGH);
    value+=10;
  }
  u8g2.clearBuffer(); 
  u8g2.setFont(u8g2_font_timB14_tf); 
  sprintf(message,"%d",value);
   u8g2.drawStr(15,17,message);
   u8g2.setFont(u8g2_font_ncenR24_te);  
  u8g2.sendBuffer(); 
}
void screen(void)
{
 u8g2.clearBuffer(); 
    u8g2.setFont(u8g2_font_timB12_tf); 
    sprintf(message,"C = %.2f  (%d)", thermocouple.readCelsius(),choosenvalue);
    Serial.println(message);
       u8g2.setFont(u8g2_font_ncenR24_te);
    u8g2.drawStr(5,17,message);
    Serial.println(message);
    u8g2.sendBuffer();
    delay(400);
}
void relaycontrol(void)
{
  if(thermocouple.readCelsius()< choosenvalue)
   {
     digitalWrite(15,LOW);
   }
   else{
     digitalWrite(15,HIGH);
   }
}

void setup() {
  Serial.begin(9600);
  pinMode(midbutton,INPUT);
  pinMode(leftbutton,INPUT);
  pinMode(rightbutton,INPUT);
  pinMode(15,OUTPUT);
  u8g2.begin(); 
}

void loop() {

 if(digitalRead(midbutton)==HIGH)
  {
    while(digitalRead(midbutton)==HIGH);
    if(sayfa==1)
    {
    sayfa=2;
    Serial.println(sayfa);
    }
    else if(sayfa==2)
    {
    sayfa=1;
    Serial.println(sayfa);
    }
  }

  if(sayfa==2)
  {settings();}
  
  else if(sayfa==1)
  {
    choosenvalue=value;
    screen();
    relaycontrol();
  }
}