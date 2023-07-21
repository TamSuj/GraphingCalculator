#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "graph_info.cpp"
#include "graph.h"

using namespace std;
class System
{
public:
    System() {};
    System(graph_info* info_ptr);
    void Step(int command);
    int Size();
    void Draw(sf::RenderWindow& widnow);
private:
    Graph graph;
    graph_info* info;
    
};

#endif // SYSTEM_H
