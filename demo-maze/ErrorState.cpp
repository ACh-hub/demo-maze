//
//  File:        DemoTile.h
//  Description: 
//  Created:     11-08-2017
//  Author:      Aleksandra Chrapkowska
//  mail:        amchrapkowska@gmail.com
//

#include "ErrorState.h"



void ErrorState::Draw(const float timestamp)
{
	demo_->window_.draw(panda_);
	hud_->DrawHud(&(demo_->window_), timestamp);
}

void ErrorState::Update(const float timestamp)
{
}

void ErrorState::HandleEvents()
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
			if (event.key.code == sf::Keyboard::Escape)
				demo_->window_.close();
			break;
		}
		default:
			break;
		}
	}
}

ErrorState::ErrorState(Demo* demo)
{
	demo_ = demo;
	demo_->window_.setTitle("Panda ma problem :(");
	
	if (!background_image_.loadFromFile("Textures\\sad_panda_is_sad.png"))
	{
		//Error LATER ERRORSTATE
	}
	else
		panda_.setTexture(&background_image_);

	panda_.setPosition(sf::Vector2f(180, 50));
	panda_.setSize(sf::Vector2f(250, 430));

	// main view
	sf::Vector2f view_size = sf::Vector2f(demo_->window_.getSize());
	main_view_.setSize(view_size);
	sf::Vector2f view_center = view_size * 0.5f;
	main_view_.setCenter(view_center);

	//Informacja
	sf::Vector2f hud_pos = sf::Vector2f(0, 510);
	sf::Vector2f hud_size = sf::Vector2f(600,50);
	hud_ = new DemoHud(hud_pos, hud_size);

	hud_->InsertHudMsg(L"Coœ posz³o dramatycznie nie tak. Panda jest smutna :(", sf::Vector2f(70, 10));
	hud_->InsertHudMsg(L"Esc wyjœcie", sf::Vector2f(70, 45));
}


ErrorState::~ErrorState()
{
}
