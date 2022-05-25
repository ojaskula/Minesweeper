#ifndef SPOT_INCLUDE
#define SPOT_INCLUDE
#include <SFML/Graphics.hpp>

class Spot : public sf::Sprite //single spot on the game board
{
private:
    bool bomb;
    bool visible;
    bool flag;
    unsigned int index;
    bool loosingOne;
public:
    Spot(bool, bool, bool);
    Spot();
    ~Spot();
    void setVisible(bool);
    bool getVisible();
    void setBomb(bool);
    bool getBomb();
    void setFlag(bool);
    bool getFlag();
    void increaseIndex();
    unsigned int getIndex();
    void setLoosingOne(bool);
    bool getLoosingOne();
};

#endif // SPOT_INCLUDE
