
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // no built in led,,,,
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, LOW);   // Turn off 
  delay(50);                       
  digitalWrite(LED_BUILTIN, HIGH);  
  delay(50);  
  digitalWrite(LED_BUILTIN, LOW); 
  delay(50);  
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(5000);                      // Wait for two seconds (to demonstrate the active low LED)
}
