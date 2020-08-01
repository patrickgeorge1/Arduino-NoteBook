// esp

#include <ESP8266WiFi.h>
const char* ssid     = "Quadrant I";     
const char* password = "jesjesjes";

void sendSerial(char *message) {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.print(message);
  delay(50);
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

void setup() {
  delay(2000);
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.print(" ... \n");


  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(" .");
  }
  
  Serial.println("\n Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
}

void loop() {}
