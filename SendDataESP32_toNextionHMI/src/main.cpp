#include <Arduino.h>
void sendData(String data);

int i=10;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial2.available())
  {
    String data="";
    delay(30);
    while(Serial2.available())
    {
      data+=char(Serial2.read());
    }
    sendData(data);
  }
  
}

void sendData(String data)
{
  if(data=="A")
  {
    Serial.println("Bar artiyor");
   Serial2.write("t0.txt=\"artiyor\"");
    Serial2.write(0Xff);
    Serial2.write(0Xff); 
    Serial2.write(0Xff);  
  }
  else if(data=="E")
  {
    Serial.println("Bar azaliyor");
    Serial2.write("t0.txt=\"azaliyor\"");
    Serial2.write(0Xff);
    Serial2.write(0Xff); 
    Serial2.write(0Xff);
  }
  else if(data=="00")
  {
    Serial.println("Process Bar 0'landi");
  }
}


