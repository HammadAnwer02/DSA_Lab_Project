#ifndef SUDUKOBOARD_H
#define SUDUKOBOARD_H

#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <vector>

using namespace std;
const int SIZE = 9;

class sudukoboard
{
public:
    sudukoboard();
    void setMaxMistakes(int mMistakes) {maxMistakes = mMistakes;}
        int getMaxMistakes() {return maxMistakes;}
        bool fill();
        bool gameWon();
        bool gameOver();
        void clearRandomSpots(int numSpots);
        void play();
        int board[SIZE][SIZE];
        bool isValid(int i, int j, int k);
        int numMistakes;

private:
                            // the actual Sudoku board
        unordered_set<int> row[SIZE];            // a hash table to store the values present in each row
        unordered_set<int> col[SIZE];            // a hash table to store the values present in each column
        unordered_set<int> subgrid[SIZE];        // a hash table to store the values present in each 3x3 subgrid
        vector<pair<int, int>> emptySpaces; // a list of empty spaces on the board
        int numEmptySlots;

        int maxMistakes;
        bool findNextCell(int &i, int &j);

};

#endif // SUDUKOBOARD_H
