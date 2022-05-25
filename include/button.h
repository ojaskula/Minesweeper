#ifndef BUTTON_INCLUDE
#define BUTTON_INCLUDE
#include <SFML/Graphics.hpp>
#include <iostream>
#define SPOT_SIZE 32

class Button //single button and its actions
{
private:
    sf::Texture texture;
    sf::Text text;
    sf::Font font;
    sf::Sprite button;
    bool clicked;
    int height;
public:
    Button(unsigned int, unsigned int, std::string);
    Button();
    ~Button();
    void setTexture(unsigned int);
    void Render(sf::RenderWindow&, unsigned int);
    void setClicked(bool);
    bool Click(sf::Vector2i);
};

#endif // BUTTON_INCLUDE
