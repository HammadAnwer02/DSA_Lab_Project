#include <iostream>

#include <vector>

using namespace std;

constexpr int rows = 9;
constexpr int cols = 9;

class Graph
{
public:
    void addEdge(int x, int y);
    Graph()
    {
        for (size_t i = 0; i < rows; i++)
        {
            vector<int> temp;
            for (size_t j = 0; j < cols; j++)
            {
                temp.push_back(0);
            }
            matrix.push_back(temp);
        }
    }

    void bfs();
    void dfs();


private:
    vector<vector<int>> matrix;
};

void Graph::addEdge(int x, int y)
{
    matrix[x][y] = 1;
    matrix[y][x] = 1;
}