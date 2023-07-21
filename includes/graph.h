#ifndef GRAPH_H
#define GRAPH_H

#include <SFML/Graphics.hpp>
#include "graph_info.cpp"
#include "plot.h"

using namespace std;

//draw points using vector<vector2f>
class Graph
{

public:
    Graph() {}
    Graph(graph_info* info_ptr) : info(info_ptr), plot(info_ptr), shift_level(0,0) {}
    void Draw(sf::RenderWindow& window);
    void Update(int command);
    void set_info();

private:
    sf::CircleShape shape;
    vector<sf::Vector2f> points;
    sf::VertexArray axis;
    sf::VertexArray grid;

    double zoom_level = 1;
    sf::Vector2f shift_level;
    bool needUpdate = true;

    graph_info* info;

    plot plot;


};

#endif // GRAPH_H