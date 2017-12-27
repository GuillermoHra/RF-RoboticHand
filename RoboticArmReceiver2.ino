//   [2]   [12]
//   [11]  [13]
//   [10]  [ 9]
//  [3.3V]|[GND]|
//Librerias por default
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define CE_PIN   9
#define CSN_PIN 10
const uint64_t pipe = 0xE8E8F0F0E1LL; 
#include <Servo.h>

Servo servo[5];
RF24 radio(CE_PIN, CSN_PIN); 
int data[5];  
int degree = 0;
//--------------------------------------------------------------------------------------
void setup(){
  Serial.begin(9600);
  delay(1000);
  Serial.println("Nrf24L01 Receiver Starting");
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  pinMode(5,OUTPUT);
  servo[0].attach(3); //pulgar
  servo[1].attach(4); //indice
  servo[2].attach(5); //medio
  servo[3].attach(6); //anular
  servo[4].attach(7); //meñique
  for (int i = 0; i < 5; i++){
        servo[i].write(0);
      } 

}
//---------------------------------------------------------------------------------------
void loop(){
  if (radio.available()){
    bool done = false; 
    while (!done){
      done = radio.read(data, sizeof(data)); // Reading good?
      //Serial.print(data[0]);
      for (int i = 0; i < 5; i++){
        Serial.print(i);
        Serial.print(" ");
        Serial.println(data[i]);
        servo[i].write(data[i]);
      } 
    } 
  }
  else{     
      Serial.println("No radio available");
  }
}
//----------------------------------------------------------------------------------------
