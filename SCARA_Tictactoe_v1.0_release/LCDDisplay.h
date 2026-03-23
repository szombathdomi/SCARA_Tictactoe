#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

void initDisplay();
void displayWelcomeScreen();
void displayHomingStatus();
void displayHomingDone();
void displayWinner(char player);
void displayRobotTurn();
void displayPlayerTurn();
void displayRefill();
void displayNoMoveError();
void displayMenuPlayer(int currentSelection);
void displayMenuDifficulty(int currentSelection);
void displayMenuWaitStart(int startingPlayer, int difficultyLevel);