#include "Ai.h"

vector<Node*> Ai::GetNeighbours(Node* node)
{
    vector<Node*> neighbours;

    auto isWithinGrid = [&](int row, int col) -> bool
        {
            return row >= 0 &&
                col >= 0 &&
                row < ROWS &&
                col < COLS;
        };

    // check north
    if (isWithinGrid(node->row - 1, node->col))
    {
        neighbours.push_back(&grid[node->row - 1][node->col]);
    }

    //check south
    if (isWithinGrid(node->row + 1, node->col))
    {
        neighbours.push_back(&grid[node->row + 1][node->col]);
    }

    //check east
    if (isWithinGrid(node->row, node->col - 1))
    {
        neighbours.push_back(&grid[node->row][node->col - 1]);
    }

    //check west
    if (isWithinGrid(node->row, node->col + 1))
    {
        neighbours.push_back(&grid[node->row][node->col + 1]);
    }

    return neighbours;
}
