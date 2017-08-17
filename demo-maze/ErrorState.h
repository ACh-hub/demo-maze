//
//  File:        ErrorState.h
//  Description: Sad panda. Error state.
//  Created:     15-08-2017
//  Author:      Aleksandra Chrapkowska
//  mail:        amchrapkowska@gmail.com
//
// (c) 2017 Aleksandra Chrapkowska
// This code is licensed under MIT license (see LICENSE.txt for details)
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

