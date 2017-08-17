//
//  File:        SolvedState.h
//  Description: State displaying pacman
//  Created:     14-08-2017
//  Author:      Aleksandra Chrapkowska
//  mail:        amchrapkowska@gmail.com
//
// (c) 2017 Aleksandra Chrapkowska
// This code is licensed under MIT license (see LICENSE.txt for details)
//

#pragma once

#include "DemoState.h"
#include "Entity.h"
#include "BfsSolverState.h"
#include "DemoAnimation.h"

class SolvedState : public MazeState
{
private:
	DemoTile *start_tile_, *end_tile_, *current_tile_;
	std::vector<int> shortest_path_;
	std::vector<Dot*> path_dots_;
	Pac* pac_man_;

public:
	std::vector<int>GetShortestPath() { return shortest_path_; }
	std::string GetPassageDirection(DemoTile* tile_from, DemoTile* tile_to);
	DemoTile* GetTileByIndex(int index);
	virtual void Draw(const float timestamp);
	virtual void Update(const float timestamp);
	virtual void HandleEvents();
	void PushBfsSolverState();
	void PushGenerateMazeState();
	void PushMenuState();
	void PushErrorState();
	SolvedState(std::vector<DemoTile*> grid, std::vector<int> shortest_path, 
				DemoTile * start, DemoTile * end, Demo* demo, int cols);
	~SolvedState();
};

