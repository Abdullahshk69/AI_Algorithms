#include "Ai.h"
#include <vector>
#include <iostream>

using namespace std;

Node* Ai::GetRandomNode()
{
	int randRow = GetRandomValue(0, (int)(grid.size()) - 1);
	int randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);
	
	while (grid[randRow][randCol].currentState == NodeState::Blocked ||
		(grid[randRow][randCol].currentState == NodeState::Start ||
			(grid[randRow][randCol].currentState == NodeState::Goal)))
	{
		randRow = GetRandomValue(0, (int)(grid.size()) - 1);
		randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);
	}

	return &grid[randRow][randCol];
}

Node* Ai::GetGoalNode()
{
	for (int i = 0; i < (int)(grid.size()); i++)
	{
		for (int j = 0; j < (int)(grid[i].size()); j++)
		{
			if (grid[i][j].currentState == NodeState::Goal)
				return &grid[i][j];
		}
	}

	return nullptr;
}

void Ai::Main()
{
	InitWindow(1000, 500, "FSM");

	Start();

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		UpdateAndDraw();

		EndDrawing();
	}

	CloseWindow();
}

void Ai::Start()
{
	// re-create the nodes
	grid.clear();
	for (int row = 0; row < ROWS; row++)
	{
		float y = NODE_SIZE * row;
		vector<Node> rowNodes;
		for (int col = 0; col < COLS; col++)
		{
			float x = NODE_SIZE * col;
			Node node = { row, col, Vector2{x, y} };
			node.SetState(NodeState::Idle);
			rowNodes.push_back(node);
		}
		grid.push_back(rowNodes);
	}

	// take some (e.g., 5, 10, or 20) from sqaures randomly and put in blockd ones
	for (int i = 0; i < 20; i++)
	{
		GetRandomNode()->SetState(NodeState::Blocked);
	}

	GetRandomNode()->SetState(NodeState::Start, 0.0f);
	GetRandomNode()->SetState(NodeState::Goal, 9.0f);
}

void Ai::UpdateAndDraw()
{
	for (int i = 0; i < (int)(grid.size()); i++)
		for (int j = 0; j < (int)(grid[i].size()); j++)
			grid[i][j].Draw();

	// Check if the "R" key is pressed
	if (IsKeyPressed(KEY_R)) { Start(); } // RESTART
	
	// if "B" key is pressed, switch the goal
	if (IsKeyPressed(KEY_B) && GetGoalNode() != nullptr)	// O(1)
	{ 
		GetGoalNode()->SetState(NodeState::Idle, true);
		GetRandomNode()->SetState(NodeState::Goal, 9.0f, true);
	}
}