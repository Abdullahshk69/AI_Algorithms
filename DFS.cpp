#include "Ai.h"
#include <stack>

void Ai::DFS(Node* start, Node* goal)
{
	dfsTracedPath.clear();
	
	// resetting the nodes in the grid
	for (auto& row : grid)
	{
		for (auto& node : row)
		{
			node.Reset();
		}
	}

	stack<Node*> openSet;

	openSet.push(start);	// We begin by pushing the start into it

	start->visited = true;

	while (!openSet.empty())
	{
		Node* current = openSet.top();	// get the first node of the queue
		openSet.pop();

		if (current->atSameSpot(*goal))
		{
			// reached the goal
			while (current != start)
			{
				dfsTracedPath.push_back(current);
				current = current->parent;
			}
			return;
		}

		for (Node* neighbour : GetNeighbours(current))
		{
			if (neighbour->blocked || neighbour->visited)
			{
				continue;
			}

			neighbour->parent = current;
			neighbour->visited = true;

			neighbour->step = current->step + 1;

			openSet.push(neighbour);
		}
	}

	// Path not found
	return;
}