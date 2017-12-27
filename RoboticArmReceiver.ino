//   [2]   [12]
//   [11]  [13]
//   [10]  [ 9]
//  [3.3V]|[GND]|

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define CE_PIN   9
#define CSN_PIN 10
const uint64_t pipe = 0xE8E8F0F0E1LL; 
#include <Servo.h>

Servo servo1;
RF24 radio(CE_PIN, CSN_PIN); 
int data[2];  
int pos=0;
int degree=0;

void setup()  
{
  Serial.begin(9600);
  delay(1000);
  Serial.println("Nrf24L01 Receiver Starting");
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  pinMode(5,OUTPUT);
  servo1.attach(7);
}

void loop()  
{
  if ( radio.available() )
  {
    bool done = false;
    while (!done)
    {
      done = radio.read(data, sizeof(data));
      Serial.print(data[0]);
      if(pos>data[0]){
        degree+=5;
        pos=data[0];
      }
      else if(pos<data[0]){
        degree-=5;
        pos=data[0];
      }
      if(degree<180 && degree>0){
        servo1.write(degree);
        delay(10);
      }
      //Serial.println(data[1]);
    }
  }
  else
  {    
      Serial.println("No radio available");
  }
}
