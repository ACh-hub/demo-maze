//
//  File:			MenuState.cpp
//  Created:		15-08-2017
//  Author:			Aleksandra Chrapkowska
//  mail:			amchrapkowska@gmail.com
//

#include "MenuState.h"
#include<string>


MenuState::MenuState(Demo* demo)
{
	demo_ = demo;
	
	// main view
	sf::Vector2f view_size = sf::Vector2f(demo_->window_.getSize());
	main_view_.setSize(view_size);
	sf::Vector2f view_center = view_size * 0.5f;
	main_view_.setCenter(view_center);

	//Background
	if (!background_image_.loadFromFile("Textures\\background.png"))
	{
		PushErrorState();
	}
	else
		background_.setTexture(background_image_);

	// Hud na górze
	sf::Vector2f title_pos = sf::Vector2f(0, 0);
	sf::Vector2f title_size = sf::Vector2f(view_size.x, 150);
	title_ = new DemoHud(title_pos, title_size);

	title_->InsertHudMsg(L"Labirynt", sf::Vector2f(10, 10));
	title_->GetHudMessages()[0]->SetMessageFontSize(32);
	title_->InsertHudMsg(L"Tworzenie labiryntu: algorytm Recursive Backtracking", 
						sf::Vector2f(10, 60));
	title_->GetHudMessages()[1]->SetMessageFontSize(16);
	title_->InsertHudMsg(L"Najkrótsza œcie¿ka: algorytm Breadth First Search", 
						sf::Vector2f(10, 85));
	title_->GetHudMessages()[2]->SetMessageFontSize(16);
	title_->InsertHudMsg(L"Aleksandra Chrapkowska (15/08/2017)", 
						sf::Vector2f(420, 130));
	title_->GetHudMessages()[3]->SetMessageFontSize(9);

	// Menu hud
	std::vector<std::wstring> menu_messages;
	menu_messages.push_back(L"10 x 10");
	menu_messages.push_back(L"20 x 20");
	menu_messages.push_back(L"30 x 30");
	menu_messages.push_back(L"50 x 50");
	menu_messages.push_back(L"W³asne");
	menu_items_.clear();
	CreateMenuItems(sf::Vector2f(0, 200), sf::Vector2f(600, 50), 
					menu_messages, sf::Color(169, 238, 171));	// visited_color
	active_menu_index_ = 0;

	// Hud na dole
	sf::Vector2f maze_hud_pos = sf::Vector2f(0, view_size.y - (int)(view_size.y * 0.15f));
	sf::Vector2f maze_hud_size = sf::Vector2f(view_size.x, (int)(view_size.y * 0.15f));
	hud_ = new DemoHud(maze_hud_pos, maze_hud_size);

	hud_->InsertHudMsg(L"Up/Down zmiana opcji", sf::Vector2f(10, 10));
	hud_->InsertHudMsg(L"Space/Enter start", sf::Vector2f(10, 35));
	hud_->InsertHudMsg(L"Esc wyjœcie", sf::Vector2f(10, 60));

}



void MenuState::PushErrorState()
{
	demo_->PushState(new ErrorState(demo_));
}


inline void MenuState::PushGenerateMazeState(int cols)
{
	demo_->PushState(new GenerateMazeState(demo_, cols));
}


void MenuState::CreateMenuItems(sf::Vector2f initial_position, 
								sf::Vector2f menu_item_size, 
								std::vector<std::wstring> msgs, 
								sf::Color menu_color)
{

	for (int i = 0; i < msgs.size(); i++)
	{
		sf::Vector2f position = sf::Vector2f(initial_position.x, 
										initial_position.y + i*menu_item_size.y);
		sf::Vector2f msg_position = sf::Vector2f(position.x / 2, position.y / 2);
		DemoHud* temp = new DemoHud(position, menu_item_size);
		temp->SetHudColor(menu_color);
		temp->SetHudOutline(true);
		temp->InsertHudMsg(msgs[i], sf::Vector2f(10, 15));
		menu_items_.push_back(temp);

	}
}


