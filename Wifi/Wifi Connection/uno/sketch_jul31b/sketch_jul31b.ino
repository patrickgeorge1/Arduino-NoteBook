#include <SoftwareSerial.h>
#define LED 7

SoftwareSerial mySerial(3, 2);  // RX, TX

void setup() {
  pinMode(LED, OUTPUT);
  mySerial.begin(9600);
  Serial.begin(9600);
}

String readSerial(boolean *StringReady) {
  String IncomingString = "";
  *StringReady = false;

  while(mySerial.available()) {
    IncomingString = mySerial.readString();
    *StringReady = true;
  }
//
//  if(*StringReady) {
//    digitalWrite(LED, HIGH);
//    Serial.println("[ESP]: " + IncomingString);  
//  }
  return IncomingString;
}

void loop() {
  boolean isAnyMessage = false;
  String message = readSerial(&isAnyMessage);
  if(isAnyMessage) {
        Serial.println("[ESP]: " + message); 
  }
  
}
