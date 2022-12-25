#include <iostream>
#include <vector>
#include <algorithm>

const int SIZE = 9;

// a class to represent a Sudoku board
class SudokuBoard {
private:
    std::vector<std::vector<int>> board; // the actual Sudoku board
    std::vector<std::vector<int>> graph; // the Sudoku board represented as an adjacency list

public:
    // default constructor: creates an empty Sudoku board
    SudokuBoard() {
        board.resize(SIZE, std::vector<int>(SIZE, 0));
        graph.resize(SIZE * SIZE);
    }

    // fills the board with random numbers using a graph coloring algorithm
        // fills the board with random numbers using a graph coloring algorithm
    bool fillRandom() {
        // add edges between vertices that represent cells that cannot have the same value
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                // add an edge between cells in the same row
                for (int k = j + 1; k < SIZE; k++) {
                    graph[i * SIZE + j].push_back(i * SIZE + k);
                    graph[i * SIZE + k].push_back(i * SIZE + j);
                }
                // add an edge between cells in the same column
                for (int k = i + 1; k < SIZE; k++) {
                    graph[i * SIZE + j].push_back(k * SIZE + j);
                    graph[k * SIZE + j].push_back(i * SIZE + j);
                }
                // add an edge between cells in the same 3x3 subgrid
                int startRow = i - i % 3;
                int startCol = j - j % 3;
                for (int x = startRow; x < startRow + 3; x++) {
                    for (int y = startCol; y < startCol + 3; y++) {
                        if (x > i || (x == i && y > j)) {
                            graph[i * SIZE + j].push_back(x * SIZE + y);
                            graph[x * SIZE + y].push_back(i * SIZE + j);
                        }
                    }
                }
            }
        }

        // assign colors to the vertices using a graph coloring algorithm
        std::vector<int> colors(SIZE * SIZE, -1);
        if (!colorGraph(0, colors)) {
            return false; // no valid coloring found
        }

        // convert the colors to a Sudoku board
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = colors[i * SIZE + j] + 1;
            }
        }

        return true;
    }

    // assigns colors to the vertices using a graph coloring algorithm
    bool colorGraph(int vertex, std::vector<int> &colors) {
        if (vertex == SIZE * SIZE) {
            return true; // all vertices have been colored
        }

        // sort the neighbors of the current vertex in decreasing order of the number of available colors
        std::sort(graph[vertex].begin(), graph[vertex].end(), [&](int a, int b) {
            return graph[a].size() > graph[b].size();
        });

        // try all possible colors for the current vertex
        for (int color = 0; color < SIZE; color++) {
            if (isSafe(vertex, color, colors)) {
                colors[vertex] = color;
                if (colorGraph(vertex + 1, colors)) {
                    return true;
                }
                colors[vertex] = -1; // backtrack
            }
        }

        return false;
    }

    // checks if a color can be assigned to a vertex without violating any constraints
    bool isSafe(int vertex, int color, std::vector<int> &colors) {
        for (int i = 0; i < graph[vertex].size(); i++) {
            int neighbor = graph[vertex][i];
            if (colors[neighbor] == color) {
                return false;
            }
        }
        return true;
    }

    // prints the Sudoku board
    void print() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                std::cout << board[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    SudokuBoard board; // create an empty Sudoku board
    board.fillRandom(); // fill the board with random numbers using a graph coloring algorithm

    // print the board
    board.print();

    return 0;
}
