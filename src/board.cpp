#include "board.h"
#include <time.h>
#include <fstream>

Board::Board(unsigned int height, unsigned int width)
{
    clearList();
    firstSpot = 0;
    start = false;
    CreateBoard(height, width);
}

Board::Board(){}

Board::~Board(){}

void Board::fillBoard(unsigned int height, unsigned int width, unsigned int numOfBombs)
{
    drawBombs(height, width, numOfBombs);
    placeBombs();
    checkIndexes();
}

bool Board::setFirstSpot(sf::Vector2i mousePos)
{
    sf::RectangleShape point(sf::Vector2f(1, 1));
    point.setPosition(mousePos.x, mousePos.y);
    for(unsigned int i=0; i<spotList.size(); i++){
        if(point.getGlobalBounds().intersects(spotList[i].getGlobalBounds()) && spotList[i].getFlag() == false){
            firstSpot = i;
            return true;
        }
    }
    return false;
}

void Board::drawBombs(unsigned int height, unsigned int width, unsigned int numOfBombs)
{
    srand(time(NULL));
    for(unsigned int i=0; i<numOfBombs; i++){
        bombList.push_back(rand() % (height * width));
        while(bombList[i] == firstSpot) bombList[i] = rand() % (height * width);
        for(unsigned int j=0; j<i; j++){
            while(bombList[i] == bombList[j] || bombList[i] == firstSpot){
                bombList[i] = rand() % (height * width);
                j = 0;
            }
        }
    }
}

void Board::placeBombs()
{
    for(unsigned int i=0; i<spotList.size(); i++){
        for(unsigned int j=0; j<bombList.size(); j++){
            if(bombList[j] == i) spotList[i].setBomb(true);
        }
    }
}

void Board::CreateBoard(unsigned int height, unsigned int width)
{
    hidden.loadFromFile("resources/texture.jpg", sf::IntRect(0, 0, 32, 32));
    unsigned int t = 0;
    for(unsigned int i=0; i<width; i++){
        unsigned int posX = i * SPOT_SIZE + 5;
        for(unsigned int j=0; j<height; j++){
            unsigned int posY = j * SPOT_SIZE + 100;
            spotList.push_back(Spot());
            spotList[t].setPosition(sf::Vector2f(posX, posY));
            spotList[t].setTexture(hidden);
            t++;
        }
    }
}

void Board::checkIndexes()
{
    sf::RectangleShape aroundBomb(sf::Vector2f(64, 64));
    for(unsigned int i=0; i<spotList.size(); i++){
        if(spotList[i].getBomb() == true){
            aroundBomb.setPosition(spotList[i].getPosition().x - 16, spotList[i].getPosition().y - 16);
            for(unsigned int j=0; j<spotList.size(); j++){
                if(spotList[j].getGlobalBounds().intersects(aroundBomb.getGlobalBounds())){
                    spotList[j].increaseIndex();
                }
            }
        }
    }
}

void Board::Render(sf::RenderWindow& window)
{
    for(unsigned int i=0; i<spotList.size(); i++) window.draw(spotList[i]);
}

void Board::Reveal(sf::Vector2i mousePos)
{
    sf::RectangleShape point(sf::Vector2f(1, 1));
    point.setPosition(mousePos.x, mousePos.y);
    for(unsigned int i=0; i<spotList.size(); i++){
        if(point.getGlobalBounds().intersects(spotList[i].getGlobalBounds()) && spotList[i].getFlag() == false){
            setStart(true);
            spotList[i].setVisible(true);
            if(spotList[i].getBomb() == true) spotList[i].setLoosingOne(true);
            if(spotList[i].getIndex() == 0) Reveal(spotList[i]);
        }
    }
}

void Board::setFlag(sf::Vector2i mousePos)
{
    sf::RectangleShape point(sf::Vector2f(1, 1));
    point.setPosition(mousePos.x, mousePos.y);
    for(unsigned int i=0; i<spotList.size(); i++){
        if(point.getGlobalBounds().intersects(spotList[i].getGlobalBounds())){
            if(spotList[i].getVisible() == false){
                if(spotList[i].getFlag() == false) spotList[i].setFlag(true);
                else if(spotList[i].getFlag() == true) spotList[i].setFlag(false);
            }
            break;
        }
    }
}

