//
//  File:			DemoHud.cpp	
//  Created:		11-08-2017
//  Author:			Aleksandra Chrapkowska
//  mail:			amchrapkowska@gmail.com
//
// (c) 2017 Aleksandra Chrapkowska
// This code is licensed under MIT license (see LICENSE.txt for details)
//

#include "DemoHud.h"
#include "DemoHelpers.h"


// Add HUD texts
// @param relative_position describes position relative to upper left corner of 
// hud instance
void DemoHud::InsertHudMsg(std::wstring message, sf::Vector2f relative_position)
{
	sf::Vector2f real_position;
	real_position.x = hud_ticker_shape_.getPosition().x + relative_position.x;
	real_position.y = hud_ticker_shape_.getPosition().y + relative_position.y;


	hud_messages_.push_back(new HudText(message, real_position));
}


void DemoHud::ClearHudMsgs()
{
	hud_messages_.clear();
}


void DemoHud::DrawHud(sf::RenderWindow * window, const float timestamp)
{
	window->draw(this->hud_ticker_shape_);

	if (!hud_messages_.empty())
	{
		for (auto it = hud_messages_.begin(); it != hud_messages_.end(); ++it)
			window->draw((*it)->GetHudTextMessage());
	}
}


DemoHud::DemoHud(sf::Vector2f position, sf::Vector2f size)
{	
	hud_messages_.clear();
	hud_ticker_color_ = sf::Color(255,255,255,150);
	hud_ticker_shape_.setPosition(position);
	hud_ticker_shape_.setSize(size);
	hud_ticker_shape_.setFillColor(hud_ticker_color_);

}


DemoHud::~DemoHud(){}


// HUD text constructor
HudText::HudText(std::wstring message, sf::Vector2f position)
	:
	message_text_(message), message_text_position(position)
{
	message_settings_ = new HudTextSettings();
	hud_text_message_.setFont(message_settings_->message_font_);
	hud_text_message_.setColor(message_settings_->message_font_color_);
	hud_text_message_.setCharacterSize(message_settings_->message_font_size_pixels_);
	hud_text_message_.setPosition(position);
	hud_text_message_.setString(message);
}


HudText::~HudText(){}



// Settings HUD 
HudTextSettings::HudTextSettings()
{
	if (!message_font_.loadFromFile("Fonts\\arial.ttf"))
		throw  DemoException("No_texture");
}



HudTextSettings::~HudTextSettings(){}
