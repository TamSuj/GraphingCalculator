#include "system.h"
#include "random.h"
#include <iostream>

#include "constants.h"

//manage domain, zoom, pan
System::System(graph_info* info_ptr) : graph(info_ptr), info(info_ptr) { 
    graph = Graph(info_ptr);
    info = info_ptr;
}


//------------------------------------------------------------------
//------------------------------------------------------------------

void System::Step(int command){
    graph.Update(command);
}


void System::Draw(sf::RenderWindow& window){
    graph.Draw(window);

}
