#ifndef PLOT_H
#define PLOT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.h"
#include "graph_info.cpp"
// #include "graph.h"

using namespace std;

class plot
{
public:
    plot() {}
    plot(graph_info* info_ptr) : info(info_ptr) {}
    sf::VertexArray generateAxis();
    sf::VertexArray grid();
    vector<sf::Vector2f> operator()();

    //convert cartesian to SFML coordinate
    sf::Vector2f toSFML(sf::Vector2f original);

private:
    //used for setting up y-axis and x-axis
    double y_int = 0;

    graph_info* info;
    double zoom, shift;
};

#endif