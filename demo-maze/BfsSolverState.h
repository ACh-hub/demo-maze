//
//  File:			BfsSolverState.h
//	Description:	State for looking for the shortest path (BFS algorithm)	
//  Created:		11-08-2017
//  Author:			Aleksandra Chrapkowska
//  mail:			amchrapkowska@gmail.com
//
// (c) 2017 Aleksandra Chrapkowska
// This code is licensed under MIT license (see LICENSE.txt for details)
//

#pragma once

#include<vector>
#include<queue>

#include "DemoTile.h"
#include "DemoState.h"
#include "SolvedState.h"


class BfsSolverState : public MazeState
{
private:
	DemoTile *start_tile_, *end_tile_, *current_tile_;
	std::queue<DemoTile*> bfs_queue_;
	std::vector<int> shortest_path_;
	void AddNeighbourToQueue(int index, int current_index);
	void PushSolvedState();
public:
	DemoTile * GetStartTile() { return start_tile_; }
	DemoTile * GetEndTile() { return end_tile_; }
	std::vector<int> GetShortestPath() { return shortest_path_; }
	virtual void Draw(const float timestamp);
	virtual void Update(const float timestamp);
	BfsSolverState(std::vector<DemoTile*> grid, Demo* demo, int cols);
	~BfsSolverState();
};
