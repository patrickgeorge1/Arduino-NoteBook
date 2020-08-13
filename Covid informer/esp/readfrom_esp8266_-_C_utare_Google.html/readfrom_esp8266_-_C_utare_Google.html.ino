// esp

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = "Quadrant I";     
const char* password = "jesjesjes";

//void sendSerial(char *message) {
//  digitalWrite(LED_BUILTIN, HIGH);
//  Serial.print(message);
//  delay(50);
//  digitalWrite(LED_BUILTIN, LOW);
//}


//String readSerial(boolean *StringReady) {
//  String IncomingString = "";
//  *StringReady = false;
//
//  while(Serial.available()) {
//    IncomingString = Serial.readString();
//    *StringReady = true;
//  }
//  return IncomingString;
//}

void setup() {
  delay(2000);
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.println();
//  Serial.print("Connecting to ");
//  Serial.print(ssid); Serial.print(" ... \n");


  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
//    Serial.print(" .");
  }
  Serial.println();
//  Serial.println();
//  Serial.println("Connection established!\n");  
//  Serial.println(WiFi.localIP());
}

// advanced serial write
void sendBigString(String message) {
      int counter = 0;
      String buffer = "";
      for (int i = 1; i <= message.length(); i++) {
          buffer += message[i - 1];
          counter ++;

          // sent 55 chars
          if (counter >= 55) {
             counter = 0;
             Serial.print(buffer);
             Serial.flush();
             buffer = "";
             delay(200);  // wait 100 ms before next transfer
          }
      }

      // send rest of message
      if (counter > 0) {
             Serial.print(buffer);
             Serial.flush();
      }
      Serial.print('\n');
      Serial.flush();
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
          HTTPClient http;
         
          http.begin("http://coronavirus-19-api.herokuapp.com/countries/romania");
          int httpCode = http.GET();

          if (httpCode > 0) {
              String payload = http.getString();
              sendBigString(payload);
//              Serial.println(payload);  
//              Serial.flush();
          }

          http.end();
    }
   delay(3600000);
}
