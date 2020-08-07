// esp

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define SEARCH_CORONA_COMMAND "a! corona check"
#define SUCCESSFUL_CONNECTION_COMMAND "e! conn success"

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

void queryAPI() {
     if (WiFi.status() == WL_CONNECTED) {
      digitalWrite(LED_BUILTIN, HIGH);
      
      HTTPClient http;
      http.begin("http://coronavirus-19-api.herokuapp.com/countries/romania"); 
      int httpCode = http.GET();

      if (httpCode > 0) {
         String payload = http.getString();
         Serial.println(payload);  
      }

      http.end();
      digitalWrite(LED_BUILTIN, LOW);
    }
}

void setup() {
  delay(3000);   // ensure that arduino is ready to listen
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.print(" ... \n");


  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(" .");
  }
  Serial.print("\n");
  Serial.println("Connection established!");  
  Serial.println(SUCCESSFUL_CONNECTION_COMMAND);
  
}

void loop() {  
  boolean isAnyMessage = false;
  String message = readSerial(&isAnyMessage);
  if(isAnyMessage) {
      if (message == SEARCH_CORONA_COMMAND) queryAPI();
  }
  delay(200);
}
