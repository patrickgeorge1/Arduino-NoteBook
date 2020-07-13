#define VOLTAGE_DIVIDER A0  // voltage across photoresitor
#define LED 7   // a led
#define TRESHOLD 25

void setup() {
    pinMode(VOLTAGE_DIVIDER, INPUT);
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
}

void loop() {
  float voltage = 100 - map(analogRead(VOLTAGE_DIVIDER), 0, 700, 0, 100);  // get a high pulse when light gets darker
  if (voltage > TRESHOLD) digitalWrite(LED, HIGH);   // over a treshold turn the led on
  else digitalWrite(LED, LOW);
  Serial.println(voltage);    // for serial plotter
  delay(50);  
}
