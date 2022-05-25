#ifndef GAME_INCLUDE
#define GAME_INCLUDE
#include <SFML/Graphics.hpp>
#include "board.h"
#include "timer.h"
#include "counter.h"
#include "faceButton.h"
#include "menu.h"
#define INITIAL_W 9
#define INITIAL_H 9

class Game //menage all other class and game functionality
{
private:
    sf::RenderWindow window;
    Board board;
    Timer timer;
    Counter counter;
    FaceButton facebutton;
    Button menubutton;
    Menu menu;
    bool isOpen;
    int width;
    int height;
    int numOfBombs;
    bool isMenuOpen;
public:
    Game();
    ~Game();
    void CheckFiles();
    void HandleInput();
    void Close();
    void ResetGame(unsigned int, unsigned int, unsigned int);
    void ResetGame();
    void Menu_LeftButtonPressed();
    void Menu_LeftButtonReleased();
    void Game_LeftButtonPressed();
    void Game_LeftButtonReleased();
    void Menu_setUnclicked();
    void Game_setUnclicked();
    void Render();
    bool isWindowOpen();
    bool EndGame();
    void Save();
    void Load();
};

#endif // GAME_INCLUDE
