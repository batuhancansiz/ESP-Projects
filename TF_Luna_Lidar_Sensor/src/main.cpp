#include <Arduino.h>
#include "string.h"
 
char message[20];
int distance;   //actual distance measurements of LiDAR
int strength;   //signal strength of LiDAR
int temperature;    //temperature of LiDAR
int CheckSum;  
int i = 0;
int received_data[9];    //datas measured by LiDAR
const int HEADER=0x59;  //frame header of data package
 
void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
}
 
void loop() { 
    if (Serial2.available()) {  
        if(i>0)
        {
            received_data[i] = Serial2.read();
            i++;
            if (i > 8)
            {
              CheckSum=received_data[0]+received_data[1]+received_data[2]+received_data[3]+received_data[4]+received_data[5]+received_data[6]+received_data[7];
                if (received_data[8] == (CheckSum & 0xff)){ //verify the received data as per protocol CheckSum
                    distance = received_data[2] | received_data[3] <<8;     //calculate distance value
                    sprintf(message,"Distance: %dcm  /  ",distance);
                    Serial.print(message);

                    strength = received_data[4] | received_data[5] <<8; //calculate signal strength value
                    sprintf(message,"Strength: %d  /  ",strength);
                    Serial.print(message);

                    temperature = received_data[6] | received_data[7] << 8; //calculate the temperature value
                    temperature = temperature / 8 - 256;                     
                    sprintf(message,"Temperature: %d℃",temperature);
                    Serial.print(message);
                    Serial.println("");
                } 
                 i = 0;          
            }       
        }
        else if(Serial2.read() == HEADER) {
            received_data[i] = HEADER;
            i++;
            }
        else{
          i=0;
        }
        }
}