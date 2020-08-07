#define RED 11
#define GREEN 10
#define BLUE 9

int red = 18;   // 45
int green = 45; // 10
int blue = 37;  // 45

void setup() {
  Serial.begin (9600);
  Serial.setTimeout(10);
}

void serialEvent() {
  
   int luminosity = Serial.readString().toInt(); 
   executeCommand(luminosity);
}

void executeCommand(int luminosity) {
   int red = map(0, 255, 20, 50, luminosity);
   int green = map(0, 255, 50, 10, luminosity);
   int blue = map(0, 255, 30, 40, luminosity);

   red = red * luminosity / 100;
   green = green * luminosity / 100;
   blue = blue * luminosity / 100;
   
   analogWrite(RED, red);
   analogWrite(GREEN, green);
   analogWrite(BLUE, blue);
   
   Serial.print(red);
   Serial.print(" ");
   Serial.print(green);
   Serial.print(" ");
   Serial.println(blue);

}

void loop() {}
