#include <iostream>
using namespace std;

int BOARD[10] = {0, 2, 2, 2, 2, 2, 2, 2, 2, 2}; 
int TURN = 1;

int MAKE2();
int POSSWIN(int p);
void GO(int n);
bool checkWin(int player);
bool checkDraw();

void GO(int n) {
    BOARD[n] = (TURN % 2 == 1) ? 3 : 5;
    TURN++;
}

void displayBoard();
int MAKE2() {
    if (BOARD[5] == 2)
        return 5;

    for (int i = 2; i <= 8; i += 2) {
        if (BOARD[i] == 2)
            return i;
    }

    return -1; 
}

int POSSWIN(int p) {
    // Check rows
    for (int i = 1; i <= 9; i += 3) {
        int product = BOARD[i] * BOARD[i + 1] * BOARD[i + 2];
        if (product == p * p * 2 && BOARD[i] == 2)
            return i;
        if (product == p * 2 * p && BOARD[i + 1] == 2)
            return i + 1;
        if (product == 2 * p * p && BOARD[i + 2] == 2)
            return i + 2;
    }

    // Check columns
    for (int i = 1; i <= 3; ++i) {
        int product = BOARD[i] * BOARD[i + 3] * BOARD[i + 6];
        if (product == p * p * 2 && BOARD[i] == 2)
            return i;
        if (product == p * 2 * p && BOARD[i + 3] == 2)
            return i + 3;
        if (product == 2 * p * p && BOARD[i + 6] == 2)
            return i + 6;
    }

    // Check diagonals
    int product1 = BOARD[1] * BOARD[5] * BOARD[9];
    int product2 = BOARD[3] * BOARD[5] * BOARD[7];

    if (product1 == p * p * 2 && BOARD[1] == 2)
        return 1;
    if (product1 == p * 2 * p && BOARD[5] == 2)
        return 5;
    if (product1 == 2 * p * p && BOARD[9] == 2)
        return 9;

    if (product2 == p * p * 2 && BOARD[3] == 2)
        return 3;
    if (product2 == p * 2 * p && BOARD[5] == 2)
        return 5;
    if (product2 == 2 * p * p && BOARD[7] == 2)
        return 7;

    return 0;
}

int main() {
    while (TURN <= 9) {
        displayBoard();  
        switch (TURN) {
            case 1:
                GO(1);
                break;
            case 2:
                if (BOARD[5] == 2)
                    GO(5);
                else
                    GO(1);
                break;
            case 3:
                if (BOARD[9] == 2)
                    GO(9);
                else
                    GO(3);
                break;
            case 4:
                if (POSSWIN(3) != 0)
                    GO(POSSWIN(3));
                else
                    GO(MAKE2());
                break;
            case 5:
                if (POSSWIN(3) != 0)
                    GO(POSSWIN(3));
                else if (POSSWIN(5) != 0)
                    GO(POSSWIN(5));
                else if (BOARD[7] == 2)
                    GO(7);
                else
                    GO(3);
                break;
            case 6:
                if (POSSWIN(5) != 0)
                    GO(POSSWIN(5));
                else if (POSSWIN(3) != 0)
                    GO(POSSWIN(3));
                else
                    GO(MAKE2());
                break;
            case 7:
                if (POSSWIN(3) != 0)
                    GO(POSSWIN(3));
                else if (POSSWIN(5) != 0)
                    GO(POSSWIN(5));
                else {
                    for (int i = 1; i <= 9; i += 2) {
                        if (BOARD[i] == 2) {
                            GO(i);
                            break;
                        }
                    }
                }
                break;
            case 8:
                if (POSSWIN(5) != 0)
                    GO(POSSWIN(5));
                else if (POSSWIN(3) != 0)
                    GO(POSSWIN(3));
                else {
                    for (int i = 1; i <= 9; i += 2) {
                        if (BOARD[i] == 2) {
                            GO(i);
                            break;
                        }
                    }
                }
                break;
            case 9:
                // Same as TURN 7
                if (POSSWIN(3) != 0)
                    GO(POSSWIN(3));
                else if (POSSWIN(5) != 0)
                    GO(POSSWIN(5));
                else {
                    for (int i = 1; i <= 9; i++) {
                        if (BOARD[i] == 2) {
                            GO(i);
                            break;
                        }
                    }
                }
                break;
        }

        if (checkWin(3)) {
            cout << "X wins!\n";
            break;
        } else if (checkWin(5)) {
            cout << "O wins!\n";
            break;
        } else if (TURN > 9) {
            cout << "It's a draw!\n";
        }
    }

    displayBoard();

    return 0;
}

void displayBoard() {
    cout << "Board after Turn " << TURN-1 << ":\n";
    for (int i = 1; i <= 9; i++) {
        if (i % 3 == 1)
            cout << "\n";
        cout << (BOARD[i] == 2 ? "2" : (BOARD[i] == 3 ? "X" : "O")) << " ";
    }
    cout << "\n";
}

bool checkWin(int player) {
    // Check rows
    for (int i = 1; i <= 9; i += 3) {
        if (BOARD[i] == player && BOARD[i + 1] == player && BOARD[i + 2] == player)
            return true;
    }

    // Check columns
    for (int i = 1; i <= 3; ++i) {
        if (BOARD[i] == player && BOARD[i + 3] == player && BOARD[i + 6] == player)
            return true;
    }

    // Check diagonals
    if ((BOARD[1] == player && BOARD[5] == player && BOARD[9] == player) ||
        (BOARD[3] == player && BOARD[5] == player && BOARD[7] == player))
        return true;

    return false;
}

bool checkDraw() {
    for (int i = 1; i <= 9; ++i) {
        if (BOARD[i] == 2)
            return false;
    }
    return true;
}
