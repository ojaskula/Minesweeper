#ifndef BOARD_INCLUDE
#define BOARD_INCLUDE
#include <iostream>
#include <SFML/Graphics.hpp>
#include "spot.h"
#define SPOT_SIZE 32

class Board //game board and its actions
{
private:
    std::vector<unsigned int> bombList;
    std::vector<Spot> spotList;
    sf::Texture hidden;
    sf::Texture flag;
    sf::Texture bomb;
    sf::Texture redBomb;
    sf::Texture eight;
    sf::Texture seven;
    sf::Texture six;
    sf::Texture five;
    sf::Texture four;
    sf::Texture three;
    sf::Texture two;
    sf::Texture one;
    sf::Texture blank;
    sf::Texture wrongFlag;
    bool start;
    unsigned int firstSpot;
public:
    Board(unsigned int, unsigned int);
    Board();
    ~Board();
    void fillBoard(unsigned int, unsigned int, unsigned int);
    void drawBombs(unsigned int, unsigned int, unsigned int);
    bool setFirstSpot(sf::Vector2i);
    int getFirstSpot();
    void placeBombs();
    void CreateBoard(unsigned int, unsigned int);
    void checkIndexes();
    void Render(sf::RenderWindow&);
    void Reveal(sf::Vector2i);
    void Reveal(Spot&);
    void setTextures();
    void setFlag(sf::Vector2i);
    bool Won();
    bool Lost();
    int numOfFlags();
    void setStart(bool);
    bool getStart();
    void clearList();
    bool Click(sf::Vector2i);
    void Save();
    void Load(unsigned int, unsigned int);
};

#endif // BOARD_INCLUDE
