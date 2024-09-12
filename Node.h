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

	NodeState currentState = NodeState::Idle;

	// New Constructor
	Node(int row = 0, int col = 0, Vector2 position = {})
	{
		this->row = row;
		this->col = col;
		this->position = position;
	}

	void SetState(NodeState newState, float gCost = FLT_MAX, bool transition = false)
	{
		if (isTransitioning)
			return;

		if (transition)
		{
			isTransitioning = true;
			trainsitionTime = 0.0f;
			nextState = newState;
			targetColor = GetColorForState(newState);
		}

		else
		{
			currentState = newState;
			this->gCost = gCost;
			fillColor = GetColorForState(newState);
		}
	}

	// Draw the node on the screen
	void Draw()
	{
		DrawRectangleV(position, Vector2{ 50, 50 }, fillColor);
		DrawRectangleLines(position.x, position.y, 50, 50, outlineColor);

		if (isTransitioning)
		{
			DoTransition();
		}

		string costText = "";

		// Draw Number
		if (gCost < 10000)
			costText = to_string(static_cast<int>(gCost));


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

	void DoTransition()
	{
		trainsitionTime += GetFrameTime();

		float totalTime = 1.0f;
		float t = trainsitionTime / totalTime;

		if (t >= 1.0f)
		{
			isTransitioning = false;
			SetState(nextState);
		}
		else
		{
			fillColor = { 
				(unsigned char)lerp((float)fillColor.r, (float)targetColor.r, t),
				(unsigned char)lerp((float)fillColor.g, (float)targetColor.g, t),
				(unsigned char)lerp((float)fillColor.b, (float)targetColor.b, t),
				(unsigned char)lerp((float)fillColor.a, (float)targetColor.a, t) 
			};

			//fillColor = LerpColor(fillColor, targetColor, t);
		}
	}

	float lerp(float a, float b, float t)
	{
		return a + (b - a) * t;
	}

	Color LerpColor(Color start, Color end, float t)
	{
		return Color{
			(unsigned char)(start.r + t * (end.r - start.r)),
			(unsigned char)(start.g + t * (end.g - start.g)),
			(unsigned char)(start.b + t * (end.b - start.b)),
			(unsigned char)(start.a + t * (end.a - start.a))
		};
	}

	void DrawPath(Color color)
	{
		DrawRectangleV(position, Vector2{ 50, 50 }, color);
	}

	// A* related costs
	float gCost = FLT_MAX; // ground cost from the start node to the current node,
	float hCost = FLT_MAX; // heuristic estimated cost from the current node to the end node
	float fCost = FLT_MAX; // final total cost (gCost + hCost)

	Node* parent = nullptr;
	bool visited = false; // Add this flag to your Node structure

	void Reset()
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

	float trainsitionTime = 0.0f;	// time elapsed from the current transition
	bool isTransitioning = false;
	NodeState nextState;
	Color targetColor;

};
