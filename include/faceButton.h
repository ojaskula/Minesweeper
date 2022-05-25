#ifndef FACEBUTTON_INCLUDE
#define FACEBUTTON_INCLUDE
#include <SFML/Graphics.hpp>
# define SPOT_SIZE 32

class FaceButton //button with face texture displayed in the game screen and its actions
{
private:
    sf::Texture face;
    sf::Sprite button;
    bool clicked = false;
    bool boardClick = false;
public:
    explicit FaceButton(int);
    FaceButton();
    ~FaceButton();
    void setTexture(bool, bool, unsigned int);
    void Render(sf::RenderWindow&, unsigned int);
    bool ResetGame(sf::Vector2i);
    bool Click(sf::Vector2i);
    void setClicked(bool);
    void setBoardClick(bool);
};

#endif // FACEBUTTON_INCLUDE
