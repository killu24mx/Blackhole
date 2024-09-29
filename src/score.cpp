#include "../include/score.h"
#include "score.h"

Score::Score(const int &score) : score(score),text(),font()
{
   
}

Score::Score(const std::string &path, const int &score) : Score(score)
{
    if(load_font(path)){
        std::cout << "font loaded" << std::endl;
    }
    text.setCharacterSize(40 * Desktop::k_y());
    text.setFillColor(sf::Color::Blue);
    text.setFont(font);
}

void Score::set_red_color()
{
    text.setFillColor(sf::Color::Red);
}

void Score::set_blue_color()
{
    text.setFillColor(sf::Color::Blue);
}

bool Score::load_font(const std::string& path)
{
    
    if(!font.loadFromFile(path)){
        return false;
    }
    text.setString("You score: " + std::to_string(this->score));
    text.setFillColor(sf::Color::Blue);
    return true;


}
void draw_score_text(Score *score_text, sf::RenderWindow *window)
{
    score_text->text.setString("You score: " + std::to_string(score_text->score));
    window->draw(score_text->text);
}
