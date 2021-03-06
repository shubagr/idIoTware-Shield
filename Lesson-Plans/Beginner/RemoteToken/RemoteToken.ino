// sets up and initialize CGShield
#include <Adafruit_NeoPixel.h>
#include <idIoTwareShield.h>
#include <Wire.h>         // Require for I2C communication
CGShield fs;             // Instantiate CGShield instance

#include <SoftwareSerial.h>
#include "U8glib.h"
#define MYDEVICETOKEN 489 //Comment this line to enable the device to respond to all tokens
SoftwareSerial BTserial(10, 9); // RX | TX 
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);  // I2C / TWI 
char receivedData[32] = "";

int BuzzerPin = A1;

void setup() 
{
    Serial.begin(9600);
    Serial.println("Arduino is ready");
    pinMode(BuzzerPin,OUTPUT);
    // HC-05 default serial speed for commincation mode is 9600
    BTserial.begin(9600);  
}
 
void loop()
    {
       // Keep reading from HC-05 and send to Arduino Serial Monitor
      if(BTserial.available())
      {  
          int data = BTserial.readBytesUntil('\n',receivedData,32);
          receivedData[data] = '\0';
          Serial.write(receivedData);         
          displayData();//Display recieved token on OLED 
          #ifndef MYDEVICETOKEN
            int recievedToken = atoi(receivedData);
            if(recievedToken == MYDEVICETOKEN)
            {
              Serial.write("Token Identified");
              buzzer();//Turn on Buzzer and RGB LED              
            }
          #else
              buzzer();//Turn on Buzzer and RGB LED
          #endif       
            
         
          
      }
    }


void displayData()
     {
         u8g.firstPage();  
       do 
        { 
          u8g.setFont(u8g_font_timB10);
          u8g.setPrintPos(0, 10); 
          u8g.print("Token Number" );
          u8g.setFont(u8g_font_fub25);
          u8g.setPrintPos(33, 50); 
          u8g.print(receivedData);
        } while( u8g.nextPage() );
        
       
     }      
        
void buzzer() 
    {
      for(byte i=0; i<10; i++)
         {
           color(0,100,0);
           digitalWrite(BuzzerPin, HIGH);   // turn the LED on (HIGH is the voltage level)
           delay(250); 
           color(0,0,0);               // wait for a second
           digitalWrite(BuzzerPin, LOW);    // turn the LED off by making the voltage LOW
           delay(250);               // wait for a second
        }
    }    
        


