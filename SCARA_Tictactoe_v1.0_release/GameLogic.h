#include <Arduino.h>

class GameLogic {
public:
  GameLogic();

  void resetGame();
  bool checkWin(char player);
  bool isDraw();
  String getWinner();

  String makeEasyMove();
  String makeHardMove();

  String findWinningMove(char player);

  bool isCellEmpty(int row, int col);
  bool isCellEmpty(String cellID);
  void setCell(String cellID, char player);

  String getCellID(int row, int col);
  bool registerPlayerMove(String cellID);
  bool getCellCoordinates(const String &cellID, int &row, int &col);

  char board[4][4];

private:
  bool cellIDToIndex(String cellID, int &row, int &col);
  String indexToCellID(int row, int col);

  bool checkRows(char player);
  bool checkColumns(char player);
  bool checkDiagonals(char player);
};