void Board::setTextures()
{
    hidden.loadFromFile("resources/texture.jpg", sf::IntRect(0, 0, 32, 32));
    flag.loadFromFile("resources/texture.jpg", sf::IntRect(0, 32, 32, 32));
    bomb.loadFromFile("resources/texture.jpg", sf::IntRect(0, 64, 32, 32));
    redBomb.loadFromFile("resources/texture.jpg", sf::IntRect(0, 192, 32, 32));
    eight.loadFromFile("resources/texture.jpg", sf::IntRect(0, 96, 32, 32));
    seven.loadFromFile("resources/texture.jpg", sf::IntRect(0, 128, 32, 32));
    six.loadFromFile("resources/texture.jpg", sf::IntRect(0, 160, 32, 32));
    five.loadFromFile("resources/texture.jpg", sf::IntRect(32, 0, 32, 32));
    four.loadFromFile("resources/texture.jpg", sf::IntRect(32, 32, 32, 32));
    three.loadFromFile("resources/texture.jpg", sf::IntRect(32, 64, 32, 32));
    two.loadFromFile("resources/texture.jpg", sf::IntRect(32, 96, 32, 32));
    one.loadFromFile("resources/texture.jpg", sf::IntRect(32, 128, 32, 32));
    blank.loadFromFile("resources/texture.jpg", sf::IntRect(32, 160, 32, 32));
    wrongFlag.loadFromFile("resources/texture.jpg", sf::IntRect(32, 192, 32, 32));
    for(unsigned int i=0; i<spotList.size(); i++){
        if(spotList[i].getVisible() == true){
            if(spotList[i].getBomb() == true && spotList[i].getLoosingOne() != true) spotList[i].setTexture(bomb);
            else if(spotList[i].getBomb() == true && spotList[i].getLoosingOne() == true) spotList[i].setTexture(redBomb);
            else if(spotList[i].getIndex() == 8) spotList[i].setTexture(eight);
            else if(spotList[i].getIndex() == 7) spotList[i].setTexture(seven);
            else if(spotList[i].getIndex() == 6) spotList[i].setTexture(six);
            else if(spotList[i].getIndex() == 5) spotList[i].setTexture(five);
            else if(spotList[i].getIndex() == 4) spotList[i].setTexture(four);
            else if(spotList[i].getIndex() == 3) spotList[i].setTexture(three);
            else if(spotList[i].getIndex() == 2) spotList[i].setTexture(two);
            else if(spotList[i].getIndex() == 1) spotList[i].setTexture(one);
            else if(spotList[i].getIndex() == 0) spotList[i].setTexture(blank);
        }
        else if(spotList[i].getFlag() == true) spotList[i].setTexture(flag);
        else{spotList[i].setTexture(hidden);}
        if(Lost() == true && spotList[i].getBomb() != true && spotList[i].getFlag() == true) spotList[i].setTexture(wrongFlag);
    }
}

void Board::Reveal(Spot& spot)
{
    std::vector<Spot> checkList;
    checkList.push_back(spot);
    sf::RectangleShape aroundBlank(sf::Vector2f(64, 64));
    while(checkList.size() > 0){
        aroundBlank.setPosition(checkList[0].getPosition().x - 16, checkList[0].getPosition().y - 16);
        for(unsigned int i=0; i<spotList.size(); i++){
            if(aroundBlank.getGlobalBounds().intersects(spotList[i].getGlobalBounds()) && spotList[i].getFlag() != true){
                if(spotList[i].getVisible() != true && spotList[i].getIndex() == 0){
                    checkList.push_back(spotList[i]);
                }
                spotList[i].setVisible(true);
            }
        }
        checkList.erase(checkList.begin());
    }
    checkList.clear();
}

bool Board::Won()
{
    unsigned int n = 0;
    for(unsigned int i=0; i<spotList.size(); i++){
        if(spotList[i].getVisible() == true && spotList[i].getBomb() != true) n++;
        else if(spotList[i].getVisible() != true && spotList[i].getBomb() == true) n++;
    }
    if(n == spotList.size()){
        for(unsigned int j=0; j<spotList.size(); j++){
            if(spotList[j].getVisible() != true){spotList[j].setFlag(true);}
        }
        return true;
    }
    else{return false;}
}

bool Board::Lost()
{
    bool n = false;
    for(unsigned int i=0; i<spotList.size(); i++){
        if(spotList[i].getVisible() == true && spotList[i].getBomb() == true){
            n = true;
            break;
        }
    }
    if(n == true){
        for(unsigned int j=0; j<spotList.size(); j++){
            if(spotList[j].getBomb() == true && spotList[j].getFlag() != true) spotList[j].setVisible(true);
        }
        return true;
    }
    else{return false;}
}

int Board::numOfFlags()
{
    int flags = 0;
    for(unsigned int i=0; i<spotList.size(); i++){
        if(spotList[i].getFlag() == true) flags++;
    }
    return flags;
}

void Board::setStart(bool start)
{
    this->start = start;
}

bool Board::getStart()
{
    return start;
}

void Board::clearList()
{
    spotList.clear();
    bombList.clear();
}

bool Board::Click(sf::Vector2i mousePos)
{
    sf::RectangleShape point(sf::Vector2f(1, 1));
    point.setPosition(mousePos.x, mousePos.y);
    for(unsigned int i=0; i<spotList.size(); i++){
        if(point.getGlobalBounds().intersects(spotList[i].getGlobalBounds())){
            return true;
        }
    }
    return false;
}

void Board::Save()
{
    std::fstream out_file;
    out_file.open("save/board.dot", std::ios_base::out | std::ios_base::binary);
    if(out_file.is_open()){
        for(unsigned int i=0; i<spotList.size(); i++){
            out_file << spotList[i].getBomb();
        }
        out_file << std::endl;
        for(unsigned int i=0; i<spotList.size(); i++){
            out_file << spotList[i].getVisible();
        }
        out_file << std::endl;
        for(unsigned int i=0; i<spotList.size(); i++){
            out_file << spotList[i].getFlag();
        }
        out_file << std::endl;
        out_file << start;
        out_file.close();
    }
    else{std::exit(EXIT_FAILURE);}
}

void Board::Load(unsigned int height, unsigned int width)
{
    clearList();
    std::fstream in_file;
    in_file.open("save/board.dot", std::ios_base::in | std::ios_base::binary);
    if(in_file.is_open()){
        std::string b, v, f, s;
        std::getline(in_file, b);
        std::getline(in_file, v);
        std::getline(in_file, f);
        std::getline(in_file, s);
        in_file.close();
        start = s[0] - '0';
        CreateBoard(height, width);
        for(unsigned int i=0; i<b.size(); i++){
            spotList[i].setBomb((int)b[i] - '0');
            spotList[i].setVisible((int)v[i] - '0');
            spotList[i].setFlag((int)f[i] - '0');
        }
    }
    else{std::exit(EXIT_FAILURE);}
    checkIndexes();
}
