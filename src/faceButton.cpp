#include "faceButton.h"
#include <iostream>

FaceButton::FaceButton(int width)
{
    setTexture(false, false, width);
    button.setPosition(width*SPOT_SIZE/2 - 19, 41);
    clicked = false;
    boardClick = false;
}

FaceButton::FaceButton(){}

FaceButton::~FaceButton(){}

void FaceButton::setTexture(bool won, bool lost, unsigned int width)
{
    if(clicked == true){face.loadFromFile("resources/faceTexture.jpg", sf::IntRect(0, 0, 48, 48));}
    else if(won == true){face.loadFromFile("resources/faceTexture.jpg", sf::IntRect(0, 48, 48, 48));}
    else if(lost == true){face.loadFromFile("resources/faceTexture.jpg", sf::IntRect(0, 96, 48, 48));}
    else if(boardClick == true){face.loadFromFile("resources/faceTexture.jpg", sf::IntRect(0, 144, 48, 48));}
    else{face.loadFromFile("resources/faceTexture.jpg", sf::IntRect(0, 192, 48, 48));}
    button.setTexture(face);
    button.setPosition(width*SPOT_SIZE/2 - 19, 41);
}

void FaceButton::Render(sf::RenderWindow& window, unsigned int width)
{
    window.draw(button);
}

bool FaceButton::ResetGame(sf::Vector2i mousePos)
{
    sf::RectangleShape point(sf::Vector2f(1, 1));
    point.setPosition(mousePos.x, mousePos.y);
    if(point.getGlobalBounds().intersects(button.getGlobalBounds())){
        return true;
    }
    else{return false;}
}

bool FaceButton::Click(sf::Vector2i mousePos)
{
    sf::RectangleShape point(sf::Vector2f(1, 1));
    point.setPosition(mousePos.x, mousePos.y);
    if(point.getGlobalBounds().intersects(button.getGlobalBounds())){
        return true;
    }
    else{return false;}
}

void FaceButton::setClicked(bool clicked)
{
    this->clicked = clicked;
}

void FaceButton::setBoardClick(bool boardClick)
{
    this->boardClick = boardClick;
}
