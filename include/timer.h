#ifndef TIMER_INCLUDE
#define TIMER_INCLUDE
#include <SFML/Graphics.hpp>
#include "numScreen.h"

class Timer : public NumScreen //game timer, inherited from numScreen class
{
private:
    sf::Clock clock;
    float t;
public:
    explicit Timer(unsigned int);
    Timer();
    ~Timer();
    void update(bool, bool);
    void Render(sf::RenderWindow&, bool, bool, unsigned int);
    void setTime(float);
    void Save();
    void Load();
};

#endif // TIMER_INCLUDE
