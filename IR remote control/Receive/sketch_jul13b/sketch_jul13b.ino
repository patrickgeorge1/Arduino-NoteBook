#include <IRremote.h>   // FFFFFFFF means that the last signal is repeated
#define IRreceiverPIN 7

IRrecv irrecv(IRreceiverPIN);
decode_results results;

unsigned long last_time_pressed = 0;


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}


void loop() {
    if ((last_time_pressed + DEBOUNCE_DELAY < millis()) && irrecv.decode(&results)) {
  
                // TO FIND the protocol that is used over IR transmission
                if (results.decode_type == NEC) {
                  Serial.print("NEC: ");
                } else
                if (results.decode_type == SONY) {
                  Serial.print("SONY: ");
                } else
                if (results.decode_type == RC5) {
                  Serial.print("RC5: ");
                } else
                if (results.decode_type == RC6) {
                  Serial.print("RC6: ");
                } else
                if (results.decode_type == UNKNOWN) {
                  Serial.print("UNKNOWN: ");
                }
                
          Serial.println(results.value, HEX);
          // TODO task
          
          irrecv.resume(); // Receive the next value
    }
}
