//
//  File:			DemoAnimation.h
//	Description:	Classes providing animation handling for the entities	
//  Created:		17-08-2017
//  Author:			Aleksandra Chrapkowska
//  mail:			amchrapkowska@gmail.com
//
// (c) 2017 Aleksandra Chrapkowska
// This code is licensed under MIT license (see LICENSE.txt for details)

#pragma once

#include<vector>

#include<SFML\Graphics.hpp>


class DemoAnimation
{
public:
	int start_frame_, end_frame_;
	float duration_;
	int GetAnimationLength() { return end_frame_ - start_frame_ + 1; }
	DemoAnimation(int start_frame, int end_frame, float duration);
	~DemoAnimation();
};


class AnimationHandler
{
private:
	std::vector<DemoAnimation*> animations_;
	float time_since_started_;
	int current_animation_;
public:
	sf::IntRect frame_bounds_, frame_size_;
	void AddAnimation(DemoAnimation* animation);
	void Update(const float timestamp);
	void ChangeAnimation(int animation_number);

	AnimationHandler();
	AnimationHandler(const sf::IntRect& frame_size);
	~AnimationHandler();

};