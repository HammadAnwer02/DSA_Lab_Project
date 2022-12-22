#include "Sudoku.h"

int main() {
    Sudoku s;
    s.generateBoard();
    s.printBoard();
    cout << endl;
    cout << endl;
    s.generatePlayBoard();
    s.printPlayBoard();
}