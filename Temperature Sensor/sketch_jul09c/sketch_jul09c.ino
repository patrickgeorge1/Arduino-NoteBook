
    void setup() {
      Serial.begin(9600);
    }
    
    void loop() {
      float sensor_value = analogRead(A0); 
      float temp = (sensor_value * 500.0) / 1023.0;
      
      Serial.println(temp);
      delay(1000);
    }
