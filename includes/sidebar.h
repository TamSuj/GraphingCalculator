#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "graph_info.cpp"

using namespace std;

class Sidebar
{
public:
    Sidebar();
    Sidebar(float left, float width, graph_info* info_ptr);
    void draw(sf::RenderWindow& window);
    bool handleEvent(sf::RenderWindow& window, sf::Event event);
    string& operator [](int index);
private:
    sf::RectangleShape rect;            //sidebar rectangle
    vector<string> items;               //strings to place on the sidebar
    sf::Font font;                      //used to draw text
    sf::Text sb_text;                   //used to draw strings on the window object
    sf::Text help_text;                 //used to tell user how to use calculator (which keyboard to press)

    sf::RectangleShape instruction;
    sf::RectangleShape helpButton;
    sf::Text buttonText;

    bool help;
    bool isButtonPressed;

    float _left;
    float _width;
    constexpr static double VERTICAL_LINE_SPACING = 15.0;

    graph_info* info;


};

#endif // SIDEBAR_H
