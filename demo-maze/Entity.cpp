//
//  File:        Entity.cpp

//  Created:     13-08-2017
//  Author:      Aleksandra Chrapkowska
//  mail:        amchrapkowska@gmail.com
//

#include "Entity.h"
#include "DemoTile.h"

Entity::Entity()
{
}


Entity::~Entity()
{
}



void Dot::Draw(sf::RenderWindow * window, const float timestamp)
{
	window->draw(_dot_shape_);
}



Dot::Dot(sf::Vector2i coordinates, int size, int radius)
	:
	_dot_radius_(radius)
{
	int tile_size = size;
	_dot_coordinates_.x = coordinates.x + size / 2;
	_dot_coordinates_.y = coordinates.y + size / 2;
	_dot_shape_color_ = sf::Color(54, 17, 103);
	_dot_shape_.setFillColor(_dot_shape_color_);
	_dot_shape_.setRadius(radius);
	_dot_shape_.setOrigin(sf::Vector2f(radius, radius));
	_dot_shape_.setPosition(sf::Vector2f(_dot_coordinates_));

}


Dot::~Dot()
{
}


void Pac::RotatePac(std::string direction)
{
	pac_sprite_.setRotation(0);

	if (direction == "NORTH")
		pac_sprite_.rotate(270);
	else if (direction == "EAST")
		pac_sprite_.rotate(0);
	else if (direction == "SOUTH")
		pac_sprite_.rotate(90);
	else if (direction == "WEST")
		pac_sprite_.rotate(180);
	else
		;
}



void Pac::MovePac(DemoTile * current_tile, DemoTile * next_tile)
{
	sf::Vector2f current_tile_coords = sf::Vector2f(current_tile->GetTileRealCoordinates());
	sf::Vector2f next_tile_coords = sf::Vector2f(next_tile->GetTileRealCoordinates());
	sf::Vector2f pac_coords = pac_sprite_.getPosition();

	float x_move = next_tile_coords.x - current_tile_coords.x;
	float y_move = next_tile_coords.y - current_tile_coords.y;

	pac_sprite_.move(sf::Vector2f(x_move, y_move));
	sf::sleep(sf::seconds(0.1)); // wait for a second(actually 0.02)
}


void Pac::Draw(sf::RenderWindow * window, const float timestamp)
{
	
	window->draw(pac_sprite_);
}

Pac::Pac(sf::Vector2i coordinates, int size)
{

	sf::IntRect framesize = sf::IntRect(0, 0, 128, 128);
	if (!pac_texture_.loadFromFile("Textures//pac_texture.png", framesize));
	{
		// error...
	}

	pac_animation_handler_ = new AnimationHandler(framesize);
	pac_animation_handler_->AddAnimation(new DemoAnimation(0, 3, 1));

	pac_sprite_.setTexture(pac_texture_);
	sf::Vector2u texture_size = pac_texture_.getSize();
	sf::Vector2f pac_scale;
	pac_scale.x = (float)size / texture_size.x;
	pac_scale.y = (float)size / texture_size.y;
	pac_sprite_.setOrigin(sf::Vector2f(texture_size.x/2,texture_size.y/2));
	pac_sprite_.setPosition(sf::Vector2f(coordinates.x+size/2,coordinates.y+size/2));
	pac_sprite_.setScale(sf::Vector2f(pac_scale));


}

Pac::~Pac()
{
}
