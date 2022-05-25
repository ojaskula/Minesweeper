#include "game.h"
#include <fstream>

Game::Game() : window(sf::VideoMode(INITIAL_W*SPOT_SIZE+10, INITIAL_H*SPOT_SIZE+105), "Minesweeper", sf::Style::Close),
    timer(INITIAL_W), counter(INITIAL_W, numOfBombs, board.numOfFlags()), facebutton(INITIAL_W),
    menubutton(INITIAL_W, 5, "MENU"), menu(INITIAL_W)
{
    CheckFiles();
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);
    sf::Image icon;
    icon.loadFromFile("resources/icon.jpg");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    height = 9;
    width = 9;
    numOfBombs = 10;
    isOpen = true;
    isMenuOpen = true;
}

Game::~Game(){}

void Game::CheckFiles()
{
    sf::Texture texture;
    sf::Font font;
    try{
        if(!texture.loadFromFile("resources/faceTexture.jpg")) throw "faceTexture.jpg missing";
        else if(!texture.loadFromFile("resources/icon.jpg")) throw "icon.jpg missing";
        else if(!texture.loadFromFile("resources/logo.png")) throw "logo.png missing";
        else if(!texture.loadFromFile("resources/numBackground.jpg")) throw "numBackground.jpg missing";
        else if(!texture.loadFromFile("resources/button.jpg")) throw "button.jpg missing";
        else if(!texture.loadFromFile("resources/texture.jpg")) throw "texture.jpg missing";
        else if(!font.loadFromFile("resources/font.ttf")) throw "font.ttf missing";
    }
    catch(const char* exeption){
        std::cout << exeption << std::endl;
        std::exit(EXIT_FAILURE);
        }
}

void Game::HandleInput()
{
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed) Close();
        else if(event.type == sf::Event::Resized){
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window.setView(sf::View(visibleArea));
        }
        else if(isMenuOpen == false){
            if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){
                Game_LeftButtonReleased();
            }
            else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                Game_LeftButtonPressed();
            }
            else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right){
                if(EndGame() == false)board.setFlag(sf::Mouse::getPosition(window));
                board.setTextures();
            }
        }
        else if(isMenuOpen == true){
            if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){
                Menu_LeftButtonReleased();
            }
            else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                Menu_LeftButtonPressed();
            }
        }
    }
}

void Game::Close()
{
    if(isMenuOpen == false) Save();
    window.close();
    isOpen = false;
    board.clearList();
}

void Game::Game_LeftButtonReleased()
{
    if(EndGame() == false && board.getStart() == false && board.setFirstSpot(sf::Mouse::getPosition(window)) == true){
        board.fillBoard(height, width, numOfBombs);
        board.Reveal(sf::Mouse::getPosition(window));
        board.setTextures();
    }
    else if(EndGame() == false){
        board.Reveal(sf::Mouse::getPosition(window));
        board.setTextures();
    }
    if(facebutton.ResetGame(sf::Mouse::getPosition(window)) == true){
        board.clearList();
        ResetGame();
    }
    if(menubutton.Click(sf::Mouse::getPosition(window)) == true){
        Save();
        width = 9;
        height = 9;
        window.setSize(sf::Vector2u(width*SPOT_SIZE+10, height*SPOT_SIZE+105));
        isMenuOpen = true;
        board.clearList();
    }
    if(EndGame() == true) board.setTextures();
    Game_setUnclicked();
    Menu_setUnclicked();
}

void Game::Game_LeftButtonPressed()
{
    if(board.Click(sf::Mouse::getPosition(window)) == true){
        facebutton.setBoardClick(true);
        facebutton.setTexture(board.Won(), board.Lost(), width);
    }
    else if(facebutton.Click(sf::Mouse::getPosition(window)) == true){
        facebutton.setClicked(true);
        facebutton.setTexture(board.Won(), board.Lost(), width);
    }
    else if(menubutton.Click(sf::Mouse::getPosition(window)) == true){
        menubutton.setClicked(true);
        menubutton.setTexture(width);
    }
}

