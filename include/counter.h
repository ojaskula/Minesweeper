#ifndef COUNTER_INCLUDE
#define COUNTER_INCLUDE
#include <SFML/Graphics.hpp>
#include "numScreen.h"

class Counter : public NumScreen //bombs counter displayed on game screen, inherited from numScreen class
{
private:
    int numCounted;
public:
    Counter(unsigned int, unsigned int, int);
    Counter();
    ~Counter();
    void update(int, int);
    void Render(sf::RenderWindow& window, int, int);
    void setNumCounted(int);
};

#endif // COUNTER_INCLUDE
