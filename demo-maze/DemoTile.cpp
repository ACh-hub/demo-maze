//
//  File:        DemoTile.cpp
//  Created:     11-08-2017
//  Author:      Aleksandra Chrapkowska
//  mail:        amchrapkowska@gmail.com
//

#include "DemoTile.h"


sf::Vector2i DemoTile::GetTileRealCoordinates()
{
	sf::Vector2i real_coordinates;
	real_coordinates.x = tile_coordinates_.x * size_;
	real_coordinates.y = tile_coordinates_.y * size_;
	return real_coordinates;
}


void DemoTile::SetTileColor(sf::Color color)
{
	if (tile_shape_.getFillColor() != color)
		tile_shape_.setFillColor(color);
}


void DemoTile::DrawTile(sf::RenderWindow* window, float timestamp)
{
	window->draw(tile_shape_);
	walls_->DrawWalls(window, timestamp);
}


DemoTile::DemoTile(sf::Vector2f coordinates, int size)
	:
	tile_coordinates_(coordinates), size_(size)
{

	sf::Color default_color = sf::Color(98,141,13);
	sf::Vector2f tile_position = sf::Vector2f(size * GetX(), size * GetY());

	tile_shape_ = sf::RectangleShape(sf::Vector2f(size, size));
	tile_shape_.setPosition(tile_position.x, tile_position.y);
	tile_shape_.setFillColor(default_color);

	walls_ = new Walls(GetX(), GetY(), size);
	flags_ = new Flags();
}


DemoTile::~DemoTile()
{
}

void Walls::DrawWalls(sf::RenderWindow * window, const float timestamp)
{
	if (north_wall_)
		window->draw(n_wall_shape_);
	if (east_wall_)
		window->draw(e_wall_shape_);
	if (south_wall_)
		window->draw(s_wall_shape_);
	if (west_wall_)
		window->draw(w_wall_shape_);
}

Walls::Walls(int x, int y, int size)
	:
	north_wall_(true), east_wall_(true), south_wall_(true), west_wall_(true)
{
	int wall_width = 1;
	int offset = size - wall_width;
	sf::Vector2f tile_position = sf::Vector2f(size * x, size * y);
	sf::Color default_walls_color = sf::Color(40,40,40);

	n_wall_shape_ = sf::RectangleShape(sf::Vector2f(size, wall_width));
	n_wall_shape_.setPosition(tile_position.x, tile_position.y);
	n_wall_shape_.setFillColor(default_walls_color);

	e_wall_shape_ = sf::RectangleShape(sf::Vector2f(wall_width, size));
	e_wall_shape_.setPosition(tile_position.x + offset, tile_position.y);
	e_wall_shape_.setFillColor(default_walls_color);

	s_wall_shape_ = sf::RectangleShape(sf::Vector2f(size, wall_width));
	s_wall_shape_.setPosition(tile_position.x, tile_position.y + offset);
	s_wall_shape_.setFillColor(default_walls_color);

	w_wall_shape_ = sf::RectangleShape(sf::Vector2f(wall_width, size));
	w_wall_shape_.setPosition(tile_position.x, tile_position.y);
	w_wall_shape_.setFillColor(default_walls_color);
}

Walls::~Walls()
{
}

void Flags::ClearAllFlags()
{
	SetIsVisitedFlag(false);
	SetOnStackFlag(false);
	SetDoneFlag(false);
	SetIsExpandedFlag(false);
	SetIsPathFlag(false);
}

Flags::Flags()
	:
	_is_visited_flag_(false), _on_stack_flag_(false), _done_flag_(false)
{
}

Flags::~Flags()
{
}
