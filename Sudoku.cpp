#include "Sudoku.h"

bool Sudoku::findNextCell(int &i, int &j)
{
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (board[i][j] == 0)
            {
                // unassigned cell found
                return true;
            }
        }
    }
    // no unassigned cells
    return false;
}

// checks if a value is valid for a given cell
bool Sudoku::isValid(int i, int j, int k)
{
    // check if value is present in the row, column, or 3x3 subgrid
    return row[i].count(k) == 0 && col[j].count(k) == 0 && subgrid[(i / 3) * 3 + j / 3].count(k) == 0;
}

Sudoku::Sudoku()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = 0;
        }
    }
    numEmptySlots = SIZE * SIZE;
    maxMistakes = 0;
}

// fills the Sudoku board with a valid configuration using backtracking
// fills the Sudoku board with a valid configuration using backtracking
// fills the Sudoku board with a valid configuration using backtracking
bool Sudoku::fill()
{
    // find the next unassigned cell
    int i, j;
    if (!findNextCell(i, j))
    {
        // no unassigned cells: the Sudoku board is complete
        numEmptySlots = 0;
        return true;
    }

    // create a shuffled list of values to try
    std::vector<int> values(SIZE);
    for (int k = 1; k <= SIZE; k++)
    {
        values[k - 1] = k;
    }
    std::random_device rd; // used to seed the generator
    std::mt19937 g(rd());  // create a Mersenne Twister generator
    std::shuffle(values.begin(), values.end(), g);

    // try the shuffled values for the unassigned cell
    for (int k : values)
    {
        if (isValid(i, j, k))
        {
            // value is valid: assign it to the cell and recurse
            board[i][j] = k;
            row[i].insert(k);
            col[j].insert(k);
            subgrid[(i / 3) * 3 + j / 3].insert(k);
            if (fill())
            {
                // valid configuration found
                return true;
            }
            // backtrack: unassign the cell and try the next value
            board[i][j] = 0;
            row[i].erase(k);
            col[j].erase(k);
            subgrid[(i / 3) * 3 + j / 3].erase(k);
        }
    }

    // no valid values found: backtrack
    return false;
}

bool Sudoku::gameWon()
{
    return numEmptySlots == 0;
}

bool Sudoku::gameOver()
{
    return numMistakes >= maxMistakes;
}

// clears a certain number of random spaces on the board

// clears a specified number of random cells in the Sudoku board
void Sudoku::clearRandomSpots(int numSpots)
{
    std::random_device rd;                                // used to seed the generator
    std::mt19937 g(rd());                                 // create a Mersenne Twister generator
    std::uniform_int_distribution<int> dist(0, SIZE - 1); // distribution to generate random indices

    for (int i = 0; i < numSpots; i++)
    {
        int randRow = dist(g);
        int randCol = dist(g);
        if (board[randRow][randCol] != 0)
        {
            // clear the cell
            row[randRow].erase(board[randRow][randCol]);
            col[randCol].erase(board[randRow][randCol]);
            subgrid[(randRow / 3) * 3 + randCol / 3].erase(board[randRow][randCol]);
            board[randRow][randCol] = 0;
        }
        else
        {
            // the cell is already empty: decrement the counter to try again
            i--;
        }
    }
    numEmptySlots = numSpots;
}

void Sudoku::play()
{
    while (true)
    {
        numMistakes = 0;
        this->fill();
        this->clearRandomSpots(2);
        this->setMaxMistakes(4);

        while (!gameWon() && !gameOver())
        {
            cout << "Here is the board right not: \n";
            this->print();

            int rowInput;
            int colInput;
            cout << "Enter the coordinates where you want to enter your number: ";
            cin >> rowInput >> colInput;

            while (board[rowInput][colInput] != 0)
            {
                cout << "Seems like this position is already occupied, Please try again!\n";
                cin >> rowInput >> colInput;
            }

            cout << "Enter the number you want to input here: ";
            int userInput;
            cin >> userInput;

            if (isValid(rowInput, colInput, userInput))
            {
                board[rowInput][colInput] = userInput;
                numEmptySlots--;
            }
            else
            {
                cout << "Uh Oh! Looks like you entered an incorrect input, Your mistake count is now: " << ++numMistakes << "\n";
                cout << "The max number of mistakes you can do is : " << maxMistakes << endl;
            }
        }

        if (gameOver())
        {
            cout << "Game Over! You reached the max mistake count.\n";
        }

        if (gameWon())
        {
            cout << "Game Won!\n";
        }

        cout << "Would you like to play again? (Y/N): ";
        char choice;
        cin >> choice;

        if (choice == 'N' || choice == 'n')
        {
            break;
        }
    }
}

void Sudoku::print()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}