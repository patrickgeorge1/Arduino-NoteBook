// arduino

#include <SoftwareSerial.h>
#define LED 7

SoftwareSerial mySerial(3, 2);  // RX, TX
String message;

void setup() {
  pinMode(LED, OUTPUT);
  mySerial.begin(9600);
  mySerial.setTimeout(15);
  Serial.begin(9600);
}

//String readSerial(boolean *StringReady) {
//  String IncomingString = "";
//  *StringReady = false;
//  while(mySerial.available()) {
//    IncomingString = mySerial.readString();
//    *StringReady = true;
//  }
//  return IncomingString;
//}
//
//void sendSerial(char *message) {
//  digitalWrite(LED_BUILTIN, HIGH);
//  mySerial.print(message);
//  delay(20);
//  digitalWrite(LED_BUILTIN, LOW);
//}


void softwareSerialEvent() {
    digitalWrite(LED, HIGH);
    delay(20);
    digitalWrite(LED, LOW);
    
    Serial.print(message);
}


void loop() {
    // advanced serial read
    if (mySerial.available() > 0) {
        bool arrived = false;
        message = "";
        while(!arrived) {
             if (mySerial.available() > 0) {
                  char received = mySerial.read();
                  message += received;
                  if (received == '\n') {
                    arrived = true;
                    break;
                  } 
             }            
        }  
        softwareSerialEvent();
    } 
    else {
        // display data
    }
    
}
