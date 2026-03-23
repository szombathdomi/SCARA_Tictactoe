#include "SensorReader.h"

const int threshold = 600;

const int sensorPins[16] = {
  A0, A1, A2, A3,
  A4, A5, A6, A7,
  A8, A9, A10, A11,
  A12, A13, A14, A15
};

String boardCells[16] = {
  "A1", "A2", "A3", "A4",
  "B1", "B2", "B3", "B4",
  "C1", "C2", "C3", "C4",
  "D1", "D2", "D3", "D4"
};

String detectPlayerMove(char board[4][4]) {
  for (int i = 0; i < 16; i++) {
    int row = i / 4;
    int col = i % 4;

    if (board[row][col] == ' ') {
      int value = analogRead(sensorPins[i]);

      if (value >= threshold) {
        return boardCells[i];
      }
    }
  }
  return "";
}