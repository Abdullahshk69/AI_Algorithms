#include "Ai.h"
#include <iostream>
#include <stack>

void Ai::AddHotspot(int row, int col, int radius)
{
	Node current = grid[row][col];
	position = current.position;
	this->radius = radius;
	float weight = 4;
   
	//grid[row][col].weight = weight;

	stack<Node*> nodes;
	nodes.push(&current);
	// Affect neighbours 3 more times
	int count = 0;
	while (count < 3)
	{
		
	}
}

void Ai::DrawHotspot()
{
	DrawCircleV(position, radius, hotspotColor);
}

void Ai::DrawWeights()
{

}

int GetClamp(int value, int min, int max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return max;
}
