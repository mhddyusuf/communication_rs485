#include <Arduino.h>
#include<Wire.h>
 
const int EnTxPin = 2;
int ledpin=9;
int ptVal;
int ledVal;


void setup () {
  Serial.begin (9600); 
  pinMode(EnTxPin, OUTPUT );
  digitalWrite (EnTxPin, LOW );
}

void loop (){
  if ( Serial.available ()){
    if ( Serial.read () == 'I' ){
      char function = Serial.read ();
      if (function=='B' ){
        int angle = Serial.parseInt ();
        analogWrite(ledpin, angle);
        if ( Serial.read () == 'F' ){
          int val = analogRead (0);
          digitalWrite (EnTxPin, HIGH ); //enable to transmit
          Serial.print ( "b" ); 
          Serial.print (val); 
          Serial.println ( "f" ); 
          Serial.flush (); 
          digitalWrite (EnTxPin, LOW ); //enable to receive
        }
      }
    }
  }
  delay (5);
}