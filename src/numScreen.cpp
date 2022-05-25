#include "numScreen.h"
#include <iostream>

NumScreen::NumScreen()
{
    font.loadFromFile("resources/font.ttf");
    text.setFont(font);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::Red);
    text.setScale(1, 1.263);
    backgroundTexture.loadFromFile("resources/numBackground.jpg");
    background.setTexture(backgroundTexture);
    background.setScale(1, 1.263);
}

NumScreen::~NumScreen(){}
