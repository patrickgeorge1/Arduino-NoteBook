#include <IRremote.h>
#define LG_POWER_BUTTON_CODE 0x20DF10EF
#define LG_REPEAT_CODE 0xFFFFFFFF


IRsend irsend;  // library use pin 3 to send (UNO), be carefull at timers !

void setup() {
  Serial.begin(9600);
  delay(1000);
}

void loop() {
    irsend.sendNEC(LG_POWER_BUTTON_CODE, 32);
    Serial.println("Sent shutdown");
    
    delay(3000);
}
