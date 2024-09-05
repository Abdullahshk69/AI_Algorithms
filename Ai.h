#include <raylib.h>
#include <vector>
#include <string>
#include <float.h> // FOR FLT MAX
#include <stdio.h> // FOR FLT MAX
#include "Node.h"

#ifndef AIPATH_H
#define AIPATH_H

using namespace std;


// Ai Class
class Ai
{
public:
#define ROWS 10
#define COLS 20
#define NODE_SIZE 50

    vector<vector<Node>> grid;
    Node pointA, pointB;

    void Main();
    void Start();
    void UpdateAndDraw();

    // Get the neighbours
    vector<Node*> GetNeighbours(Node* node);

    // Hotspot
    void AddHotspot(int row, int col, int radius);
    void DrawHotspot();
    void DrawWeights();
    vector<vector<int>> weight;
    int radius;
    Vector2 position;
    Color hotspotColor = BLUE;
    

    // SEARCH ALGORITHMS

    // BFS
    void BFS(Node* start, Node* goal);
    vector<Node*> bfsTracedPath;
    Color bfsColor = Color{ 200, 0, 0, 100 };

    // DFS
    void DFS(Node* start, Node* goal);
    vector<Node*> dfsTracedPath;
    Color dfsColor = Color{ 0, 200, 0, 100 };

    //Djikstra
    std::vector<Node*> djikstraTacedPath;
    Color djikstraColor = Color{ 0, 255, 0, 150 };
    void Djikstra(Node* start, Node* goal);

    //A*
    std::vector<Node*> astarTacedPath;
    Color astarColor = Color{ 0, 255, 0, 150 };
    void Astar(Node* start, Node* goal);

};

#endif