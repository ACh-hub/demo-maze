//
//  File:			DemoHud.h
//	Description:	Wyœwietlanie HUD.	
//  Created:		13-08-2017
//  Author:			Aleksandra Chrapkowska
//  mail:			amchrapkowska@gmail.com
//

#pragma once
#include<vector>

#include<SFML\Graphics.hpp>

class HudTextSettings;
class HudText;


// Podstawowa klasa do rysowania HUD
class DemoHud
{
private:
	sf::RectangleShape hud_ticker_shape_;
	sf::Color hud_ticker_color_;
	std::vector<HudText*> hud_messages_;
public:
	std::vector<HudText*> GetHudMessages() { return hud_messages_; }
	void SetHudColor(sf::Color color) { hud_ticker_shape_.setFillColor(color); }
	void SetHudOutline(bool val) { hud_ticker_shape_.setOutlineThickness((int)val); }
	void InsertHudMsg(std::wstring message, sf::Vector2f relative_position);
	void ClearHudMsgs();
	void DrawHud(sf::RenderWindow* window, const float timestamp);
	DemoHud(sf::Vector2f position, sf::Vector2f size);
	~DemoHud();
};

// Tekst do wyœletlania na HUD
class HudText
{
private:
	sf::Text hud_text_message_;
	std::wstring message_text_;
	sf::Vector2f message_text_position;
	HudTextSettings* message_settings_;
public:
	sf::Text GetHudTextMessage() { return hud_text_message_; }
	void SetMessageFontSize(int pixels) { hud_text_message_.setCharacterSize(pixels); }
	HudText(std::wstring message, sf::Vector2f position);
	~HudText();
};

//Ustawienia HUD
class HudTextSettings
{
public:
	sf::Font message_font_;
	int message_font_size_pixels_ = 18;
	sf::Color message_font_color_ = sf::Color(0, 51, 0);
	int GetFontSize() { return message_font_size_pixels_; }
	void SetFontSize(int pixels) { message_font_size_pixels_ = pixels; }
	HudTextSettings();
	~HudTextSettings();
};


