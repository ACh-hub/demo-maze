//
//  File:			DemoState.h
//  Description:	Podstawowa klasa dla stanu,
//					podstawowa klasa dla labiryntu
//  Created:		11-08-2017
//  Author:			Aleksandra Chrapkowska
//  mail:			amchrapkowska@gmail.com
//

#pragma once

#include<vector>

#include"Demo.h"
#include"DemoTile.h"
#include"DemoHud.h"
#include"DemoHelpers.h"

class Demo;
class DemoTile;



class DemoState
{
public:
	Demo* demo_;
	sf::View main_view_;
	DemoHud* hud_;
	DemoHud* GetHud() { return hud_; }
	virtual void Draw(const float timestamp) = 0;
	virtual void Update(const float timestamp) = 0;
	virtual void HandleEvents() = 0;
	DemoState();
	virtual ~DemoState();
};



class MazeState : public DemoState
{
protected:
	int maze_width_, maze_cols_;
	std::vector<DemoTile*> grid_;
	void _MakeGrid();
	void SetDone();
public:
	int GetTileIndexByPosition(int col, int row);
	bool GetDone();
	std::vector<DemoTile*> GetGrid() { return grid_; }
	virtual void Draw(const float timestamp);
	virtual void Update(const float timestamp);
	virtual void HandleEvents();
	MazeState() {};
	MazeState(Demo* demo, int cols);
	~MazeState();
};
