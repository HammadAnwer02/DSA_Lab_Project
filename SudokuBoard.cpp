#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>

const int SIZE = 9;
using namespace std;

// a class to represent a Sudoku board
class SudokuBoard
{
private:
    int board[SIZE][SIZE];                        // the actual Sudoku board
    std::vector<std::pair<int, int>> emptySpaces; // a list of empty spaces on the board
    std::vector<std::vector<int>> graph;

public:
    // default constructor: creates an empty Sudoku board
    SudokuBoard()
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                board[i][j] = 0;
                emptySpaces.push_back(std::make_pair(i, j));
            }
        }
        graph.resize(SIZE * SIZE);
    }

    void buildGraph()
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                // add an edge between cells in the same row
                for (int k = j + 1; k < SIZE; k++)
                {
                    graph[i * SIZE + j].push_back(i * SIZE + k);
                    graph[i * SIZE + k].push_back(i * SIZE + j);
                }
                // add an edge between cells in the same column
                for (int k = i + 1; k < SIZE; k++)
                {
                    graph[i * SIZE + j].push_back(k * SIZE + j);
                    graph[k * SIZE + j].push_back(i * SIZE + j);
                }
                // add an edge between cells in the same 3x3 subgrid
                int startRow = i - i % 3;
                int startCol = j - j % 3;
                for (int x = startRow; x < startRow + 3; x++)
                {
                    for (int y = startCol; y < startCol + 3; y++)
                    {
                        if (x > i || (x == i && y > j))
                        {
                            graph[i * SIZE + j].push_back(x * SIZE + y);
                            graph[x * SIZE + y].push_back(i * SIZE + j);
                        }
                    }
                }
            }
        }
    }

    bool colorGraph(int vertex, std::vector<int> &colors)
    {
        // base case: all vertices have been colored
        if (vertex == SIZE * SIZE)
        {
            return true;
        }

        // try assigning each color to the current vertex
        for (int c = 0; c < SIZE; c++)
        {
            bool valid = true;
            // check if the current color is valid for the current vertex
            for (int i = 0; i < graph[vertex].size(); i++)
            {
                if (colors[graph[vertex][i]] == c)
                {
                    valid = false;
                    break;
                }
            }
            if (valid)
            {
                // assign the current color to the current vertex and move on to the next vertex
                colors[vertex] = c;
                if (colorGraph(vertex + 1, colors))
                {
                    return true;
                }
            }
        }
        // no valid coloring found for the current vertex
        colors[vertex] = -1;
        return false;
    }
    // // fills the board with random numbers
    void fillRandom()
    {
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(1, SIZE);
        fillRandom(0, 0, dist, rng);
    }

    // recursive function to fill the board with a valid Sudoku configuration using a backtracking algorithm
    bool fillRandom(int row, int col, std::uniform_int_distribution<int> &dist, std::mt19937 &rng)
    {
        // base case: all cells have been filled
        if (row == SIZE)
        {
            return true;
        }

        // move to the next row if we have reached the end of the current row
        if (col == SIZE)
        {
            return fillRandom(row + 1, 0, dist, rng);
        }

        // skip cells that are already filled
        if (board[row][col] != 0)
        {
            return fillRandom(row, col + 1, dist, rng);
        }

        // try filling the current cell with a random valid value
        for (int i = 0; i < SIZE; i++)
        {
            int value = dist(rng);
            if (isSafe(row, col, value))
            {
                board[row][col] = value;
                if (fillRandom(row, col + 1, dist, rng))
                {
                    return true;
                }
            }
        }

        // no valid value found for the current cell, backtrack
        board[row][col] = 0;
        return false;
    }
    // finds the first empty space on the board
    bool findEmptySpace(int &row, int &col)
    {
        for (row = 0; row < SIZE; row++)
        {
            for (col = 0; col < SIZE; col++)
            {
                if (board[row][col] == 0)
                {
                    return true;
                }
            }
        }
        return false;
    }

    // clears a certain number of random spaces on the board
    void clearRandomSpaces(int numSpaces)
    {
        for (int i = 0; i < numSpaces; i++)
        {
            int index = rand() % emptySpaces.size();
            std::pair<int, int> space = emptySpaces[index];
            board[space.first][space.second] = 0;
            emptySpaces.erase(emptySpaces.begin() + index);
        }
    }

    // checks if a number can be placed at a given position on the board
    bool isSafe(int row, int col, int num)
    {
        // check if the number is already in the row
        for (int i = 0; i < SIZE; i++)
        {
            if (board[row][i] == num)
            {
                return false;
            }
        }

        // check if the number is already in the column
        for (int i = 0; i < SIZE; i++)
        {
            if (board[i][col] == num)
            {
                return false;
            }
        }

        // check if the number is already in the 3x3 subgrid
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = startRow; i < startRow + 3; i++)
        {
            for (int j = startCol; j < startCol + 3; j++)
            {
                if (board[i][j] == num)
                {
                    return false;
                }
            }
        }

        return true;
    }

    // prints the Sudoku board
    void print()
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                cout << board[i][j] << ' ';
            }
            cout << endl;
        }
    }
    bool checkEmptySpaces()
    {
        for (int i = 0; i < SIZE * SIZE; i++)
        {
            if (board[i / SIZE][i % SIZE] == 0)
            {
                std::vector<bool> usedValues(SIZE, false);
                for (int j : graph[i])
                {
                    usedValues[board[j / SIZE][j % SIZE] - 1] = true;
                }
                for (int j = 0; j < SIZE; j++)
                {
                    if (!usedValues[j])
                    {
                        board[i / SIZE][i % SIZE] = j + 1;
                        break;
                    }
                }
                if (board[i / SIZE][i % SIZE] == 0)
                {
                    return false;
                }
            }
        }
        return true;
    }
   
    
                
};

int main()
{
    srand(time(0)); // seed the random number generator

    SudokuBoard board;  // create an empty Sudoku board
    board.fillRandom(); // fill the board with random numbers

    std::cout << "Filled board:" << std::endl;
    board.print(); // print the filled board

    board.clearRandomSpaces(20); // clear 40 random spaces on the board

    std::cout << std::endl
              << "Empty board:" << std::endl;
    board.print(); // print the empty board

    // board.solve();

    std::cout << std::endl
              << "After solving:" << std::endl;
    board.checkEmptySpaces();
    board.print();

    return 0;
}
