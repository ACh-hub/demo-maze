//
//  File:			DemoAnimation.h
//	Description:	Classes providing animation handling for the entities	
//  Created:		17-08-2017
//  Author:			Aleksandra Chrapkowska
//  mail:			amchrapkowska@gmail.com
//
// (c) 2017 Aleksandra Chrapkowska
// This code is licensed under MIT license (see LICENSE.txt for details)


#include "DemoAnimation.h"
#include "DemoHelpers.h"

// DemoAnimation constructor
DemoAnimation::DemoAnimation(int start_frame, int end_frame, float duration)
	:
	start_frame_(start_frame), end_frame_(end_frame), duration_(duration),
	is_stopped_(false), is_looped_(true), frames_played(0)
{
}


DemoAnimation::~DemoAnimation()
{
}


void AnimationHandler::AddAnimation(DemoAnimation * animation)
{
	animations_.push_back(animation);
}


void AnimationHandler::Update(const float timestamp)
{

	if (!(current_animation_ >= animations_.size() || current_animation_ < 0))
	{

   		float duration = animations_[current_animation_]->duration_;

		if (int((time_since_started_ + timestamp) / duration) >= int(time_since_started_ / duration))
		{
  			int frame = int((time_since_started_ + timestamp)/duration);

      		frame = frame % (animations_[current_animation_]->GetAnimationLength());

			sf::IntRect frame_rectangle = frame_size_;
			frame_rectangle.left = frame_rectangle.width * frame;				
			frame_rectangle.top = frame_rectangle.height * current_animation_;
			frame_bounds_ = frame_rectangle;
		}

		time_since_started_ += timestamp;

		if (time_since_started_ > duration * animations_[current_animation_]->GetAnimationLength())
			time_since_started_ = 0;
		
	}

}


void AnimationHandler::ChangeAnimation(int animation_number)
{
		current_animation_ = animation_number;
		sf::IntRect frame_rectangle = frame_size_;
		frame_rectangle.top = frame_rectangle.height * animation_number;
		frame_bounds_ = frame_rectangle;
		time_since_started_ = 0;
}


// AnimationHandler constructor
AnimationHandler::AnimationHandler()
	:
	time_since_started_(0), current_animation_(-1)
{}

AnimationHandler::AnimationHandler(const sf::IntRect & frame_size)
	:
	frame_size_(frame_size)
{
	AnimationHandler();
}


AnimationHandler::~AnimationHandler()
{
}
