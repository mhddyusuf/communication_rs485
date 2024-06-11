#include<Arduino.h>
#include<Wire.h>
#include <LiquidCrystal.h>          //Include LCD library for using LCD display functions 

const int EnTxPin = 8;
int ledpin=9;
int ptVal;
int ledVal;


LiquidCrystal lcd(2,3,4,5,6,7); 

void setup () {
  Serial.begin (9600); 
  pinMode(EnTxPin, OUTPUT );
  digitalWrite (EnTxPin, LOW );
  lcd.begin(16,2);
  lcd.print("RS485 COMMUNICATION");
  lcd.setCursor(0,1);
  lcd.print("SLAVE-1 RS485");
  delay(100);
  lcd.clear();
  
}

void loop (){
  if ( Serial.available ()){
    if ( Serial.read () == 'I' ){
      char function = Serial.read ();
      if (function=='A' ){
        int ledval = Serial.parseInt ();
        if ( Serial.read () == 'F' ){
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("PWM MASTER");
            lcd.setCursor(12,0);
            lcd.print(ledval); 
            
            analogWrite(ledpin, ledval);
            int val = analogRead (0);
            int ledval= map(val, 0, 1023, 0, 255);
            
            digitalWrite (EnTxPin, HIGH ); //enable to transmit
            Serial.print ( "i" ); 
            Serial.print (ledval); 
            Serial.print ( "f" ); 
            Serial.flush (); 
            digitalWrite (EnTxPin, LOW ); //enable to receive
        }
      }
    }
  }
  delay (10);
}