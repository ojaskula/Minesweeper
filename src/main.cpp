#include <SFML/Graphics.hpp>
#include "game.h"

int main()
{
    Game game;
    while(game.isWindowOpen()){
        game.HandleInput();
        game.Render();
    }
    return 0;
}