void Game::Menu_LeftButtonReleased()
{
    if(menu.beginner.Click(sf::Mouse::getPosition(window)) == true){
        ResetGame(9, 9, 10);
    }
    else if(menu.intermediate.Click(sf::Mouse::getPosition(window)) == true){
        ResetGame(16, 16, 40);
    }
    else if(menu.expert.Click(sf::Mouse::getPosition(window)) == true){
        ResetGame(30, 16, 99);
    }
    else if(menu.resume.Click(sf::Mouse::getPosition(window)) == true){
        isMenuOpen = false;
        Load();
        Game_setUnclicked();
    }
    Menu_setUnclicked();
}

void Game::ResetGame(unsigned int width, unsigned int height, unsigned int numOfBombs)
{
    this->width = width;
    this->height = height;
    this->numOfBombs = numOfBombs;
    ResetGame();
}

void Game::Menu_LeftButtonPressed()
{
    if(menu.beginner.Click(sf::Mouse::getPosition(window)) == true){
        menu.beginner.setClicked(true);
        menu.beginner.setTexture(width);
    }
    else if(menu.intermediate.Click(sf::Mouse::getPosition(window)) == true) {
        menu.intermediate.setClicked(true);
        menu.intermediate.setTexture(width);
    }
    else if(menu.expert.Click(sf::Mouse::getPosition(window)) == true) {
        menu.expert.setClicked(true);
        menu.expert.setTexture(width);
    }
    else if(menu.resume.Click(sf::Mouse::getPosition(window)) == true) {
        menu.resume.setClicked(true);
        menu.resume.setTexture(width);
    }
}

void Game::Menu_setUnclicked()
{
    menu.beginner.setClicked(false);
    menu.intermediate.setClicked(false);
    menu.expert.setClicked(false);
    menu.resume.setClicked(false);
    menu.beginner.setTexture(width);
    menu.intermediate.setTexture(width);
    menu.expert.setTexture(width);
    menu.resume.setTexture(width);
}

void Game::Game_setUnclicked()
{
    facebutton.setClicked(false);
    facebutton.setBoardClick(false);
    menubutton.setClicked(false);
    facebutton.setTexture(board.Won(), board.Lost(), width);
    menubutton.setTexture(width);
}

void Game::Render()
{
    window.clear(sf::Color(220, 220, 220));
    if(isMenuOpen == false){
        counter.Render(window, numOfBombs, board.numOfFlags());
        facebutton.Render(window, width);
        timer.Render(window, board.getStart(), EndGame(), width);
        menubutton.Render(window, width);
        board.Render(window);
    }
    else{menu.Render(window, width);}
    window.display();
}

bool Game::isWindowOpen()
{
    return isOpen;
}

bool Game::EndGame()
{
    if(board.Lost() != true && board.Won() != true) return false;
    else{return true;}
}

void Game::ResetGame()
{
    window.setSize(sf::Vector2u(width*SPOT_SIZE+10, height*32+105));
    isMenuOpen = false;
    board.setStart(false);
    board.CreateBoard(height, width);
    timer.setTime(0);
    counter.setNumCounted(numOfBombs);
    Menu_setUnclicked();
    Game_setUnclicked();
}

void Game::Save()
{
    board.Save();
    timer.Save();
    std::fstream out_file;
    out_file.open("save/game.dot", std::ios_base::out | std::ios_base::binary);
    if(out_file.is_open()){
        out_file << width << std::endl << height << std::endl << numOfBombs;
    }
    else{std::exit(EXIT_FAILURE);}
}

void Game::Load()
{
    std::fstream in_file;
    in_file.open("save/game.dot", std::ios_base::in | std::ios_base::binary);
    if(in_file.is_open()){
        std::string w, h, n;
        std::getline(in_file, w);
        std::getline(in_file, h);
        std::getline(in_file, n);
        in_file.close();
        this->width = std::stoi(w);
        this->height = std::stoi(h);
        this->numOfBombs = std::stoi(n);
    }
    else{std::exit(EXIT_FAILURE);}
    board.Load(height, width);
    timer.Load();
    board.setTextures();
    window.setSize(sf::Vector2u(width*SPOT_SIZE+10, height*SPOT_SIZE+105));
}
