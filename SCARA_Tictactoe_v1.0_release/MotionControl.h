#include <Arduino.h>

struct Coordinate {
  const char* id;
  long left;
  long right;
};

extern const Coordinate LookUpTable[16];

void initMotion();
void home();
void placeDisc(String cellID);
void moveToCell(String cellID);
void moveMotors(long targetLeft, long targetRight);
void moveToRefill();
void returnFromRefill();