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

RF24 radio(CE_PIN, CSN_PIN);
int datas[2]; 
int val,valMod;
int data[20];
int temp[20];

void setup() 
{
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
}

void loop()  
{
  val=analogRead(A0);
  for(int i=0;i<20;i++){
    data[i]=analogRead(A0);
    //Serial.println(data[i]);
  }
  merge(0,19);
  //Serial.println(data[10]);
  valMod=map(data[10],0,1023,0,255);
  Serial.println(valMod);
  
  for(int i=0;i<20;i++){
    data[i]=0;
    //Serial.println(data[i]);
  }
  //Serial.println(val);
  //data[1] = 4;
  datas[0]=valMod;
  //Serial.println(valMod);
  radio.write(datas, sizeof(datas));
}

//----------------------------------------------------------------------------------
void merge(int b,int e){
   int m;
   if(b<e){
     m=(b+e)/2;
     merge(b,m);
     merge(m+1,e);
     join(b,m,e);
   }
}
//----------------------------------------------------------------------------------
void join(int ini, int medio, int fin){
  int i=ini;
  int j=medio+1;
  int k=fin;
  while(i<=medio && j<=fin){
    if(data[i]<data[j]){
       temp[k] = data[i];
       i++;}
    else{
      temp[k]=data[j];
      j++;}
    k++;
  }
    
  if(i>medio){
    for(int l=j;l<=fin;l++){
      temp[k]=data[l];
      k++;}}
  else{
    for(int u=i;u<=medio;u++){
      temp[k]=data[u];
      k++;}}
  for(int p=0;p<20;p++){
    data[p]=temp[p];}
}
  
  

