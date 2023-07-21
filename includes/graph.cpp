#include "graph.h"
#include "constants.h"



void Graph::Draw(sf::RenderWindow& window){
    shape = sf::CircleShape(1);
    shape.setFillColor(sf::Color(177,221,241));	
    // shape.setFillColor(sf::Color(255, 99, 97)); //Pink 		
    shape.setPosition(sf::Vector2f(WORK_PANEL/2, SCREEN_HEIGHT/2));

    //grid
    grid = plot.grid();
    window.draw(grid);

    if(needUpdate){
        set_info();
        needUpdate = false;
    }

    for (const auto& position : points)
    {
        shape.setPosition(position);
        // Draw the circle.
        window.draw(shape);
    }

    //axis
    axis = plot.generateAxis();
    window.draw(axis);
    
}

void Graph::Update(int command){
    //update domain
    //received command from animate

    switch(command){
    case 1: //pan left
        info->shift.x -= 140;
        needUpdate = true;
        break;
    case 2: //pan right
        info->shift.x += 140;
        needUpdate = true;
        break;
    case 3: //pan up
        info->shift.y += 140;
        needUpdate = true;
        break;
    case 4: //pan down
        info->shift.y -= 140;
        needUpdate = true;
        break;
    case 5: //zoom in
        info->zoom /= 2;
        if(info->zoom <= 0.15)
            info->zoom *= 2;
        needUpdate = true;
        break;
    case 6: //zoom out
        info->zoom *= 2;
        if(info->zoom >= 8.5)
            info->zoom /= 2;
        needUpdate = true;
        break;
    case 10: //equation inputted
        needUpdate = true;
    default:
        break;

    }
}

void Graph::set_info(){
    points = plot();
    
}