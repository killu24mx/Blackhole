#include "../include/menu.h"

using namespace sf;


Button::Button(std::string text, int size, const Vector2f& position)
{
	this->font.loadFromFile("fonts/font.ttf");
	this->text.setFont(font);
	this->text.setFillColor(sf::Color::Blue);
	this->text.setString(text);
	this->text.setCharacterSize(size);
	this->text.setPosition(position);
	this->wasHovered = false;
	this->form.setPosition(this->text.getPosition().x - 10 * Desktop::k_x(), this->text.getPosition().y - 10 * Desktop::k_y());

	Vector2f size_vec(text.size() * size - 120 * ::Desktop::k_x(), size + 40 * Desktop::k_y());
	this->form.setSize(size_vec);
	this->form.setFillColor(Color::White);
	
}

bool Button::wasClicked(Sprite& cursor)
{
	if (this->text.getGlobalBounds().intersects(cursor.getGlobalBounds()))
		if (Mouse::isButtonPressed(Mouse::Left))
			return true;
			
   return false;
}

void Button::checkHovered(Sprite& cursor)
{
	
	Vector2f mouse_pos((float)Mouse::getPosition().x,(float)Mouse::getPosition().y);
	
	cursor.setPosition(mouse_pos);
	
	if (this->form.getGlobalBounds().intersects(cursor.getGlobalBounds()))
	{
		if (!wasHovered)
		{
			this->text.setCharacterSize(this->text.getCharacterSize() + 10 * Desktop::k_y());
			this->text.setFillColor(Color::White);
			wasHovered = true;
		}
		
	}

	else
	{
		if (wasHovered)
		{
			this->text.setCharacterSize(this->text.getCharacterSize() - 10 * Desktop::k_y());
			this->text.setFillColor(Color::Blue);
			wasHovered = false;
		}
		
	}
	
}

sf::Text Button::get_text()
{
    return text;
}

StartMenu::StartMenu(){
	this->background = new Background();
	this->cursor_texture.loadFromFile("sprites/cursor.png");
	this->cursor.setTexture(cursor_texture);

	list_of_buttons.push_back(new Button("Start", 80 * Desktop::k_y(), Vector2f(650 * Desktop::k_x(), 250 * Desktop::k_y())));
    list_of_buttons.push_back(new Button("Exit", 80 * Desktop::k_y(), Vector2f(675 * Desktop::k_x(), 800 *  Desktop::k_y())));
    list_of_buttons.push_back(new Button("Statistic", 80 *Desktop::k_y(), Vector2f(575 * Desktop::k_x(), 400 * Desktop::k_y())));

}


StartMenu::StartMenuExitCode StartMenu::update()
{
	sf::Clock timer;

    int delta = 0;
    int time = 0;



	while (window->isOpen())
	{
		int new_time = timer.getElapsedTime().asMilliseconds() * GameParametrs::default_game_speed;
		delta = new_time - time;
		time = new_time;
		
		

		Event event;

		for (int i = 0; i < list_of_buttons.size(); i++)
			list_of_buttons[i]->checkHovered(cursor);

		while (window->pollEvent(event))
			if (event.type == Event::Closed)
				window->close();

			
	
		if (list_of_buttons[0]->wasClicked(cursor))
			  return StartMenu::StartMenuExitCode::START;
		
	      
	
		if (list_of_buttons[1]->wasClicked(cursor))
			return StartMenu::StartMenuExitCode::EXIT;
		
		
		window->clear(Color::Black);
		background->update(delta);
		draw_background(background,window);
		draw_buttons();
		
			
		window->draw(cursor);
		window->display();
	
	}

	return StartMenu::StartMenuExitCode::EXIT;
	
}



Lose_menu::Lose_menu()
{
	this->cursor_texture.loadFromFile("sprites/cursor.png");
	this->cursor.setTexture(cursor_texture);

	list_of_buttons.push_back(new Button("Menu", 80 * Desktop::k_y(), Vector2f(675 * Desktop::k_x(), 350 * Desktop::k_y())));
    list_of_buttons.push_back(new Button("Exit", 80 * Desktop::k_y(), Vector2f(700 * Desktop::k_x(), 800 * Desktop::k_y())));

}
Lose_menu::LoseMenuExitCode Lose_menu::update()
{
	for (int i = 0; i < list_of_buttons.size(); i++)
		list_of_buttons[i]->checkHovered(cursor);

	
	if (list_of_buttons[0]->wasClicked(cursor))
		return Lose_menu::LoseMenuExitCode::MENU;

	if (list_of_buttons[1]->wasClicked(cursor))
		return Lose_menu::LoseMenuExitCode::EXIT;

	
	draw_buttons();
	window->draw(cursor);


	window->display();
	
	return Lose_menu::LoseMenuExitCode::SKIP;

}


Stop_menu::Stop_menu()
{
	this->cursor_texture.loadFromFile("sprites/cursor.png");
	this->cursor.setTexture(cursor_texture);
	list_of_buttons.push_back(new Button("Continue", 80 * Desktop::k_y(), Vector2f(650 * Desktop::k_x(), 250 * Desktop::k_y())));
    list_of_buttons.push_back(new Button("Menu", 80 * Desktop::k_y(), Vector2f(750 * Desktop::k_x(), 400 * Desktop::k_y())));
    list_of_buttons.push_back(new Button("Exit", 80 * Desktop::k_y(), Vector2f(780 * Desktop::k_x(), 800 * Desktop::k_y())));

  
}

Stop_menu::StopMenuExitCode Stop_menu::update()
{
	for (int i = 0; i < list_of_buttons.size(); i++)
		list_of_buttons[i]->checkHovered(cursor);

	
	if (list_of_buttons[0]->wasClicked(cursor))
		return Stop_menu::StopMenuExitCode::CONTINUE;
	
		
	
	if (list_of_buttons[1]->wasClicked(cursor))
		return Stop_menu::StopMenuExitCode::MENU;
	
		
	if (list_of_buttons[2]->wasClicked(cursor))
		window->close();
	
		
		
	draw_buttons();
	window->draw(cursor);
		
	
	
	return Stop_menu::StopMenuExitCode::SKIP;
}

Menu::~Menu()
{
	while(list_of_buttons.size()){
		delete list_of_buttons[0];
		list_of_buttons.erase(list_of_buttons.begin());
	}
}

void Menu::draw_buttons()
{
	for(auto* button : list_of_buttons){
		window->draw(button->get_text());
	}
}

StartMenu &StartMenu::get_instance()
{
    static StartMenu menu;
	return menu;
}


Lose_menu &Lose_menu::get_instance()
{
    static Lose_menu menu;
	return menu;
}

Stop_menu& Stop_menu::get_instance()
{
	static Stop_menu menu;
	return menu;
}
