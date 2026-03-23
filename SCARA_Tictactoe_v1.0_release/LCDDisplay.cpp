#include "LCDDisplay.h"

LiquidCrystal_I2C lcd(0x3F, 20, 4);

void initDisplay() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void displayWelcomeScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" SCARA TIC-TAC-TOE ");
  lcd.setCursor(7, 1);
  lcd.print("LOADING");
  lcd.setCursor(0, 2);
  for (int i = 0; i <= 19; i++) {
    lcd.setCursor(i, 2);
    lcd.write(byte(255));
    delay(100);
  }
  delay(500);
  lcd.clear();
  lcd.setCursor(2, 1);
  lcd.print("PRESS HOME BUTTON");
  lcd.setCursor(7, 2);
  lcd.print("TO HOME");
}

void displayHomingStatus() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("HOMING IN PROGRESS..");
  lcd.setCursor(0, 2);
  lcd.print("PLEASE WAIT");
}

void displayHomingDone() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("  HOMING COMPLETE  ");
  lcd.setCursor(0, 2);
  lcd.print("   SYSTEM READY    ");
  delay(2000);
  lcd.clear();
}

void displayWinner(char player) {
  lcd.clear();
  lcd.setCursor(0, 0);

  if (player == 'O') {
    lcd.setCursor(6, 1);
    lcd.print("YOU WIN!");
  } else if (player == 'X') {
    lcd.setCursor(1, 1);
    lcd.print("SCARA ROBOT WINS!");
  } else if (player == '-') {
    lcd.setCursor(7, 1);
    lcd.print("DRAW!");
  }

  lcd.setCursor(4, 2);
  lcd.print("PRESS START");
  lcd.setCursor(3, 3);
  lcd.print("TO PLAY AGAIN");
}

void displayRobotTurn() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ROBOT'S TURN!");
  lcd.setCursor(0, 1);
  lcd.print("KEEP HANDS CLEAR");
}

void displayPlayerTurn() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("YOUR TURN!");
  lcd.setCursor(0, 1);
  lcd.print("PLACE 1 DISC, THEN");
  lcd.setCursor(0, 2);
  lcd.print("PRESS THE OK BUTTON");
}

void displayRefill(){
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("REFILL DISPENSER");
  lcd.setCursor(4, 1);
  lcd.print("AND PRESS OK");
}

void displayNoMoveError() {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("NO MOVE DETECTED!");
  lcd.setCursor(2, 1);
  lcd.print("PLACE A DISC ON");
  lcd.setCursor(2, 2);
  lcd.print("THE BOARD, THEN");
  lcd.setCursor(1, 3);
  lcd.print("PRESS OK TO RETRY");
  delay(3500);
}

void displayMenuPlayer(int startingPlayer) {
  lcd.setCursor(0, 0);
  lcd.print("CHOOSE WHO STARTS:");

  lcd.setCursor(0, 1);
  if (startingPlayer == 0)
    lcd.print("-> ROBOT           ");
  else
    lcd.print("-> HUMAN           ");
  lcd.setCursor(0, 2);
  lcd.print("USE SELECT TO CHANGE");
  lcd.setCursor(0, 3);
  lcd.print("PRESS OK TO CONTINUE");
}

void displayMenuDifficulty(int difficultyLevel) {
  lcd.setCursor(0, 0);
  lcd.print("SELECT DIFFICULTY: ");

  lcd.setCursor(0, 1);
  switch (difficultyLevel) {
    case 0: lcd.print("-> EASY            "); break;
    case 1: lcd.print("-> HARD            "); break;
  }
  lcd.setCursor(0, 2);
  lcd.print("USE SELECT TO CHANGE");
  lcd.setCursor(0, 3);
  lcd.print("PRESS OK TO CONTINUE");
}

void displayMenuWaitStart(int startingPlayer, int difficultyLevel) {
  lcd.setCursor(0, 0);
  lcd.print("STARTER PLAYER:");
  if (startingPlayer == 0)
    lcd.print("ROBOT");
  else
    lcd.print("HUMAN");
  lcd.setCursor(0, 1);
  lcd.print("DIFFICULTY:");
  switch (difficultyLevel) {
    case 0: lcd.print(" EASY    "); break;
    case 1: lcd.print(" HARD    "); break;
  }
  lcd.setCursor(0, 2);
  lcd.print("PRESS START BUTTON  ");
  lcd.setCursor(0, 3);
  lcd.print("TO BEGIN GAME       ");
}