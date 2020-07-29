//  Torque invere proportion with distance to the rotor
//2 . 5  ...... 1 cm
//5      ...... 0.5 cm
//1 . 25 ...... 2 cm


#include <Servo.h>
#include <IRremote.h>   // FFFFFFFF means that the last signal is repeated
#define IRreceiverPIN 10
#define SERVOPIN 8

#define CENTER_DEGREES 90    // the servo is centered
#define FULLY_COUNTERCLOCKWISE_DEGREES 180  // the servo is fully counterclockwise
#define FULLY_CLOCKWISE_DEGREES 0  // the servo is full clockwise
#define STEP_DEGREES 3
#define LEFT_COMMAND 0xFF22DD
#define RIGHT_COMMAND 0xFF02FD
#define REPEAT_COMMAND 0xFFFFFFFF
#define TO_LEFT -1
#define TO_RIGHT 1


IRrecv irrecv(IRreceiverPIN);
decode_results results;
Servo servo;
int pos = CENTER_DEGREES;
int lastCommand = 0;

void setup() {
  Serial.begin(9600);
  servo.attach(SERVOPIN);
  servo.write(CENTER_DEGREES);

    irrecv.enableIRIn(); // Start the receiver
}

void moveLeft() {
  pos = min(FULLY_COUNTERCLOCKWISE_DEGREES, pos + STEP_DEGREES);
  servo.write(pos);
}

void moveRight() {
   pos = max(FULLY_CLOCKWISE_DEGREES, pos - STEP_DEGREES);
   servo.write(pos);
}

void loop() {
     if (irrecv.decode(&results)) {
  
                // TO FIND the protocol that is used over IR transmission
                if (results.decode_type == NEC) {
                  Serial.print("NEC: ");
                  if (results.value == LEFT_COMMAND){ 
                    moveLeft();
                    lastCommand = TO_LEFT;
                  }
                  else if (results.value == RIGHT_COMMAND){
                    moveRight();
                    lastCommand = TO_RIGHT;
                  } else if (results.value == REPEAT_COMMAND){
                      if (lastCommand == TO_LEFT) moveLeft();
                      else moveRight();
                    }
                } 
                
          Serial.println(results.value, HEX);
          // TODO task
          
          irrecv.resume(); // Receive the next value
    }


  
//  moveLeft();
//  delay(400);

}
