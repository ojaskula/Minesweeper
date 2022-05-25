#include "counter.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Counter::Counter(unsigned int width, unsigned int numOfBombs, int numOfFlags) : NumScreen()
{
    this->numCounted = numOfBombs;
    text.setPosition(15, 36);
    background.setPosition(15, 41);
}

Counter::Counter(){}

Counter::~Counter(){}

void Counter::update(int numOfFlags, int numOfBombs)
{
    numCounted = numOfBombs - numOfFlags;
}

void Counter::Render(sf::RenderWindow& window, int numOfBombs, int numOfFlags)
{
    update(numOfFlags, numOfBombs);
    std::stringstream stream;
    if(numCounted >= 0){
        if(numCounted > 999)numCounted = 999;
        stream << std::setfill('0') << std::setw(3) << std::fixed << std::setprecision(0) << numCounted;
    }
    else{
        if(numCounted < -99)numCounted = -99;
        stream << '-' << std::setfill('0') << std::setw(2) << std::fixed << std::setprecision(0) << numCounted * (-1);
    }
    std::string counted = stream.str();
    text.setString(counted);
    window.draw(background);
    window.draw(text);
}

void Counter::setNumCounted(int num)
{
    this->numCounted = num;
}
