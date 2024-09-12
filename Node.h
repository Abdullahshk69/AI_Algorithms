#include <raylib.h>
#include <vector>
#include <string>
#include <float.h> // FOR FLT MAX
#include <stdio.h> // FOR FLT MAX

using namespace std;

enum class NodeState
{
    Idle,
    Blocked,
    Exploring,
    Visited,
    Goal,
    Start
};


// Standalone Node Struct
struct Node
{
    int row, col;
    Vector2 position;
    Color fillColor = RAYWHITE, outlineColor = LIGHTGRAY;

    int step = -1; // we keep this -1 for A and B and set costText Manually
    string costText = "";

    NodeState currentState = NodeState::Idle;

    // New Constructor
    Node(int row = 0, int col = 0, Vector2 position = {})
    {
        this->row = row;
        this->col = col;
        this->position = position;
    }

    void SetState(NodeState newState)
    {
        currentState = newState;
        fillColor = GetColorForState(newState);
    }

    // Draw the node on the screen
    void Draw()
    {
        DrawRectangleV(position, Vector2{50, 50}, fillColor);
        DrawRectangleLines(position.x, position.y, 50, 50, outlineColor);


        // Draw Number
        if (step != -1)
            costText = to_string(static_cast<int>(step));
        
        
        // Measure the text size to center it
        int textWidth = MeasureText(costText.c_str(), 20);
        int textHeight = 20;  // Font size is 20
        
        // Calculate the center position for the text
        Vector2 textPosition = { position.x + 25 - textWidth / 2, position.y + 25 - textHeight / 2 };

        // Draw the text in the center of the rectangle
        DrawText(costText.c_str(), textPosition.x, textPosition.y, 20, BLACK);
    }

    Color GetColorForState(NodeState state)
    {
        switch (state)
        {
            case NodeState::Idle:
                return RAYWHITE;
                break;
            case NodeState::Blocked:
                return DARKGRAY;
                break;
            case NodeState::Exploring:
                return YELLOW;
                break;
            case NodeState::Visited:
                return ORANGE;
                break;
            case NodeState::Goal:
                return GREEN;
                break;
            case NodeState::Start:
                return BLUE;
                break;
            default:
                return RAYWHITE;
        }
    }

    void DrawPath (Color color)
    {
        DrawRectangleV(position, Vector2{ 50, 50 }, color);
    }

    // A* related costs
    float gCost = FLT_MAX; // ground cost from the start node to the current node,
    float hCost = FLT_MAX; // heuristic estimated cost from the current node to the end node
    float fCost = FLT_MAX; // final total cost (gCost + hCost)

    Node* parent = nullptr;
    bool visited = false; // Add this flag to your Node structure

    void Reset ()
    {
        parent = nullptr;
        visited = false;
        
        gCost = FLT_MAX; // ground cost from the start node to the current node,
        hCost = FLT_MAX; // heuristic estimated cost from the current node to the end node
        fCost = FLT_MAX; // final total cost (gCost + hCost)
    }


    // New member function to check if this node is at the same position as another node
    bool atSameSpot(const Node& other) const
    {
        return this->row == other.row && this->col == other.col;
    }

};
