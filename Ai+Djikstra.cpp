#include "Ai.h"
#include <queue>
#include <iostream>

void Ai::Djikstra(Node* start, Node* goal)
{
	// clear the path
	djikstraTacedPath.clear();
	
	// reset everyone
	for (auto& row : grid)
	{
		for (auto& node : row)
		{
			node.Reset();
		}
	}

	auto Compare = [](Node* a, Node* b)
		{
			return a->gCost > b->gCost;	// nodes with lower gCost have higher priority
		};
	
	// we begin all of the nodes at infinity cost
	
	// What is a priority Queue
	// what are the types, what container stores them, how we compare them
	// Node, vector, Compare
	priority_queue<Node*, vector<Node*>, decltype (Compare)> openSet(Compare);
	// a list of the nodes
	// that when you call to get the top of it, it always give you the one with the highest priorty

	// we begin all of the nodes at infinity cost
	start->gCost = 0;
	start->step = 0;
	openSet.push(start);

	while (!openSet.empty())
	{
		// I have to get the current element of the open set

		Node* current = openSet.top();
		openSet.pop();

		// what do you want to do with the current now!?
		if (current->atSameSpot(*goal))	// we have reached there
		{
			std::cout << "Path Found!" << endl;
			// re-construct the path. so we know how we got here
			while (current != nullptr)
			{
				djikstraTacedPath.push_back(current);
				current = current->parent;
			}
			reverse(djikstraTacedPath.begin(), djikstraTacedPath.end());
			std::cout << "Path Size: " << djikstraTacedPath.size() << endl;
			return;
		}

		for (Node* neighbour : GetNeighbours(current))
		{
			/*if (neighbour->blocked || neighbour->visited)
			{
				continue;
			}*/

			// calculate the tentative cost
			float tentativeCost = current->gCost + 1;	// assuming a uniform cost

			if (tentativeCost < neighbour->gCost)	// this path to the neighbour is better
			{
				neighbour->gCost = tentativeCost;
				neighbour->parent = current;
				neighbour->visited = true;
				neighbour->step = current->step + 1;
				openSet.push(neighbour);
			}
		}
	}

	std::cout << "No path found!" << endl;

}