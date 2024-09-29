#ifndef _MENU_H_
#define _MENU_H_

#include "entity.h"
#include "mainwindow.h"
#include "background.h"

class Button {
public:
	Button(std::string text, int size, const sf::Vector2f& position);
	bool wasClicked(sf::Sprite& cursor);
	void checkHovered(sf::Sprite& cursor);
	sf::Text get_text();
	
private:
	sf::Font font;
	sf::Vector2f position;
	int size;
	bool wasHovered;
	sf::Text text;
	sf::RectangleShape form;

};

class Menu
{
public:
	~Menu();
	void draw_buttons();

	void set_background(Background* back){
		if(this->background){
			delete this->background;
		}
		this->background = back;
	}

protected:
	std::vector<Button*> list_of_buttons;
	sf::Sprite cursor;
	sf::Texture cursor_texture;
	sf::RenderWindow* window = get_window();

	Menu() = default;
	Menu(const Menu& other) = default;
	Menu& operator=(const Menu& other) = default;
    
	Background* background = nullptr;
};

class StartMenu : public Menu {
public:

	enum class StartMenuExitCode{
		EXIT = 0,
		START = 1,
		STATISTIC = 2
	};
	StartMenuExitCode update();
	static StartMenu& get_instance();

	~StartMenu(){delete background;}

	

	StartMenu();

	
};

class Lose_menu : public Menu {
public:

	enum class LoseMenuExitCode{
		EXIT = 0,
		MENU = 1,
		SKIP = 2
	};
	LoseMenuExitCode update();
	static Lose_menu& get_instance();

	
	Lose_menu();
private: 
	
	
	
};

class Stop_menu: public Menu {
public:
	enum class StopMenuExitCode{
		EXIT = 0,
		CONTINUE = 1,
		MENU = 2,
		SKIP = 3
	};
	StopMenuExitCode update();
	static Stop_menu& get_instance();
	Stop_menu();
private:
	Background* background = nullptr;
};

#endif