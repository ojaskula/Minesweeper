#ifndef NUMSCREEN_INCLUDE
#define NUMSCREEN_INCLUDE
#include <SFML/Graphics.hpp>
#define SPOT_SIZE 32

class NumScreen //pure virtual class with numerical screen, used for inheritance
{
protected:
    sf::Font font;
    sf::Text text;
    sf::Sprite background;
    sf::Texture backgroundTexture;
    NumScreen();
    virtual ~NumScreen() = 0;
};

#endif // NUMSCREEN_INCLUDE
