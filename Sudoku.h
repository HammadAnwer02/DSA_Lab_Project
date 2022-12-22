#include "graph.h"

struct Position
{
    int x;
    int y;
    Position(int xPos = 0, int yPos = 0)
    {
        x = xPos;
        y = yPos;
    }
    bool samePosition(const Position &p)
    {
        return this->x == p.x && this->y == p.y;
    }
};

class Sudoku
{
private:
    int board[9][9];
    int playBoard[9][9];

public:
    Sudoku()
    {
        for (size_t i = 0; i < 9; i++)
        {
            for (size_t j = 0; j < 9; j++)
            {
                board[i][j] = 0;
            }
        }
    }
    bool canPlace(int num, Position &p);
    bool isInRow(int num, Position &p);
    bool isInCol(int num, Position &p);
    bool isInBox(int num, Position &p);
    void generateBoard();
    void generatePlayBoard();
    void printCompleteBoard()
    {
        for (size_t i = 0; i < 9; i++)
        {
            for (size_t j = 0; j < 9; j++)
            {
            }
            cout << endl;
        }
    }

    void printBoard()
    {
        for (size_t i = 0; i < 9; i++)
        {

            for (int j = 0; j < 9; j++)
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
    void printPlayBoard()
    {
        for (size_t i = 0; i < 9; i++)
        {

            for (int j = 0; j < 9; j++)
            {
                cout << playBoard[i][j] << " ";
            }
            cout << endl;
        }
    }
};

bool Sudoku::canPlace(int num, Position &p)
{
    return !isInBox(num, p) && !isInRow(num, p) && !isInCol(num, p);
}

bool Sudoku::isInRow(int num, Position &p)
{

    for (int x = 0; x < 9; x++)
    {
        if (board[p.y][x] == num && x != p.x)
        {
            return false;
        }
    }
    return true;
}

bool Sudoku::isInCol(int num, Position &p)
{
    for (size_t y = 0; y < 9; y++)
    {
        if (board[y][p.x] == num && y != p.y)
        {
            return false;
        }
    }
    return true;
}

bool Sudoku::isInBox(int num, Position &p)
{
    int startX = p.x / 3;
    int endX = startX + 3;

    int startY = p.y / 3;
    int endY = p.y + 3;

    for (int i = startY; i < endY; i++)
    {
        for (int j = startX; j < endX; j++)
        {
            if (board[i][j] == num && i != p.y && j != p.x)
            {
                return false;
            }
        }
    }

    return true;
}

void Sudoku::generateBoard()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            Position p(j, i);
            int num;
            do
            {
                num = rand() * 9 + 1;
            } while (!canPlace(num, p));
            board[i][j] = num;
        }
    }
}

void Sudoku::generatePlayBoard()
{
    for (size_t i = 0; i < 9; i++)
    {
        int boxesCleared = 0;

        while (boxesCleared != 0)
        {
            for (int j = 0; j < 9; j++)
            {
                int clearBox = rand() * 10 + 1;
                if (clearBox > 5)
                {
                    playBoard[i][j] = 0;
                }
                else
                {
                    playBoard[i][j] = board[i][j];
                }
            }
        }
        cout << endl;
    }
}
