#include <Wire.h>
#include "PS2X_lib.h"
#include "QGPMaker_MotorShield.h"

#define TRIGGER_PIN  A0
#define ECHO_PIN     A1
#define SPEEDback  255
#define SPEEDfront 250

QGPMaker_MotorShield AFMS = QGPMaker_MotorShield();
PS2X ps2x;
//Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

long ARM_MIN[] = {0, 10, 40, 60};
long ARM_MAX[] = {180, 140, 170, 120};
long speedcarf=255;
long speedcarb=211;
long speedservo=3;

QGPMaker_Servo *Servo1 = AFMS.getServo(1);
QGPMaker_Servo *Servo2 = AFMS.getServo(2);// servo2是爪子

QGPMaker_DCMotor *DCMotor_1 = AFMS.getMotor(1);
QGPMaker_DCMotor *DCMotor_2 = AFMS.getMotor(2);
QGPMaker_DCMotor *DCMotor_3 = AFMS.getMotor(3);
QGPMaker_DCMotor *DCMotor_4 = AFMS.getMotor(4);


//Grab something
void openGripper() {
  Servo2->writeServo(ARM_MIN[3]);
  delay(300);
}

void closeGripper() {
  Servo2->writeServo(ARM_MAX[3]);
  delay(300);
}

void setup() {
  AFMS.begin(50);
  int error = 0;
  do {
    error = ps2x.config_gamepad(13, 11, 10, 12, true, true);
    if (error == 0) {
      break;
    } else {
      delay(100);
    }
  } while (1);
  Servo1->writeServo(140);
  Servo2->writeServo(90);

}



void loop() {
  ps2x.read_gamepad(false, 0);
  if (ps2x.Button(PSB_PAD_UP)) {
    DCMotor_1->setSpeed(speedcarf);
    DCMotor_2->setSpeed(speedcarf);
    DCMotor_3->setSpeed(speedcarb);
    DCMotor_4->setSpeed(speedcarb);
    DCMotor_1->run(FORWARD);
    DCMotor_2->run(FORWARD);
    DCMotor_3->run(FORWARD);
    DCMotor_4->run(FORWARD);
  } else if (ps2x.Button(PSB_PAD_DOWN)) {
    DCMotor_1->setSpeed(speedcarf);
    DCMotor_2->setSpeed(speedcarf);
    DCMotor_3->setSpeed(speedcarb);
    DCMotor_4->setSpeed(speedcarb);
    DCMotor_1->run(BACKWARD);
    DCMotor_2->run(BACKWARD);
    DCMotor_3->run(BACKWARD);
    DCMotor_4->run(BACKWARD);
  } else if (ps2x.Button(PSB_PAD_LEFT)) {
    DCMotor_1->setSpeed(speedcarf);
    DCMotor_2->setSpeed(speedcarf);
    DCMotor_3->setSpeed(speedcarb);
    DCMotor_4->setSpeed(speedcarb);
    DCMotor_1->run(BACKWARD);
    DCMotor_3->run(BACKWARD);
    DCMotor_2->run(FORWARD);
    DCMotor_4->run(FORWARD);
  } else if (ps2x.Button(PSB_PAD_RIGHT)) {
    DCMotor_1->setSpeed(speedcarf);
    DCMotor_2->setSpeed(speedcarf);
    DCMotor_3->setSpeed(speedcarb);
    DCMotor_4->setSpeed(speedcarb);
    DCMotor_1->run(FORWARD);
    DCMotor_3->run(FORWARD);
    DCMotor_2->run(BACKWARD);
    DCMotor_4->run(BACKWARD);
  } else {
    DCMotor_1->setSpeed(0);
    DCMotor_1->run(RELEASE);
    DCMotor_2->setSpeed(0);
    DCMotor_2->run(RELEASE);  
    DCMotor_3->setSpeed(0);
    DCMotor_3->run(RELEASE);
    DCMotor_4->setSpeed(0);
    DCMotor_4->run(RELEASE);
  }
if (ps2x.Button(PSB_TRIANGLE)) {
    DCMotor_1->setSpeed(50);
    DCMotor_2->setSpeed(50);
    DCMotor_3->setSpeed(41.46);
    DCMotor_4->setSpeed(41.46);
    DCMotor_1->run(FORWARD);
    DCMotor_2->run(FORWARD);
    DCMotor_3->run(FORWARD);
    DCMotor_4->run(FORWARD);
  }
  if (ps2x.Button(PSB_CROSS)) {
    ps2x.read_gamepad(true, 200);
    delay(300);
    ps2x.read_gamepad(false, 0);
  }
  if (ps2x.ButtonPressed(PSB_CIRCLE)) {   
    openGripper();
  }
  if (ps2x.ButtonPressed(PSB_SQUARE)) { 
    closeGripper() ;
  }
  if(ps2x.ButtonPressed(PSB_R2)){
     Servo1->writeServo((30));
  }
  if(ps2x.ButtonPressed(PSB_R1)){
     Servo1->writeServo((160));
  }
  if (ps2x.Button(PSB_L1)) {
    
      Servo1->writeServo((Servo1->readDegrees() +2*speedservo));
    
  } else if (ps2x.Button(PSB_L2)) {
    
      Servo1->writeServo((Servo1->readDegrees() - 2*speedservo));
    
  }


 
  delay(5);
}

//void obstacle(){
//  float cmMsec =ultrasonic.convert(ultrasonic.timing(), Ultrasonic::CM);
//  if(cmMsec<5){
//    DCMotor_3->setSpeed(SPEED);
//    DCMotor_3->run(FORWARD);
//    DCMotor_4->setSpeed(SPEED);
//    DCMotor_4->run(BACKWARD);
//    delay(100);
//  }else{
//    DCMotor_3->setSpeed(SPEED);
//    DCMotor_4->setSpeed(SPEED);
//    DCMotor_3->run(FORWARD);
//    DCMotor_4->run(FORWARD);
//  }
//  
//}
