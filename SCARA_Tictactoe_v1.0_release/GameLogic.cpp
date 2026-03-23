#include "GameLogic.h"

GameLogic::GameLogic() {
    resetGame();
}

void GameLogic::resetGame() {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            board[r][c] = ' ';
        }
    }
}

bool GameLogic::cellIDToIndex(String cellID, int &row, int &col) {
    if (cellID.length() != 2) return false;
    char letter = toupper(cellID.charAt(0));
    char number = cellID.charAt(1);
    row = letter - 'A';
    col = number - '1';
    return (row >= 0 && row < 4 && col >= 0 && col < 4);
}

String GameLogic::indexToCellID(int row, int col) {
    String id = "";
    id += (char)('A' + row);
    id += (char)('1' + col);
    return id;
}

bool GameLogic::isCellEmpty(int row, int col) {
    return board[row][col] == ' ';
}

bool GameLogic::isCellEmpty(String cellID) {
    int r, c;
    if (cellIDToIndex(cellID, r, c)) return isCellEmpty(r, c);
    return false;
}

void GameLogic::setCell(String cellID, char player) {
    int r, c;
    if (cellIDToIndex(cellID, r, c)) board[r][c] = player;
}

bool GameLogic::registerPlayerMove(String cellID) {
    int r, c;
    if (!cellIDToIndex(cellID, r, c)) return false;
    if (!isCellEmpty(r, c)) return false;
    board[r][c] = 'O';
    return true;
}

String GameLogic::makeEasyMove() {
    int emptyIndices[16];
    int count = 0;

    for (int i = 0; i < 16; i++) {
        if (board[i / 4][i % 4] == ' ') {
            emptyIndices[count++] = i;
        }
    }

    if (count == 0) return "";

    int randomIndex = emptyIndices[random(count)];
    String chosen = indexToCellID(randomIndex / 4, randomIndex % 4);
    setCell(chosen, 'X');

    return chosen;
}

String GameLogic::makeHardMove() {
    String winMove = findWinningMove('X');
    if (winMove != "") {
        setCell(winMove, 'X');
        return winMove;
    }

    String blockMove = findWinningMove('O');
    if (blockMove != "") {
        setCell(blockMove, 'X');
        return blockMove;
    }

    String centers[] = {"B2", "B3", "C2", "C3"};
    for (String center : centers) {
        if (isCellEmpty(center)) {
            setCell(center, 'X');
            return center;
        }
    }

    return makeEasyMove();
}

String GameLogic::findWinningMove(char player) {
    for (int row = 0; row < 4; row++) {
        int countPlayer = 0;
        int countEmpty = 0;
        int emptyCol = -1;
        for (int col = 0; col < 4; col++) {
            if (board[row][col] == player) countPlayer++;
            else if (board[row][col] == ' ') { countEmpty++; emptyCol = col; }
        }
        if (countPlayer == 3 && countEmpty == 1) return indexToCellID(row, emptyCol);
    }

    for (int col = 0; col < 4; col++) {
        int countPlayer = 0;
        int countEmpty = 0;
        int emptyRow = -1;
        for (int row = 0; row < 4; row++) {
            if (board[row][col] == player) countPlayer++;
            else if (board[row][col] == ' ') { countEmpty++; emptyRow = row; }
        }
        if (countPlayer == 3 && countEmpty == 1) return indexToCellID(emptyRow, col);
    }

    int countP = 0, countE = 0, emptyIdx = -1;
    for (int i = 0; i < 4; i++) {
        if (board[i][i] == player) countP++;
        else if (board[i][i] == ' ') { countE++; emptyIdx = i; }
    }
    if (countP == 3 && countE == 1) return indexToCellID(emptyIdx, emptyIdx);

    countP = 0; countE = 0; emptyIdx = -1;
    for (int i = 0; i < 4; i++) {
        if (board[i][3 - i] == player) countP++;
        else if (board[i][3 - i] == ' ') { countE++; emptyIdx = i; }
    }
    if (countP == 3 && countE == 1) return indexToCellID(emptyIdx, 3 - emptyIdx);

    return "";
}

bool GameLogic::checkWin(char player) {
    return checkRows(player) || checkColumns(player) || checkDiagonals(player);
}

bool GameLogic::checkRows(char player) {
    for (int r = 0; r < 4; r++) {
        if (board[r][0] == player && board[r][1] == player && 
            board[r][2] == player && board[r][3] == player) return true;
    }
    return false;
}

bool GameLogic::checkColumns(char player) {
    for (int c = 0; c < 4; c++) {
        if (board[0][c] == player && board[1][c] == player && 
            board[2][c] == player && board[3][c] == player) return true;
    }
    return false;
}

bool GameLogic::checkDiagonals(char player) {
    bool main = (board[0][0] == player && board[1][1] == player && board[2][2] == player && board[3][3] == player);
    bool anti = (board[0][3] == player && board[1][2] == player && board[2][1] == player && board[3][0] == player);
    return main || anti;
}

bool GameLogic::isDraw() {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (board[r][c] == ' ') return false;
        }
    }
    return true;
}

String GameLogic::getWinner() {
    if (checkWin('X')) return "X";
    if (checkWin('O')) return "O";
    return "";
}