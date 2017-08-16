//
//  File:			Demo.h
//	Description:	Manager stanów, g³ówna pêtla	
//  Created:		11-08-2017
//  Author:			Aleksandra Chrapkowska
//  mail:			amchrapkowska@gmail.com
//

#pragma once

#include<stack>

#include<SFML\Graphics.hpp>

#include"DemoState.h"



class DemoState;

class Demo
{
public:
	int demo_frames_limit = 60;
	int demo_width_;
	int demo_height_;
	std::stack<DemoState*> states_;
	sf::RenderWindow window_;
	void PushState(DemoState* state);
	void PopState();
	void ChangeState(DemoState* state);
	DemoState* TopState();
	void RunDemo();
	Demo(int demo_width, int demo_height);
	~Demo();
};

