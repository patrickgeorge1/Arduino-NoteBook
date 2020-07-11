      const int ain_pin = A0;

      void setup() {
        Serial.begin(9600);
      }
      
      void loop() {
              int val = analogRead(ain_pin);
              float voltage = val * 5.0 /1023;
              Serial.println(voltage); 
              delay(1000);
      }
