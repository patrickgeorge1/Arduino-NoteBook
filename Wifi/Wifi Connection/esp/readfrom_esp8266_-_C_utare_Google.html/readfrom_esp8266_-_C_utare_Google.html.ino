// esp

void setup() {
  delay(2000);
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void sendSerial(char *message) {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.print(message);
  delay(20);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
//  SEND A MESSAGE
//  sendSerial("I am esp\n");
//  delay(3000);
}
