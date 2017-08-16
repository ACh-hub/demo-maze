//
//  File:        GenerateMazeState.cpp
//  Created:     11-08-2017
//  Author:      Aleksandra Chrapkowska
//  mail:        amchrapkowska@gmail.com
//

#include "GenerateMazeState.h"
#include "DemoState.h"
#include "DemoHelpers.h"
#include "DemoTile.h"
#include "BfsSolverState.h"




DemoTile * GenerateMazeState::_RandomNeighbour(DemoTile * tile)
{
	unsigned int index;
	std::vector<DemoTile*> neighbours;

	index = GetTileIndexByPosition(tile->GetX(), tile->GetY() - 1);
	if (index < grid_.size() && index >= 0)
		if (!grid_[index]->GetFlags()->GetIsVisitedFlag())
			neighbours.push_back(grid_[index]);

	index = GetTileIndexByPosition(tile->GetX() + 1, tile->GetY());
	if (index < grid_.size() && index >= 0)
		if (!grid_[index]->GetFlags()->GetIsVisitedFlag())
			neighbours.push_back(grid_[index]);

	index = GetTileIndexByPosition(tile->GetX(), tile->GetY() + 1);
	if (index < grid_.size() && index >= 0)
		if (!grid_[index]->GetFlags()->GetIsVisitedFlag())
			neighbours.push_back(grid_[index]);

	index = GetTileIndexByPosition(tile->GetX() - 1, tile->GetY());
	if (index < grid_.size() && index >= 0)
		if (!grid_[index]->GetFlags()->GetIsVisitedFlag())
			neighbours.push_back(grid_[index]);

	if (neighbours.size() > 0)
		return neighbours[RandomInt(0, neighbours.size() - 1)];
	else
		return nullptr;
}



void GenerateMazeState::DigHole(DemoTile * tile1, DemoTile * tile2)
{
	if (tile1->GetY() == tile2->GetY() + 1)
	{
		tile1->GetWalls()->SetNWall(false);
		tile2->GetWalls()->SetSWall(false);
	}
	else if (tile1->GetX() == tile2->GetX() - 1)
	{
		tile1->GetWalls()->SetEWall(false);
		tile2->GetWalls()->SetWWall(false);
	}
	else if (tile1->GetY() == tile2->GetY() - 1)
	{
		tile1->GetWalls()->SetSWall(false);
		tile2->GetWalls()->SetNWall(false);
	}
	else if (tile1->GetX() == tile2->GetX() + 1)
	{
		tile1->GetWalls()->SetWWall(false);
		tile2->GetWalls()->SetEWall(false);
	}
}



void GenerateMazeState::SetDone()
{
	if (!maze_done_)
	{
		maze_done_ = true;
		GetHud()->ClearHudMsgs();
		GetHud()->InsertHudMsg(L"SPACE  rozwi¹zanie", sf::Vector2f(10, 10));
		GetHud()->InsertHudMsg(L"F1  nowy labirynt", sf::Vector2f(10, 35));
		GetHud()->InsertHudMsg(L"Esc  menu", sf::Vector2f(10, 60));

		MazeState::SetDone();
	}
}



void GenerateMazeState::PushGenerateMazeState()
{
	demo_->PushState(new GenerateMazeState(demo_, maze_cols_));
}



void GenerateMazeState::PushBfsSolverState()
{
	demo_->PushState(new BfsSolverState(GetGrid(), demo_, maze_cols_));
}

void GenerateMazeState::PushMenuState()
{
	demo_->PushState(new MenuState(demo_));
}



void GenerateMazeState::Draw(const float timestamp)
{
	// Display colors and priority
	for (auto it = grid_.begin(); it != grid_.end(); ++it)
	{
		if ((*it)->GetFlags()->GetDoneFlag())
			(*it)->SetTileColor((*it)->GetFlags()->done_color_);
		else if ((*it)->GetFlags()->GetOnStackFlag())
			(*it)->SetTileColor((*it)->GetFlags()->on_stack_color_);
		else if ((*it)->GetFlags()->GetIsVisitedFlag())
			(*it)->SetTileColor((*it)->GetFlags()->is_visited_color);
	}
	MazeState::Draw(timestamp);
	hud_->DrawHud(&(demo_->window_), timestamp);
}



void GenerateMazeState::Update(const float timestamp)
{
	// here be dragons and dfs
	current_tile_->GetFlags()->SetIsVisitedFlag(true);
	current_tile_->GetFlags()->SetOnStackFlag(true);

	DemoTile* next = _RandomNeighbour(current_tile_);
	if (next != nullptr)
	{
		DigHole(current_tile_, next);
		current_tile_ = next;
		dfs_stack_.push(current_tile_);
	}
	else
	{
		if (dfs_stack_.size() > 1)
		{
			dfs_stack_.top()->GetFlags()->SetOnStackFlag(false);
			dfs_stack_.pop();
			current_tile_ = dfs_stack_.top();
		}
		else if (dfs_stack_.size() == 1)
		{
			dfs_stack_.top()->GetFlags()->SetOnStackFlag(false);
			dfs_stack_.empty();
			SetDone();
		}

	}
}



void GenerateMazeState::HandleEvents()
{
	sf::Event event;

	while (demo_->window_.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		{
			demo_->window_.close();
			break;
		}
		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::Space && GetDone())
				PushBfsSolverState(); 
			if (event.key.code == sf::Keyboard::F1 && GetDone()) 
				PushGenerateMazeState();
			if (event.key.code == sf::Keyboard::Escape)
				PushMenuState();

				break;
		}
		default:
			break;
		}
	}
}



GenerateMazeState::GenerateMazeState(Demo* demo, int cols)
	: 
	MazeState::MazeState(demo, cols),
	maze_done_(false)
{
	dfs_stack_.empty();
	current_tile_ = grid_[RandomInt(0, grid_.size() - 1)];
	dfs_stack_.push(current_tile_);

	hud_->InsertHudMsg(L"Tworzê labirynt", sf::Vector2f(10,10));
	hud_->InsertHudMsg(L"U¿yty algorytm Recursive Backtracking (DFS)", 
								sf::Vector2f(10, 35));
	hud_->InsertHudMsg(L"Esc menu", sf::Vector2f(10, 60));
}



GenerateMazeState::~GenerateMazeState()
{
}
