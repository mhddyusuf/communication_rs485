#include <Arduino.h>
const int ledPin =  13;  // Built-in LED
const int EnTxPin =  2;  // HIGH:Transmitter, LOW:Receiver
int slave1=1;
void setup() 
{ 
  Serial.begin(9600);
  Serial.setTimeout(100);  
  pinMode(ledPin, OUTPUT);
  pinMode(EnTxPin, OUTPUT);
  digitalWrite(ledPin, LOW); 
  digitalWrite(EnTxPin, HIGH); 
} 

void onLED(int data)
{
  if(data>500)
     digitalWrite(ledPin, HIGH); 
  else
     digitalWrite(ledPin, LOW); 
}

void loop() 
{   
  int rdata1 = analogRead(0); //data from potentiometer 
  int ledval1= map(rdata1, 0, 1023, 0, 255); 
  
  
  
  //transmitter data packet
  Serial.print("I"); //initiate data packet
  Serial.print("S"); //code for servo
  Serial.print(ledval1); //servo angle data
  Serial.print("F"); //finish data packet
  Serial.flush(); 
   digitalWrite(EnTxPin, LOW); //RS485 as receiver
  if(Serial.find('i'))
  {
      int data=Serial.parseInt(); 
      if(Serial.read()=='f') //finish reading
       {
         onLED(data);            
      }   
  }
  digitalWrite(EnTxPin, HIGH); //RS485 as transmitter
  //transmitter data packet
  int rdata2 = analogRead(1); //data from potentiometer 
  int ledval2= map(rdata2, 0, 1023, 0, 255); 
  Serial.print("I"); //initiate data packet
  Serial.print("B"); //code for servo
  Serial.print(ledval2); //servo angle data
  Serial.print("F"); //finish data packet
   Serial.flush(); 
    digitalWrite(EnTxPin, LOW); //RS485 as receiver
    Serial.parseInt(); 
    digitalWrite(EnTxPin, HIGH); //RS485 as transmitter

  //transmitter data packet
  int rdata3 = analogRead(2); //data from potentiometer 
  int ledval3= map(rdata3, 0, 1023, 0, 255); 
  Serial.print("I"); //initiate data packet
  Serial.print("C"); //code for servo
  Serial.print(ledval3); //servo angle data
  Serial.print("F"); //finish data packet
  Serial.flush(); 
    digitalWrite(EnTxPin, LOW); //RS485 as receiver
    Serial.parseInt(); 
    digitalWrite(EnTxPin, HIGH); //RS485 as transmitter

  //receiver data packet
  Serial.print("I"); //initiate data packet
  Serial.print("L"); //code for sensor
  Serial.print("F"); //finish data packet
  Serial.flush();    

  
} 

