// arduino

#include <SoftwareSerial.h>
#include<ArduinoJson.h>
#include <LiquidCrystal.h>

#define DISPLAY_MODE_NR 4
#define GREETING_MODE 0
#define TOTAL_CASES_MODE 1
#define TODAY_CASES_MODE 2
#define TODAY_DEATHS_MODE 3

SoftwareSerial mySerial(3, 2);  // RX, TX
StaticJsonDocument<450> doc;
LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

String message;
long cases = 0;
int todayCases = 0;
int todayDeaths = 0;
unsigned long lastTime = 0;
int display_mode = -1;
    
void setup() {
  lcd.begin(16, 2);    
  mySerial.begin(9600);
  mySerial.setTimeout(15);
  Serial.begin(9600);
}

void readBigJsonFromSerial() {  
        // READ
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

        // PARSE
        DeserializationError error = deserializeJson(doc, message);
        if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.c_str());
            return;
         }

        // UPDATE
        cases = doc["cases"];
        todayCases = doc["todayCases"];
        todayDeaths = doc["todayDeaths"];
}

void loop() {
        // update
        if (mySerial.available() > 0) {
              readBigJsonFromSerial();
        }
        // display
        else {
             if (abs(millis() - lastTime) > 3500) {
                  display_mode = (display_mode + 1) % DISPLAY_MODE_NR;

                  switch(display_mode) {
                      case GREETING_MODE:
                          lcd.clear();
                          lcd.print("  CO - VID 19");
                          break;
                    
                      case TOTAL_CASES_MODE:
                          lcd.clear();
                          lcd.setCursor(0, 0);
                          lcd.print("Cazuri totale:");
                          lcd.setCursor(0, 1);
                          lcd.print(cases);
                          break;

                      case TODAY_CASES_MODE:
                          lcd.clear();
                          lcd.setCursor(0, 0);
                          lcd.print("Cazuri de azi:");
                          lcd.setCursor(0, 1);
                          lcd.print(todayCases);
                          break;

                      case TODAY_DEATHS_MODE:
                          lcd.clear();
                          lcd.setCursor(0, 0);
                          lcd.print("Morti azi:");
                          lcd.setCursor(0, 1);
                          lcd.print(todayDeaths);
                          break;
                  }
                  lastTime = millis();
             }
        }  
}
