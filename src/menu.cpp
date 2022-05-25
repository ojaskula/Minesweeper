#include "Menu.h"

Menu::Menu(unsigned int width) : resume(width, 160, "RESUME"), beginner(width, 240, "BEGINNER"),
    intermediate(width, 280, "INTERMEDIATE"),expert(width, 320, "EXPERT")
{
    texture.loadFromFile("resources/logo.png");
    logo.setPosition(sf::Vector2f(width*30/2 - 113, 0));
    logo.setTexture(texture);
    signature.setString("by O.J. PolSl 2020");
    font.loadFromFile("resources/font.ttf");
    signature.setFont(font);
    signature.setCharacterSize(8);
    signature.setColor(sf::Color::Black);
    signature.setPosition(180, 383);
}

Menu::Menu(){}

Menu::~Menu(){}

void Menu::Render(sf::RenderWindow& window, unsigned int width)
{
    window.draw(signature);
    window.draw(logo);
    resume.Render(window, width);
    beginner.Render(window, width);
    intermediate.Render(window, width);
    expert.Render(window, width);
}
