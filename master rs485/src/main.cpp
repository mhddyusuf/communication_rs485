#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>

const int ledPin = 13;  
const int EnTxPin = 8;  // HIGH: Transmitter, LOW: Receiver
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);


void transmitDataToSlave(char command, int analogPin);
void readAndDisplayData();

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(100);
  pinMode(ledPin, OUTPUT);
  pinMode(EnTxPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(EnTxPin, HIGH);
  lcd.begin(16, 2);
  lcd.print("RS485 COMMUNICATION");
  lcd.setCursor(0, 1);
  lcd.print("MASTER RS485");
  delay(100);
  lcd.clear();
}

void loop() {
  // Transmit data to slaves
  transmitDataToSlave('A', 0);  // Slave 1
  delay(50);
  transmitDataToSlave('B', 1);  // Slave 2
  delay(50);
  transmitDataToSlave('C', 2);  // Slave 3
  delay(50);

  // Read and display data from slaves
  readAndDisplayData();
}

void transmitDataToSlave(char command, int analogPin) {
  int rdata = analogRead(analogPin); 
  int ledval = map(rdata, 0, 1023, 0, 255);

  digitalWrite(EnTxPin, HIGH); 
  Serial.print("I"); 
  Serial.print(command);
  Serial.print(ledval); 
  Serial.print("F"); 
  Serial.flush();
  digitalWrite(EnTxPin, LOW); 
}

void readAndDisplayData() {
  while (Serial.available()) {
    char command = Serial.read();

    if (command == 'i' || command == 'b' || command == 'c') {
      int data = Serial.parseInt();
      if (Serial.read() == 'f') { 
        switch (command) {
          case 'i':
            lcd.setCursor(0, 0);
            lcd.print("Sl1:");    //Slave 1
            lcd.print(data);
            lcd.print("   "); 
            break;
          case 'b':
            lcd.setCursor(8, 0);
            lcd.print("Sl2:");    //Slave 2
            lcd.print(data);
            lcd.print("   "); 
            break;
          case 'c':
            lcd.setCursor(0, 8);
            lcd.print("Slave3: ");  //Slave 3
            lcd.print(data);
            lcd.print("   "); 
            break;
        }
      }
    }
  }
}
