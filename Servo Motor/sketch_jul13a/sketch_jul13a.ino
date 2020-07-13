#include <Servo.h>
#define SERVOPIN 9
#define CENTER_DEGREES 90    // the servo is centered
#define FULLY_COUNTERCLOCKWISE_DEGREES 180  // the servo is fully counterclockwise
#define FULLY_CLOCKWISE_DEGREES 0  // the servo is full clockwise
#define STEP_DEGREES 5

Servo servo;

void setup() {
  servo.attach(SERVOPIN);
}

void loop() {
  servo.write(CENTER_DEGREES);   // servo need the specific degrees value to move in range of [0, 180]
  delay(1000);

    servo.write(FULLY_COUNTERCLOCKWISE_DEGREES);
    delay(1000);

     servo.write(FULLY_CLOCKWISE_DEGREES);
     delay(1000);

     for(int pos = FULLY_CLOCKWISE_DEGREES; pos <= FULLY_COUNTERCLOCKWISE_DEGREES; pos += STEP_DEGREES) {
        servo.write(pos);
        delay(50);
      }
      delay(1000);
}
