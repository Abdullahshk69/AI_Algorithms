#include "Ai.h"
#include <queue>
#include <iostream>
#include <map>
#include <unordered_map>

void Ai::Astar(Node* start, Node* goal)
{
	astarTacedPath.clear();

	// two lambdas this time
	// one to find the ground cost
	// one for the heuristic (estimation)
	auto Heuristic = [](Node* a, Node* b) -> float
		{
			return abs(a->row - b->row) + abs(a->col - b->col);
		};

	// comparison
	auto Compare = [](Node* a, Node* b)
		{
			return a->fCost > b->fCost || (a->fCost == b->fCost && a->hCost > b->hCost);
		};

	priority_queue<Node*, vector<Node*>, decltype(Compare)> openSet(Compare);

	//unordered_map<Node*, Node*> cameFrom;	// the map of the best path to each node
	unordered_map<Node*, float> gScore;	// the map of the cheapest route from start to each node

	for (auto& row : grid)
	{
		for (auto& node : row)
		{
			gScore[&node] = INFINITY;
		}
	}

	gScore[start] = 0;

	start->hCost = Heuristic(start, goal);	// this is right at the beginning
	start->fCost = start->hCost;
	start->visited = true;
	start->step = 0;
	openSet.push(start);

	while (!openSet.empty())
	{
		Node* current = openSet.top();
		openSet.pop();
		current->visited = true;

		if (current->atSameSpot(*goal))
		{
			std::cout << "Path Found!" << endl;
			// re-construct the path. so we know how we got here
			while (current != nullptr)
			{
				astarTacedPath.push_back(current);
				current = current->parent;
			}
			reverse(astarTacedPath.begin(), astarTacedPath.end());
			return;
		}

		for (Node* neighbour : GetNeighbours(current))
		{
			/*if (neighbour->blocked || neighbour->visited)
			{
				continue;
			}*/

			float tentative_gCost = gScore[current] + 1;	// assuming uniform

			if (tentative_gCost < gScore[neighbour])
			{
				//cameFrom[neighbour] = current;
				// the best path to THIS neighbour came through the current

				gScore[neighbour] = tentative_gCost;
				neighbour->hCost = Heuristic(neighbour, goal);
				neighbour->fCost = gScore[neighbour] + neighbour->hCost;
				neighbour->visited = true;
				neighbour->step = current->step + 1;
				neighbour->parent = current;

				openSet.push(neighbour);
			}
		}
	}

	cout << "No path!" << endl;
}