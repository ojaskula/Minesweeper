#include "timer.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <string>

Timer::Timer(unsigned int width) : NumScreen()
{
    this->t = 0;
    text.setPosition(width*SPOT_SIZE-89, 36);
    background.setPosition(width*SPOT_SIZE-89, 41);
}
Timer::Timer(){}

Timer::~Timer(){}

void Timer::update(bool start, bool EndGame)
{
    if(t < 999){
        if(start != true) clock.restart();
        if(start == true && EndGame == false)t = t + clock.restart().asSeconds();
    }
}

void Timer::Render(sf::RenderWindow& window, bool start, bool EndGame, unsigned int width)
{
    background.setPosition(width*SPOT_SIZE-89, 41);
    text.setPosition(width*SPOT_SIZE-89, 36);
    update(start, EndGame);
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(3) << std::fixed << std::setprecision(0) << t;
    std::string time = stream.str();
    text.setString(time);
    window.draw(background);
    window.draw(text);
}

void Timer::setTime(float time)
{
    this->t = time;
}

void Timer::Save()
{
    std::fstream out_file;
    out_file.open("save/timer.dot", std::ios_base::out | std::ios_base::binary);
    if(out_file.is_open()) out_file << t;
    else{std::exit(EXIT_FAILURE);}
}

void Timer::Load()
{
    clock.restart();
    std::fstream in_file;
    in_file.open("save/timer.dot", std::ios_base::in | std::ios_base::binary);
    if(in_file.is_open()){
        std::string time;
        std::getline(in_file, time);
        in_file.close();
        setTime(std::stof(time));
    }
    else{std::exit(EXIT_FAILURE);}
}
