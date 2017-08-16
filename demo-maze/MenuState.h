//
//  File:			MenuState.h
//  Description:	G³ówne menu
//  Created:		15-08-2017
//  Author:			Aleksandra Chrapkowska
//  mail:			amchrapkowska@gmail.com
//

#pragma once

#include<vector>
#include "DemoState.h"
#include "GenerateMazeState.h"
#include "DemoHud.h"
#include "ErrorState.h"

class MenuState : public DemoState
{
private:
	DemoHud* title_;
	std::vector<DemoHud*> menu_items_;
	int active_menu_index_;
	std::wstring own_resolution_;
	sf::Texture background_image_;
	sf::Sprite background_;

public:
	void PushErrorState();
	void PushGenerateMazeState(int cols);
	void CreateMenuItems(sf::Vector2f initial_position, sf::Vector2f menu_item_size, std::vector<std::wstring> msgs, sf::Color menu_color);
	virtual void Draw(const float timestamp);
	virtual void Update(const float timestamp);
	virtual void HandleEvents();
	MenuState(Demo* demo);
	~MenuState();
};

