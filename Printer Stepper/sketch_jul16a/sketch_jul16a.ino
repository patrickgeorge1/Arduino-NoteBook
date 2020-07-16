#include <Stepper.h>

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define calibration_switch 4

#define MOTOR_STEPS 96 
#define STRIDE_ANGLE 1.875
#define SPEED_VARIATION_RATIO 1.0 / 64.0
#define STEPS_FOR_REVOLUTION 96
#define TOTAL_TRAJECTORY_STEPS 1100

int position = 0;

Stepper stepper1(MOTOR_STEPS, IN1, IN3, IN2, IN4); 

    void calibrate() {
        stepper1.setSpeed(100); 
        int i = 0;
        while(digitalRead(calibration_switch) == LOW) {
            stepper1.step(1);
            i += 1;
        }

        stepper1.setSpeed(250); // recommanded max rpm  300 for 103-550-0146 SANYO-DENKI
        stepper1.step(-TOTAL_TRAJECTORY_STEPS);
    }

    void move(int x) {
      if (x < 0) x = 0;
      else if (x > TOTAL_TRAJECTORY_STEPS) x = TOTAL_TRAJECTORY_STEPS;
      
      stepper1.step(x - position);
      position = x;
    }
    
    void setup() {
      Serial.begin(9600);
      pinMode(calibration_switch, INPUT);
      calibrate();  // move to initial position
    }

  
    void loop() {
        // can move in interval [0, 1100]
        move(100);
        delay(500);
        move(0);
        delay(500);
    }
