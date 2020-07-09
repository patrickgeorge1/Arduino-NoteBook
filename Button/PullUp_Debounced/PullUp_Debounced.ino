      const int btn_pin = 6;
      const int btn_delay = 90;

      int btn_prev  = HIGH;
      unsigned long last_valid_change = 0;

      void setup() {
        Serial.begin(9600);
        pinMode(btn_pin, INPUT_PULLUP);   
      }
      
      void loop() {
          int btn_read = digitalRead(btn_pin);
          
          if( (btn_read != btn_prev) && (last_valid_change + btn_delay < millis()))
          {
            if (btn_read == LOW) {
              Serial.println("Pressed"); 
              // anything
            }
            btn_prev = btn_read;
            last_valid_change = millis();
          }
      }
