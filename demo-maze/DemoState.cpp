//
//  File:        DemoState.cpp
//  Created:     11-08-2017
//  Author:      Aleksandra Chrapkowska
//  mail:        amchrapkowska@gmail.com
//

#include "DemoState.h"
#include "DemoTile.h"
#include "ErrorState.h"

DemoState::DemoState(){}
DemoState::~DemoState(){}



void MazeState::_MakeGrid()
{
	int size = (int)maze_width_ / maze_cols_;

	grid_.clear();

	for (auto i = 0; i < maze_cols_; i++)
	{
		for (auto j = 0; j < maze_cols_; j++)
		{
			grid_.push_back(new DemoTile(sf::Vector2f(i, j), size));
		}
	}
}


int MazeState::GetTileIndexByPosition(int col, int row)
{
	bool outbound = col < 0 || row < 0 || col > maze_cols_ - 1 || row > maze_cols_ - 1;

	if (outbound) return -1;
	else return col * maze_cols_ + row;
}


void MazeState::SetDone()
{
	for (auto it = grid_.begin(); it != grid_.end(); ++it)
	{
		if(!(*it)->GetFlags()->GetDoneFlag())
			(*it)->GetFlags()->SetDoneFlag(true);
	}
}


bool MazeState::GetDone()
{
	for (auto it = grid_.begin(); it != grid_.end(); ++it)
		if (!(*it)->GetFlags()->GetDoneFlag())
			return false;

	return true;
}


inline void MazeState::Draw(const float timestamp)
{

	demo_->window_.clear(sf::Color::White);
	demo_->window_.setView(main_view_);

	for (auto it=grid_.begin(); it!=grid_.end(); ++it)
	{
		(*it)->DrawTile(&(demo_->window_), timestamp);
	}

}

void MazeState::Update(const float timestamp)
{
}

void MazeState::HandleEvents()
{
}

MazeState::MazeState(Demo* demo, int cols)
	:
	maze_cols_(cols)
{
	demo_ = demo;
	maze_width_ = demo_->demo_width_;

	// grid generation
	_MakeGrid();

	// main view
	sf::Vector2f view_size = sf::Vector2f(demo_->window_.getSize());
	main_view_.setSize(view_size);
	sf::Vector2f view_center = view_size * 0.5f;
	main_view_.setCenter(view_center);

	// 15% wysokoœci hud
	sf::Vector2f maze_hud_pos = sf::Vector2f(0, view_size.y - (int)(view_size.y * 0.15f));
	sf::Vector2f maze_hud_size = sf::Vector2f(view_size.x, (int)(view_size.y * 0.15f));

	hud_ = new DemoHud(maze_hud_pos, maze_hud_size);
}

MazeState::~MazeState(){}

