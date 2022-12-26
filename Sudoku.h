#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <random>

constexpr int SIZE = 9;

using namespace std;

class Sudoku
{
private:
    int board[SIZE][SIZE];                        // the actual Sudoku board
    unordered_set<int> row[SIZE];            // a hash table to store the values present in each row
    unordered_set<int> col[SIZE];            // a hash table to store the values present in each column
    unordered_set<int> subgrid[SIZE];        // a hash table to store the values present in each 3x3 subgrid
    vector<pair<int, int>> emptySpaces; // a list of empty spaces on the board
    int numEmptySlots;
    int numMistakes;
    int maxMistakes;
    bool findNextCell(int &i, int &j);
    bool isValid(int i, int j, int k);
    
public:
    // constructor: creates an empty Sudoku board
    Sudoku();
    void setMaxMistakes(int mMistakes) {maxMistakes = mMistakes;}
    int getMaxMistakes() {return maxMistakes;}
    bool fill();
    bool gameWon();
    bool gameOver();
    void clearRandomSpots(int numSpots);
    void play();
    void print();
};
