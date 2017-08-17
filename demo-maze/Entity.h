//
//  File:			Entity.h
//  Description:	The class for entities: pacman, path dots.
//  Created:		13-08-2017
//  Author:			Aleksandra Chrapkowska
//  mail:			amchrapkowska@gmail.com
//
// (c) 2017 Aleksandra Chrapkowska
// This code is licensed under MIT license (see LICENSE.txt for details)
//

#pragma once

#include <SFML\Graphics.hpp>

#include "DemoTile.h"
#include "DemoAnimation.h"


class Entity
{
public:
	AnimationHandler* animation_handler_;
	virtual void Draw(sf::RenderWindow * window, const float timestamp) = 0;
	virtual void Update(const float timestamp) = 0;
	virtual int ChangeAnimation(int animation_number) = 0;
	Entity();
	virtual ~Entity();
};


class Dot : public Entity
{
protected:
	sf::Vector2i _dot_coordinates_;
	sf::CircleShape _dot_shape_;
	sf::Color _dot_shape_color_;
	int _dot_radius_;
public:
	sf::Vector2i GetCoordinates() { return _dot_coordinates_; }
	virtual void Draw(sf::RenderWindow * window, const float timestamp);
	virtual void Update(const float timestamp);
	virtual int ChangeAnimation(int animation_number);
	Dot() {}
	Dot(sf::Vector2i coordinates, int size, int radius = 4);
	~Dot();
};


class Pac : public Dot
{
private:
	sf::Texture pac_texture_;
	sf::Sprite pac_sprite_;

public:
	void RotatePac(std::string direction);
	void MovePac(DemoTile* current_tile, DemoTile* next_tile);
	sf::Vector2i GetCoordinates() { return sf::Vector2i(pac_sprite_.getPosition()); }
	virtual void Draw(sf::RenderWindow * window, const float timestamp);
	virtual void Update(const float timestamp);
	virtual int ChangeAnimation(int animation_number);
	Pac() {}
	Pac(sf::Vector2i coordinates, int size);
	~Pac();
};

