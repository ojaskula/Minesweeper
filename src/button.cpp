#include "button.h"

Button::Button(unsigned int width, unsigned int height, std::string str)
{
    font.loadFromFile("resources/font.ttf");
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setString(str);
    button.setPosition(width*SPOT_SIZE / 2 - 113, height);
    this->height = height;
    this->clicked = false;
    setTexture(width);
}

Button::Button(){}

Button::~Button(){}

void Button::setTexture(unsigned int width)
{
    if(clicked == false){
        texture.loadFromFile("resources/button.jpg", sf::IntRect(0, 32, 236, 32));
        text.setPosition(width*SPOT_SIZE/2 - ((text.getString().getSize()-1) * 14 - 2)/2, height + 5);
    }
    else{
        texture.loadFromFile("resources/button.jpg", sf::IntRect(0, 0, 236, 32));
        text.setPosition(width*SPOT_SIZE/2 - ((text.getString().getSize()-1) * 14 - 2)/2, height + 7);
    }
    button.setTexture(texture);
    button.setPosition(width*SPOT_SIZE/2 - 113, height);
}

bool Button::Click(sf::Vector2i mousePos)
{
    sf::RectangleShape point(sf::Vector2f(1, 1));
    point.setPosition(mousePos.x, mousePos.y);
    if(point.getGlobalBounds().intersects(button.getGlobalBounds())){
        setClicked(true);
        return true;
    }
    else{
        setClicked(false);
        return false;
    }
}

void Button::Render(sf::RenderWindow& window, unsigned int width)
{
    window.draw(button);
    window.draw(text);
}

void Button::setClicked(bool clicked)
{
    this->clicked = clicked;
}
