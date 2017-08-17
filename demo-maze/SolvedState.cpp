//
//  File:        SolvedState.cpp
//  Created:     14-08-2017
//  Author:      Aleksandra Chrapkowska
//  mail:        amchrapkowska@gmail.com
//
// (c) 2017 Aleksandra Chrapkowska
// This code is licensed under MIT license (see LICENSE.txt for details)

#include "SolvedState.h"
#include "Entity.h"
#include "GenerateMazeState.h"


std::string SolvedState::GetPassageDirection(DemoTile * tile_from, DemoTile * tile_to)
{
	std::string direction;
	int x_diff = tile_from->GetTileCoordinates().x - tile_to->GetTileCoordinates().x;
	int y_diff = tile_from->GetTileCoordinates().y - tile_to->GetTileCoordinates().y;

	if (x_diff>0 && y_diff==0)
		return "WEST";

	if (x_diff==0 && y_diff > 0)
		return "NORTH";

	if (x_diff<0 && y_diff == 0)
		return "EAST";

	if (x_diff == 0 && y_diff < 0)
		return "SOUTH";
	
	direction = "NO_PASARAN__";
		
	return direction;
}


DemoTile * SolvedState::GetTileByIndex(int index)
{
	if(index<grid_.size())
		return grid_[index];
	else return nullptr;
}


void SolvedState::Draw(const float timestamp)
{
	// flags colors and priorities
	for (auto it = grid_.begin(); it != grid_.end(); ++it)
	{
		if ((*it)->GetFlags()->GetIsPathFlag())
			(*it)->SetTileColor((*it)->GetFlags()->is_path_color);
		else if ((*it)->GetFlags()->GetOnStackFlag())
			(*it)->SetTileColor((*it)->GetFlags()->on_stack_color_);
		else if ((*it)->GetFlags()->GetIsVisitedFlag())
			(*it)->SetTileColor((*it)->GetFlags()->is_visited_color);
	}
	MazeState::Draw(timestamp);
	for (auto it = path_dots_.begin(); it != path_dots_.end(); ++it)
		(*it)->Draw(&(demo_->window_), timestamp);
	pac_man_->Draw(&(demo_->window_), timestamp);
	hud_->DrawHud(&(demo_->window_), timestamp);
}


void SolvedState::Update(const float timestamp)
{
	try
	{
		//change the animation if at the end
		if (current_tile_ == end_tile_)
		{
			if (pac_man_->animation_handler_->GetCurrentAnimation() != 1)
				pac_man_->ChangeAnimation(1);

			if (pac_man_->animation_handler_->GetAnimations()[1]->frames_played == 10)
			{
				if(pac_man_->animation_handler_->GetCurrentAnimation() != 2)
					pac_man_->ChangeAnimation(2);
				if (pac_man_->animation_handler_->GetAnimations()[2]->frames_played == 10)
					pac_man_->ChangeAnimation(3);
			}
		}

		// Update pacman animation
  		pac_man_->Update(timestamp);


		// Remove the dot under pacman
		for (auto it = path_dots_.begin(); it != path_dots_.end(); )
		{
			if ((*it)->GetCoordinates() == pac_man_->GetCoordinates())
				it = path_dots_.erase(it);
			else
				++it;
		}

		// Check where to turn (get the common wall for short-path adjacent index)
		int current_index = GetTileIndexByPosition(current_tile_->GetX(), current_tile_->GetY());
		int next_index = -1;

		for (auto it = shortest_path_.begin(); it != shortest_path_.end(); )
		{
			if ((*it) == current_index)
			{
				if (!(it + 1 == shortest_path_.end()))
				{
					next_index = *(it + 1);
					it = shortest_path_.erase(it);
				}
				else
				{
					next_index = shortest_path_.at(0);
					it = shortest_path_.erase(it);
				}
			}
			else
				++it;
		}

		if (next_index != -1)
		{
			DemoTile* next_tile = GetTileByIndex(next_index);
			std::string next_turn = GetPassageDirection(current_tile_, next_tile);

			// Rotate pacman
			pac_man_->RotatePac(next_turn);
			// Move pacman
			pac_man_->MovePac(current_tile_, next_tile);

			current_tile_ = next_tile;
		}
		else
		{
			pac_man_->MovePac(current_tile_, end_tile_);
			current_tile_ = end_tile_;
		}
	}
	catch (DemoException const& exception)
	{
		PushErrorState();
	}
}


void SolvedState::HandleEvents()
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
			if (event.key.code == sf::Keyboard::Space)
				PushBfsSolverState();
			if (event.key.code == sf::Keyboard::Escape)
				PushMenuState();

			break;
		}
		default:
			break;
		}
	}
}


void SolvedState::PushBfsSolverState()
{

	demo_->PushState(new BfsSolverState(GetGrid(), demo_, maze_cols_));
}


void SolvedState::PushGenerateMazeState()
{

	demo_->PushState(new GenerateMazeState(demo_, maze_cols_));
}


void SolvedState::PushMenuState()
{
	demo_->PushState(new MenuState(demo_));
}

void SolvedState::PushErrorState()
{
	demo_->PushState(new ErrorState(demo_));
}


SolvedState::SolvedState(std::vector<DemoTile*> grid, 
						std::vector<int> shortest_path, DemoTile * start, 
						DemoTile * end, Demo * demo, int cols)
	:
	MazeState::MazeState(demo, cols)
{
	grid_ = grid;
	shortest_path_ = shortest_path;
	start_tile_ = start;
	end_tile_ = end;
	current_tile_ = start_tile_;
	path_dots_.clear();
	int radius = (int)start_tile_->GetSize() / 6;
	for (auto it = shortest_path_.begin(); it != shortest_path_.end(); ++it)
	{
		path_dots_.push_back(new Dot(grid_[(*it)]->GetTileRealCoordinates(), 
									start_tile_->GetSize(), radius));
	}
	path_dots_.push_back(new Dot(end_tile_->GetTileRealCoordinates(),
								start_tile_->GetSize(), radius));

	pac_man_ = new Pac(start_tile_->GetTileRealCoordinates(), (int)start_tile_->GetSize());


	GetHud()->InsertHudMsg(L"Space  nowe rozwi¹zanie", sf::Vector2f(10, 35));
	GetHud()->InsertHudMsg(L"Esc  menu", sf::Vector2f(10, 60));
}


SolvedState::~SolvedState()
{
}
