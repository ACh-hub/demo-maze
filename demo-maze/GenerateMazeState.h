//
//  File:			GenerateMazeState.h
//  Description:	
//  Created:		11-08-2017
//  Author:			Aleksandra Chrapkowska
//  mail:			amchrapkowska@gmail.com
//

#pragma once

#include <stack>

#include "DemoState.h"
#include "MenuState.h"

class GenerateMazeState : public MazeState
{
private:
	DemoTile* current_tile_;
	std::stack<DemoTile*> dfs_stack_;
	DemoTile* _RandomNeighbour(DemoTile* tile);
	bool maze_done_;
	void DigHole(DemoTile* tile1, DemoTile* tile2);
	void SetDone();
public:
	void PushGenerateMazeState();
	void PushBfsSolverState();
	void PushMenuState();
	virtual void Draw(const float timestamp);
	virtual void Update(const float timestamp);
	virtual void HandleEvents();
	GenerateMazeState(Demo* demo, int cols);
	~GenerateMazeState();
};

