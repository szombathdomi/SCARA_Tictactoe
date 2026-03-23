#include "VacuumGripper.h"
#include <Arduino.h>

const int GRIPPER_IN3 = 8;
const int GRIPPER_IN4 = 9;
const int DISC_FEEDER_IN1 = 10;
const int DISC_FEEDER_IN2 = 11;
const int VACUUM = 30;

void initGripper() {
  pinMode(VACUUM, OUTPUT);
  digitalWrite(VACUUM, LOW);

  pinMode(GRIPPER_IN3, OUTPUT);
  pinMode(GRIPPER_IN4, OUTPUT);

  pinMode(DISC_FEEDER_IN1, OUTPUT);
  pinMode(DISC_FEEDER_IN2, OUTPUT);
}

void pickUpDisc() {
  pushNextDisc();
  vacuumOn();
  lowerGripper();
  delay(1500);
  raiseGripper();
  delay(500);
}

void releaseDisc() {
  lowerGripper();
  delay(1300);
  vacuumOff();
  delay(500);
  raiseGripper();
  delay(200);
}

void vacuumOn() {
  digitalWrite(VACUUM, HIGH);
}

void vacuumOff() {
  digitalWrite(VACUUM, LOW);
}

void raiseGripper() {
  digitalWrite(GRIPPER_IN3, LOW);
  digitalWrite(GRIPPER_IN4, HIGH);
}

void lowerGripper() {
  digitalWrite(GRIPPER_IN3, HIGH);
  digitalWrite(GRIPPER_IN4, LOW);
}

void pushNextDisc() {
  digitalWrite(DISC_FEEDER_IN1, HIGH);
  digitalWrite(DISC_FEEDER_IN2, LOW);
  delay(2050);
  digitalWrite(DISC_FEEDER_IN1, LOW);
  digitalWrite(DISC_FEEDER_IN2, HIGH);             
}