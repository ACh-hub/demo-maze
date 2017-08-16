//
//  File:			BfsSolverState.cpp	
//  Created:		11-08-2017
//  Author:			Aleksandra Chrapkowska
//  mail:			amchrapkowska@gmail.com
//

#include <algorithm>

#include "BfsSolverState.h"
#include "DemoHelpers.h"


void BfsSolverState::AddNeighbourToQueue(int index, int current_index)
{
	if (!grid_[index]->GetFlags()->GetOnStackFlag() 
		&& !grid_[index]->GetFlags()->GetIsExpandedFlag())
	{
		bfs_queue_.push(grid_[index]);
		grid_[index]->GetFlags()->SetOnStackFlag(true);
		shortest_path_[index] = current_index;
	}
}



inline void BfsSolverState::PushSolvedState()
{
	demo_->PushState(new SolvedState(GetGrid(), GetShortestPath(), GetStartTile(), 
					GetEndTile(), demo_, maze_cols_));
}



void BfsSolverState::Draw(const float timestamp)
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
	hud_->DrawHud(&(demo_->window_), timestamp);
}


// BFS
void BfsSolverState::Update(const float timestamp)
{
	int index;
	int current_index;

	current_tile_->GetFlags()->SetIsVisitedFlag(true);

	// using on_stack_ flag for not to create separate for the queue
	current_tile_->GetFlags()->SetOnStackFlag(true);

	current_index = GetTileIndexByPosition(current_tile_->GetX(), current_tile_->GetY());

	if (bfs_queue_.size() > 0)
	{
		if (bfs_queue_.front() != end_tile_)
		{
			/// dequeue and expand
			bfs_queue_.front()->GetFlags()->SetIsVisitedFlag(true);
			bfs_queue_.front()->GetFlags()->SetIsExpandedFlag(true);
			bfs_queue_.front()->GetFlags()->SetOnStackFlag(false);
			bfs_queue_.pop();

			if (!current_tile_->GetWalls()->GetWwall())
			{
				index = GetTileIndexByPosition(current_tile_->GetX() - 1, current_tile_->GetY());
				AddNeighbourToQueue(index, current_index);
			}

			if (!current_tile_->GetWalls()->GetNwall())
			{
				index = GetTileIndexByPosition(current_tile_->GetX(), current_tile_->GetY() - 1);
				AddNeighbourToQueue(index, current_index);
			}

			if (!current_tile_->GetWalls()->GetSwall())
			{
				index = GetTileIndexByPosition(current_tile_->GetX(), current_tile_->GetY() + 1);
				AddNeighbourToQueue(index, current_index);
			}

			if (!current_tile_->GetWalls()->GetEwall())
			{
				index = GetTileIndexByPosition(current_tile_->GetX() + 1, current_tile_->GetY());
				AddNeighbourToQueue(index, current_index);
			}

			current_tile_ = bfs_queue_.front();
		}
		else
		{

			int start_index = GetTileIndexByPosition(start_tile_->GetX(), start_tile_->GetY());
			int end_index = GetTileIndexByPosition(end_tile_->GetX(), end_tile_->GetY());
			int temp = end_index;

			std::vector<int> temporary_for_path = shortest_path_;
			shortest_path_.clear();

			do
			{
				grid_[temp]->GetFlags()->SetIsPathFlag(true);
				temp = temporary_for_path[temp];

				shortest_path_.push_back(temp);
			} while (temp != start_index);
			
			std::reverse(shortest_path_.begin(), shortest_path_.end());
			PushSolvedState();
		}
	}
	else
	{
		// Recursive Backtracking tworzy labirynty idealne, 
		// wiêc zawsze istnieje œcie¿ka
	}
}



// Konstruktor
BfsSolverState::BfsSolverState(std::vector<DemoTile*> grid, Demo * demo, int cols)
	:
	MazeState::MazeState(demo, cols)
{
	grid_ = grid;
	for (auto it = grid_.begin(); it != grid_.end(); ++it)
	{
		(*it)->GetFlags()->ClearAllFlags();
		(*it)->SetTileColor((*it)->GetFlags()->done_color_);
	}
	start_tile_ = grid_[RandomInt(0, grid_.size() - 1)];
	end_tile_ = grid_[RandomInt(0, grid_.size() - 1)];
	current_tile_ = start_tile_;

	start_tile_->GetFlags()->SetIsPathFlag(true);
	end_tile_->GetFlags()->SetIsPathFlag(true);

	shortest_path_.clear();
	shortest_path_.resize(grid_.size());

	bfs_queue_.push(current_tile_);

	hud_->InsertHudMsg(L"Poszukiwanie najkrótszej œcie¿ki.", sf::Vector2f(10, 35));
	hud_->InsertHudMsg(L"U¿yty algorytm BFS.", sf::Vector2f(10, 60));
}


BfsSolverState::~BfsSolverState() {}
