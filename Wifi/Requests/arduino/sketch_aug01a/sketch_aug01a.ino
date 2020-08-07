// arduino

#include <SoftwareSerial.h>
#define SEARCH_CORONA_COMMAND "a! corona check"
#define SUCCESSFUL_CONNECTION_COMMAND "e! conn success"
#define LED 7

SoftwareSerial mySerial(3, 2);  // RX, TX
boolean wifiConnected = false;

const byte numChars = 1024;
char receivedChars[numChars];

//String readSerial(boolean *StringReady) {
//  String IncomingString = "";
//  *StringReady = false;
//
//  while(mySerial.available()) {
//    IncomingString = mySerial.readString();
//    *StringReady = true;
//  }
//  return IncomingString;
//}

//void sendSerial(char *message) {
//  digitalWrite(LED_BUILTIN, HIGH);
//  mySerial.print(message);
//  delay(20);
//  digitalWrite(LED_BUILTIN, LOW);
//}

void setup() {
  pinMode(LED, OUTPUT);
  mySerial.begin(9600);
  mySerial.setTimeout(20);

  Serial.begin(9600);
}

//void displaySerial() {
//      // Read from serial
//      String message = Serial.readString();
//      Serial.println(message + "->" + strcmp(SUCCESSFUL_CONNECTION_COMMAND, message.c_str()));
//}


void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;
  
  while (mySerial.available() > 0) {
    rc = mySerial.read();
    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    } 
    else {
        receivedChars[ndx] = '\0'; // terminate the string
        ndx = 0;
      }
  }
}

void loop() {
   if (mySerial.available() > 0) {
        recvWithEndMarker();
        Serial.print(receivedChars);
   }
  
//  Serial.println("hey loop");
//  sendSerial(SEARCH_CORONA_COMMAND);
//  delay(5000);
//  
  // Read from serial
//  boolean isAnyMessage = false;
//  String message = readSerial(&isAnyMessage);
//  if(isAnyMessage) {
//        Serial.println("[ESP]: " + message); 
//  }
}
