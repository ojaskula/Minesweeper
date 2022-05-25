#include "spot.h"
#include <iostream>

Spot::Spot()
{
    this->bomb = false;
    this->visible = false;
    this->flag = false;
    this->index = 0;
    this->loosingOne = false;
}

Spot::Spot(bool bomb, bool visible, bool flag)
{
    this->bomb = bomb;
    this->visible = visible;
    this->flag = flag;
    this->index = 0;
    this->loosingOne = false;
}

Spot::~Spot(){}

void Spot::setVisible(bool visible)
{
    this->visible = visible;
}

bool Spot::getVisible()
{
    return visible;
}

void Spot::setBomb(bool bomb)
{
    this->bomb = bomb;
}

bool Spot::getBomb()
{
    return bomb;
}

void Spot::setFlag(bool flag)
{
    this->flag = flag;
}

bool Spot::getFlag()
{
    return flag;
}

void Spot::increaseIndex()
{
    index++;
}

unsigned int Spot::getIndex()
{
    return index;
}

void Spot::setLoosingOne(bool loosingOne)
{
    this->loosingOne = loosingOne;
}

bool Spot::getLoosingOne()
{
    return loosingOne;
}
