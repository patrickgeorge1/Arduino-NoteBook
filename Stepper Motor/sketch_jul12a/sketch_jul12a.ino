#include <Stepper.h>

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

/*
 * "Stride Angle 5.625° /64 " -->  1 rotation of rotor can be executed in 64 "half steps" (360 / 5.625), so in reality are 32 full steps !!
 * "Speed Variation Ratio 1/64"   -->  rotor is connected to a gear so the rotor has to rotate 64 times that the gear will rotate 1 time
 * so to rotate the "outer shft" we need a 32 rotor full steps (1 revolution of rotor) x 64 times 
 * Formula for total stepts :   360 / (2 * half stride angle) * (1 / speed variation ratio)
 *                            = 360 / (2 * 5.625) * (1 / (1/64)) == 2096 rotor steps to move 1 revolution the outer shaft
 */

#define MOTOR_STEPS 32 
#define STRIDE_ANGLE 5.625
#define SPEED_VARIATION_RATIO 1.0 / 64.0
#define STEPS_FOR_REVOLUTION (360 / (2 * STRIDE_ANGLE)) * (1.0 / (SPEED_VARIATION_RATIO))

Stepper stepper1(STEPS_FOR_REVOLUTION, IN1, IN3, IN2, IN4); 


    void setup() {
      stepper1.setSpeed(15); // max RPM value for 28BYJ-48 5v
    }

  
    void loop() {
      stepper1.step(STEPS_FOR_REVOLUTION);
      delay(1000);
      stepper1.step(- STEPS_FOR_REVOLUTION);
      delay(1000);
    }
