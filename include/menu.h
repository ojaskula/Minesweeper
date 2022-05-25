#ifndef EMENU_INCLUDE
#define MENU_INCLUDE
#include "button.h"

class Menu //menu and its actions
{
private:
    friend class Game;
    Button resume;
    Button beginner;
    Button intermediate;
    Button expert;
    sf::Sprite logo;
    sf::Texture texture;
    sf::Text signature;
    sf::Font font;
public:
    explicit Menu(unsigned int);
    Menu();
    ~Menu();
    void Render(sf::RenderWindow&, unsigned int);
};


#endif // MENU_INCLUDE
