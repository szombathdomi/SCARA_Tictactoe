#include "MotionControl.h"
#include <Arduino.h>
#include "VacuumGripper.h" 

const int STEP_L = 6;
const int DIR_L = 7;
const int ENABLE_L = 5;

const int STEP_R = 3;
const int DIR_R = 4;
const int ENABLE_R = 2;

const int LIMIT_L = 12;
const int LIMIT_R = 13;

long currentLeftSteps = 0;
long currentRightSteps = 0;

long lastLeftTarget = 0;
long lastRightTarget = 0;

const Coordinate LookUpTable[16] = {
  {"A1", -277, -806}, {"A2", -227, -717}, {"A3", -159, -650}, {"A4", -67, -598},
  {"B1", -370, -726}, {"B2", -309, -641}, {"B3", -233, -566}, {"B4", -148, -505},
  {"C1", -461, -683}, {"C2", -383, -585}, {"C3", -288, -491}, {"C4", -191, -415},
  {"D1", -568, -654}, {"D2", -465, -540}, {"D3", -331, -408}, {"D4", -211, -298}
};

void initMotion() {
  pinMode(STEP_L, OUTPUT);
  pinMode(DIR_L, OUTPUT);
  pinMode(ENABLE_L, OUTPUT);
  pinMode(STEP_R, OUTPUT);
  pinMode(DIR_R, OUTPUT);
  pinMode(ENABLE_R, OUTPUT);

  digitalWrite(ENABLE_L, LOW);
  digitalWrite(ENABLE_R, LOW);

  pinMode(LIMIT_L, INPUT_PULLUP);
  pinMode(LIMIT_R, INPUT_PULLUP);
}

void placeDisc(String cellID) {
  pickUpDisc();
  moveToCell(cellID);
  releaseDisc();
  moveMotors(-lastLeftTarget, -lastRightTarget);
}

void home() {
  digitalWrite(DIR_L, LOW);
  digitalWrite(DIR_R, LOW);

  bool rightMotorStopped = false;
  bool leftMotorStopped = false;

  int currentDelay = 10000; 
  const int TARGET_DELAY = 7000;
  const int STEP_REDUCTION = 50; 

  while (!(rightMotorStopped && leftMotorStopped)) {
    if (!rightMotorStopped) {
      if (digitalRead(LIMIT_R) == HIGH) {
        rightMotorStopped = true;
      } else {
        digitalWrite(STEP_R, HIGH);
        digitalWrite(STEP_R, LOW);
      }
    }

    if (!leftMotorStopped) {
      if (digitalRead(LIMIT_L) == HIGH) {
        leftMotorStopped = true;
      } else {
        digitalWrite(STEP_L, HIGH);
        digitalWrite(STEP_L, LOW);
      }
    }

    delayMicroseconds(currentDelay);

    if (currentDelay > TARGET_DELAY) {
      currentDelay -= STEP_REDUCTION;
      if (currentDelay < TARGET_DELAY) currentDelay = TARGET_DELAY;
    }
  }
}

void moveToCell(String cellID) {
  const int NUM_CELLS = sizeof(LookUpTable) / sizeof(LookUpTable[0]);

  for (int i = 0; i < NUM_CELLS; i++) {
    if (cellID.equals(LookUpTable[i].id)) {
      lastLeftTarget = LookUpTable[i].left;
      lastRightTarget = LookUpTable[i].right;
      moveMotors(lastLeftTarget, lastRightTarget);
      break; 
    }
  }
}

void moveMotors(long targetLeft, long targetRight) {
  bool dirLeft = targetLeft < 0 ? HIGH : LOW;
  bool dirRight = targetRight < 0 ? HIGH : LOW;

  digitalWrite(DIR_L, dirLeft);
  digitalWrite(DIR_R, dirRight);

  long totalLeft = abs(targetLeft);
  long totalRight = abs(targetRight);
  long remainingLeft = totalLeft;
  long remainingRight = totalRight;

  long maxSteps = max(totalLeft, totalRight);
  if (maxSteps == 0) return;

  const int NORMAL_DELAY = 2000;
  const int SLOW_DELAY = 5000;
  const int ACCEL_STEPS = 50;

  for (long i = 0; i < maxSteps; i++) {
    int currentDelay;
    if (i < ACCEL_STEPS) {
      currentDelay = map(i, 0, ACCEL_STEPS, SLOW_DELAY, NORMAL_DELAY);
    } else if (i >= (maxSteps - ACCEL_STEPS)) {
      currentDelay = map(i, maxSteps - ACCEL_STEPS, maxSteps, NORMAL_DELAY, SLOW_DELAY);
    } else {
      currentDelay = NORMAL_DELAY;
    }

    if (remainingLeft > 0) {
      if ((i * totalLeft / maxSteps) >= (totalLeft - remainingLeft)) {
        digitalWrite(STEP_L, HIGH);
        digitalWrite(STEP_L, LOW);
        currentLeftSteps += (dirLeft == LOW ? 1 : -1);
        remainingLeft--;
      }
    }

    if (remainingRight > 0) {
      if ((i * totalRight / maxSteps) >= (totalRight - remainingRight)) {
        digitalWrite(STEP_R, HIGH);
        digitalWrite(STEP_R, LOW);
        currentRightSteps += (dirRight == LOW ? 1 : -1);
        remainingRight--;
      }
    }

    delayMicroseconds(currentDelay);
  }
}

void moveToRefill() {
  moveMotors(0, -200);
}

void returnFromRefill() {
  moveMotors(0, 200);
}