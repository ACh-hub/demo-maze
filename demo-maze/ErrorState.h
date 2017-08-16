//
//  File:        ErrorState.h
//  Description: stan do wy�wietlania informacji o b��dzie.
//  Created:     15-08-2017
//  Author:      Aleksandra Chrapkowska
//  mail:        amchrapkowska@gmail.com
//

#pragma once

#include "DemoState.h"


class ErrorState : public DemoState
{
private:
	sf::Texture background_image_;
	sf::RectangleShape panda_;
public:
	virtual void Draw(const float timestamp);
	virtual void Update(const float timestamp);
	virtual void HandleEvents();
	ErrorState(Demo* demo);
	~ErrorState();
};

