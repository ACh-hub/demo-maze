//
//  File:        DemoTile.h
//  Description: Classes for creating and managing the single tile of the maze
//  Created:     11-08-2017
//  Author:      Aleksandra Chrapkowska
//  mail:        amchrapkowska@gmail.com
//
// (c) 2017 Aleksandra Chrapkowska
// This code is licensed under MIT license (see LICENSE.txt for details)
//

#pragma once

#include<SFML\Graphics.hpp>

#include"Demo.h"


class Walls;
class Flags;

class DemoTile
{
protected:
	sf::Vector2f tile_coordinates_;
	int size_;
	sf::RectangleShape tile_shape_;
	Walls* walls_;
	Flags* flags_;
public:
	sf::Vector2f GetTileCoordinates() { return tile_coordinates_; }
	sf::Vector2i GetTileRealCoordinates();
	void SetTileCoordinates(sf::Vector2f coordinates) { tile_coordinates_ = coordinates; }
	int GetX() { return (int)(tile_coordinates_.x); }
	int GetY() { return (int)(tile_coordinates_.y); }
	int GetSize() { return size_; }
	Flags* GetFlags() { return flags_; }
	Walls* GetWalls() { return walls_; }
	void SetTileColor(sf::Color color);
	void DrawTile(sf::RenderWindow* window, const float timestamp);
	DemoTile(sf::Vector2f coordinates, int size);
	~DemoTile();
};


class Walls
{
private:
	bool north_wall_, east_wall_, south_wall_, west_wall_;
	sf::RectangleShape n_wall_shape_;
	sf::RectangleShape e_wall_shape_;
	sf::RectangleShape s_wall_shape_;
	sf::RectangleShape w_wall_shape_;

public:
	bool GetNwall() { return north_wall_; }
	void SetNWall(bool val) { north_wall_= val; }
	bool GetEwall() { return east_wall_; }
	void SetEWall(bool val) { east_wall_ = val; }
	bool GetSwall() { return south_wall_; }
	void SetSWall(bool val) { south_wall_ = val; }
	bool GetWwall() { return west_wall_; }
	void SetWWall(bool val) { west_wall_ = val; }
	void DrawWalls(sf::RenderWindow* window, const float timestamp);
	Walls(int x, int y, int size);
	~Walls();
};


class Flags
{
private:
	bool _is_visited_flag_, _on_stack_flag_, _done_flag_;
	bool _is_expanded_flag_, _is_path_flag_;
public:
	sf::Color is_visited_color = sf::Color(169, 238, 171);
	sf::Color on_stack_color_ = sf::Color(151, 201, 119);
	sf::Color done_color_ = sf::Color(255, 252, 184);
	sf::Color is_expanded_color_ = sf::Color(151, 208, 236);
	sf::Color is_path_color = sf::Color(244, 168, 218);
	void ClearAllFlags();
	bool GetIsVisitedFlag() { return _is_visited_flag_; }
	void SetIsVisitedFlag(bool val) { _is_visited_flag_=val; }
	bool GetOnStackFlag() { return _on_stack_flag_; }
	void SetOnStackFlag(bool val) { _on_stack_flag_ = val; }
	bool GetDoneFlag() { return _done_flag_; }
	void SetDoneFlag(bool val) { _done_flag_ = val; }
	bool GetIsExpandedFlag() { return _is_expanded_flag_; }
	void SetIsExpandedFlag(bool val) { _is_expanded_flag_ = val; }
	bool GetIsPathFlag() { return _is_path_flag_; }
	void SetIsPathFlag(bool val) { _is_path_flag_ = val; }
	Flags();
	~Flags();
};