void MenuState::Draw(const float timestamp)
{
	demo_->window_.clear(sf::Color::White);
	demo_->window_.setView(main_view_);
	
	//Background
	demo_->window_.draw(background_);

	//Title
	title_->DrawHud(&(demo_->window_), timestamp);

	//Menu items
	for (auto it = menu_items_.begin(); it != menu_items_.end(); ++it)
	{
		(*it)->DrawHud(&(demo_->window_), timestamp);

	}

	hud_->DrawHud(&(demo_->window_), timestamp);
}


void MenuState::Update(const float timestamp)
{

	for (int i = 0; i < menu_items_.size(); i++)
		menu_items_[i]->SetHudColor(sf::Color(169, 238, 171));

	menu_items_[active_menu_index_]->SetHudColor(sf::Color(151, 201, 119));
	
}


void MenuState::HandleEvents()
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
		case sf::Event::TextEntered:
		{
			if (active_menu_index_ == 4)
			{
				if (own_resolution_ == L"0")
					own_resolution_.clear();

				if (event.text.unicode > 47 && event.text.unicode < 58)
				{
					own_resolution_.push_back((char)event.text.unicode);
					std::wstring res_display = own_resolution_ + L" x " + own_resolution_;
					menu_items_[4]->ClearHudMsgs();
					menu_items_[4]->InsertHudMsg(res_display, sf::Vector2f(10, 15));
				}
				else if (event.text.unicode == 8)
				{
					if (!own_resolution_.empty())
					{
						own_resolution_.pop_back();

						std::wstring res_display = own_resolution_ + L" x " + own_resolution_;
						menu_items_[4]->ClearHudMsgs();
						menu_items_[4]->InsertHudMsg(res_display, sf::Vector2f(10, 15));
					}
				}
				break;
			}
		}
		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::Escape)
				demo_->window_.close();

			if (event.key.code == sf::Keyboard::Down)
			{
				if (active_menu_index_ != menu_items_.size() - 1)
					active_menu_index_++;
				else
					active_menu_index_ = 0;

				if (active_menu_index_ == 4)
				{
					menu_items_[active_menu_index_]->ClearHudMsgs();
					menu_items_[active_menu_index_]->InsertHudMsg(L"|", sf::Vector2f(10, 15));
				}
				else
				{
					own_resolution_ = L"0";
					menu_items_[4]->ClearHudMsgs();
					menu_items_[4]->InsertHudMsg(L"W³asne", sf::Vector2f(10, 15));
				}
			}

			if (event.key.code == sf::Keyboard::Up)
			{
				if (active_menu_index_ != 0)
					active_menu_index_--;
				else
					active_menu_index_ = menu_items_.size() - 1;

				if (active_menu_index_ == 4)
				{
					menu_items_[active_menu_index_]->ClearHudMsgs();
					menu_items_[active_menu_index_]->InsertHudMsg(L"|", sf::Vector2f(10, 15));
				}
				else
				{
					own_resolution_ = L"0";
					menu_items_[4]->ClearHudMsgs();
					menu_items_[4]->InsertHudMsg(L"W³asne", sf::Vector2f(10, 15));
				}
			}

			if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Return)
			{
				switch (active_menu_index_)
				{
					case 0:
					{
						PushGenerateMazeState(10);
						break;
					}
					case 1:
					{
						PushGenerateMazeState(20);
						break;
					}
					case 2:
					{
						PushGenerateMazeState(30);
						break;
					}
					case 3:
					{
						PushGenerateMazeState(50);
						break;
					}
					case 4:
					{
						int resolution = std::stoi(own_resolution_);
						if(resolution>0 && resolution<601)
							PushGenerateMazeState(resolution);
						else
						{
							own_resolution_.clear();
							menu_items_[4]->ClearHudMsgs();
							menu_items_[4]->InsertHudMsg(L"Siatka powinna byæ" 
											" minimum 1 x 1, maximum 600 x 600." 
											" Nie polecam wiêkszych wartoœci ni¿" 
											" 50 x 50.", sf::Vector2f(10, 15));
							menu_items_[4]->GetHudMessages()[0]->SetMessageFontSize(12);
						}
							break;
					}
				}
			}

			break;
		}
		default:
			break;
		}
	}
}



MenuState::~MenuState()
{
}
