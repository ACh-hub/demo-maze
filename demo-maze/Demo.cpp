//
//  File:        DemoTile.h
//  Description: 
//  Created:     11-08-2017
//  Author:      Aleksandra Chrapkowska
//  mail:        amchrapkowska@gmail.com
//

#include<SFML\Graphics.hpp>
#include<SFML\System.hpp>

#include "Demo.h"
#include"DemoState.h"


// 
inline void Demo::PushState(DemoState* state)
{
	states_.push(state);
}

void Demo::PopState()
{
	delete states_.top();
	states_.pop();
}

void Demo::ChangeState(DemoState* state)
{
	if (!states_.empty())
		PopState();
	PushState(state);
}

DemoState* Demo::TopState()
{
	if (states_.empty()) return nullptr;
	else return states_.top();
}

// Main loop
void Demo::RunDemo()
{
	sf::Clock clock;

	while (window_.isOpen())
	{
		sf::Time elapsed = clock.restart();
		float timestamp = elapsed.asSeconds();
		if (TopState() == nullptr) continue;
		TopState()->HandleEvents();
		TopState()->Update(timestamp);
		window_.clear(sf::Color::White);
		TopState()->Draw(timestamp);
		window_.display();
	}
}

Demo::Demo(int demo_width, int demo_height)
	:demo_width_(demo_width), demo_height_(demo_height)
{

	window_.create(sf::VideoMode(demo_width, demo_height), "Maze", sf::Style::Close);
	window_.setFramerateLimit(demo_frames_limit);
}


Demo::~Demo()
{
	while (!states_.empty()) PopState();
}
