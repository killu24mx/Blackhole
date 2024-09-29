#ifndef _SCORE_H_
#define _SCORE_H_

#include "entity.h"



class Score{
public:
    Score(const int& score);
    Score(const std::string& path,const int& score);

    void set_red_color();
    void set_blue_color();

    bool load_font(const std::string& path);

    friend void draw_score_text(Score* score,sf::RenderWindow* window);


private:
    const int& score;
    sf::Text text;
    sf::Font font;

};




#endif