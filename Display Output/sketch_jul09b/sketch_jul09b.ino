      #include <LiquidCrystal.h>

      LiquidCrystal lcd(12, 11, 2, 3, 4, 5);
      //                sel, en, bit1, bit2...
      
      void setup() {
        lcd.begin(16, 2);   // 16 characters x 2 rows
        lcd.clear();
        lcd.print("Te iubesc,");
        lcd.setCursor(0, 1);  // move cursor to 0 on x and 1 on y axis
        lcd.print("      Petruta !");

      }
      
      void loop() {
        // put your main code here, to run repeatedly:
        int counter = millis() / 1000;
        lcd.setCursor(13, 0);  // move cursor to 0 on x and 1 on y axis
        lcd.print(counter);
      }
