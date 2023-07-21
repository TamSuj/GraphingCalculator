#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "system.h"
#include "sidebar.h"
#include "graph_info.cpp"

class animate{
public:
    animate();
    void run();
    void processEvents();
    void update();
    void render();
    void Draw();

    string getInput(){ return inputString; }
private:
    sf::RenderWindow window;
    System system;                      //container for all the animated objects
    int command;                        //command to send to system
    sf::Font font;                      //font to draw on main screen
    sf::Text myTextLabel;               //text to draw on main screen
    sf::Text FunctionLabel;               //text to draw on main screen
    Sidebar sidebar;                    //rectangular message sidebar

    string inputString;
    sf::Text Domain;

    graph_info* info;

};

#endif // GAME_H
