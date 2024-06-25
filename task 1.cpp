#include <iostream>
using namespace std;

class TicTacToe {
private:
    char board[3][3];
    char currentPlayer;
    bool gameOver;

    void initializeBoard() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                board[i][j] = ' ';
            }
        }
    }

    bool checkWin(char player) {
        // Check rows and columns
        for (int i = 0; i < 3; ++i) {
            if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
                (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
                return true;
            }
        }
        // Check diagonals
        if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
            (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
            return true;
        }
        return false;
    }

    bool checkDraw() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

public:
    TicTacToe() : currentPlayer('X'), gameOver(false) {
        initializeBoard();
    }

    void printBoard() {
        cout << "Current board state:\n";
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << board[i][j];
                if (j < 2) cout << " | ";
            }
            cout << endl;
            if (i < 2) cout << "--|---|--\n";
        }
    }

    void makeMove(int row, int col) {
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
            cout << "Invalid move. Try again.\n";
            return;
        }

        board[row][col] = currentPlayer;
        if (checkWin(currentPlayer)) {
            gameOver = true;
            cout << "Player " << currentPlayer << " wins!\n";
        } else if (checkDraw()) {
            gameOver = true;
            cout << "The game is a draw!\n";
        } else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }

    bool isGameOver() const {
        return gameOver;
    }

    char getCurrentPlayer() const {
        return currentPlayer;
    }
};

int main() {
    TicTacToe game;
    int row, col;

    while (!game.isGameOver()) {
        game.printBoard();
        cout << "Player " << game.getCurrentPlayer() << "'s turn. enter row and column (0-2): ";
        cin >> row >> col;
        game.makeMove(row, col);
    }

    return 0;
}
