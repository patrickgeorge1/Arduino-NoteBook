#define LED 7

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, LOW);   // Turn off 
  delay(50);                       
  digitalWrite(LED, HIGH);  
  delay(50);  
  digitalWrite(LED, LOW); 
  delay(50);  
  digitalWrite(LED, HIGH); 
  delay(5000);                      // Wait for two seconds (to demonstrate the active low LED)
}
