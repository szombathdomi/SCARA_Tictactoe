#include "MotionControl.h"
#include "VacuumGripper.h"
#include "SensorReader.h"
#include "GameLogic.h"
#include "LCDDisplay.h"
#include "ButtonHandler.h"

enum MenuState {
  SELECT_PLAYER,
  SELECT_DIFFICULTY,
  WAIT_START,
  PLAYING,
  GAME_OVER
};

GameLogic game;
MenuState menuState = SELECT_PLAYER;
int startingPlayer = 0;
int difficultyLevel = 0;
bool gameStarted = false;

void setup() {
  initDisplay();
  displayWelcomeScreen();
  initButtons();
  initMotion();
  initGripper();

  while (!isHomingPressed())
    ;
  displayHomingStatus();
  home();
  displayHomingDone();
}

void loop() {
  switch (menuState) {
    case SELECT_PLAYER:
      handleSelectPlayer();
      break;

    case SELECT_DIFFICULTY:
      handleSelectDifficulty();
      break;

    case WAIT_START:
      handleWaitStart();
      break;

    case PLAYING:
      handleGameLogic();
      break;

    case GAME_OVER:
      handleGameOver();
      break;
  }
}

void handleSelectPlayer() {
  displayMenuPlayer(startingPlayer);
  if (isSelectPressed()) {
    startingPlayer = (startingPlayer + 1) % 2;
  }
  if (isOkPressed()) {
    menuState = SELECT_DIFFICULTY;
  }
}

void handleSelectDifficulty() {
  displayMenuDifficulty(difficultyLevel);
  if (isSelectPressed()) {
    difficultyLevel = (difficultyLevel + 1) % 2;
  }
  if (isOkPressed()) {
    menuState = WAIT_START;
  }
}

void handleWaitStart() {
  displayMenuWaitStart(startingPlayer, difficultyLevel);
  if (isStartPressed()) {
    randomSeed(millis());
    game.resetGame();
    gameStarted = true;
    menuState = PLAYING;

    if (startingPlayer == 0) {
      robotMove();
    }
  }
}

void handleGameLogic() {
  humanMove();
  if (checkGameEnd()) return;

  robotMove();
  checkGameEnd();
}

void handleGameOver() {
  if (isStartPressed()) {
    moveToRefill();
    displayRefill();

    while (!isOkPressed())
      ;

    returnFromRefill();
    resetToMainMenu();
  }
}

bool checkGameEnd() {
  if (game.checkWin('X')) {
    displayWinner('X');
    finishGame();
    return true;
  }
  if (game.checkWin('O')) {
    displayWinner('O');
    finishGame();
    return true;
  }
  if (game.isDraw()) {
    displayWinner('-');
    finishGame();
    return true;
  }
  return false;
}

void finishGame() {
  gameStarted = false;
  menuState = GAME_OVER;
}

void resetToMainMenu() {
  menuState = SELECT_PLAYER;
  startingPlayer = 0;
  difficultyLevel = 0;
  gameStarted = false;
  displayMenuPlayer(startingPlayer);
}

void robotMove() {
  displayRobotTurn();
  String robotCellID = (difficultyLevel == 0) ? game.makeEasyMove() : game.makeHardMove();

  if (robotCellID != "") {
    placeDisc(robotCellID);
  }
}

void humanMove() {
  bool validMove = false;
  displayPlayerTurn();

  while (!validMove) {
    while (!isOkPressed())
      ;

    String playerCellID = detectPlayerMove(game.board);

    if (playerCellID != "") {
      game.registerPlayerMove(playerCellID);
      validMove = true;
    } else {
      displayNoMoveError();
    }
  }
}