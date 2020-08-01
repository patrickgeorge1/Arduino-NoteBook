// esp

void setup() {
  delay(2000);
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void sendSerial(char *message) {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.print(message);
  delay(20);
  digitalWrite(LED_BUILTIN, LOW);
}


String readSerial(boolean *StringReady) {
  String IncomingString = "";
  *StringReady = false;

  while(Serial.available()) {
    IncomingString = Serial.readString();
    *StringReady = true;
  }
  return IncomingString;
}

void loop() {
// Send to serial
//  sendSerial("I am esp\n");
//  delay(3000);


// Read from serial
//  boolean isAnyMessage = false;
//  String message = readSerial(&isAnyMessage);
//  if(isAnyMessage) {
//      digitalWrite(LED_BUILTIN, HIGH);
//  }
}
