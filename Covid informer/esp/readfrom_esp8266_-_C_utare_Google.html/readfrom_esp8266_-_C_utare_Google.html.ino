// esp

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = "Quadrant I";     
const char* password = "jesjesjes";
String lastJsonRequested;
unsigned long lastTime = -300000;


void setup() {
  delay(2000);
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.println();


  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  Serial.println();
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
    // make a new request
    if (abs(millis() - lastTime > 300000) && WiFi.status() == WL_CONNECTED) {
          HTTPClient http;
         
          http.begin("http://coronavirus-19-api.herokuapp.com/countries/romania");
          int httpCode = http.GET();

          if (httpCode > 0) {
              lastJsonRequested = String(http.getString());
          }

          http.end();
          lastTime = millis();
    }
    else {
        sendBigString(lastJsonRequested);
        delay(2500);
    }
}
