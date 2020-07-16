  #define Ox A0
  #define Oy A1



void setup() {
   Serial.begin(9600);
   pinMode(Ox, INPUT);
   pinMode(Oy, INPUT);
}

void loop() {
   int x = 2 +  map(analogRead(Ox) / 3, 0, 341, -170, 170); // to fix joystick fizic problems
   int y = 1 +  map(analogRead(Oy) / 3, 0, 341, -170, 170);

   Serial.print(x);
   Serial.print("#");
   Serial.println(y);
   delay(50);
   
}
