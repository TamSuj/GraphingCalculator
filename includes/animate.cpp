#include "animate.h"
#include "constants.h"
#include <iostream>
using namespace std;

animate::animate(): info(new graph_info())
{
    system = System(info);
     sidebar = Sidebar(WORK_PANEL, SIDE_BAR, info);
    
    cout<<"animate CTOR: TOP"<<endl;
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Calculator | Tammy Sujaritchai");
    window.setFramerateLimit(60);
    // window.setFramerateLimit(200);

    cout<<"Loading font."<<endl;

    if (!font.loadFromFile("/Users/tammy/Documents/GitHub/99_00_final_project-TamSuj/arial.ttf")){
        cout<<"animate() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }

    FunctionLabel = sf::Text("f(x) = ", font);
    FunctionLabel.setCharacterSize(27);
    FunctionLabel.setStyle(sf::Text::Bold);
    FunctionLabel.setFillColor(sf::Color::White);
    FunctionLabel.setPosition(sf::Vector2f(35, SCREEN_HEIGHT-myTextLabel.getLocalBounds().height-55));

    myTextLabel = sf::Text(info->equation, font);
    myTextLabel.setCharacterSize(27);
    myTextLabel.setStyle(sf::Text::Bold);
    myTextLabel.setFillColor(sf::Color::White);
    myTextLabel.setPosition(sf::Vector2f(125, SCREEN_HEIGHT-myTextLabel.getLocalBounds().height-30));

    cout<<"animate instantiated successfully."<<endl;
}

void animate::Draw(){
    system.Draw(window);
     sidebar.draw(window);

    //drawing Test: . . . . . . . . . . . .
    //This is how you draw text:)
    window.draw(FunctionLabel);
    window.draw(myTextLabel);
}

void animate::update(){
    //cause changes to the data for the next frame
    system.Step(command);
    command = 0;
}
void animate::render(){
    window.clear();
    Draw();
    window.display();
    
}



void animate::processEvents()
{
   sf::Event event;
   while (window.pollEvent(event))
    {
        // check the type of the event...
        switch (event.type)
        {
            // window closed
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::TextEntered:
            {
                //I Googled
                if (event.text.unicode == '\b' && inputString.size() > 0) // Handle backspace
                {
                    inputString.erase(inputString.size() - 1);
                    myTextLabel.setString(inputString);
                }
                else if (event.text.unicode < 128 && event.text.unicode != '\r' && event.text.unicode != ' '
                && !sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) // Handle input
                {
                    inputString += static_cast<char>(event.text.unicode);
                    myTextLabel.setString(inputString);
                }
            }

            // key pressed
            case sf::Event::KeyPressed:
                switch(event.key.code){
                case sf::Keyboard::Left: //pan left
                    command = 1;
                    cout << "LEFT ARROW" << endl;
                    break;
                case sf::Keyboard::Right: //pan right
                    command = 2;
                    cout << "RIGHT ARROW" << endl;
                    break;
                case sf::Keyboard::Up: //pan upward
                    command = 3;
                    cout << "UP ARROW" << endl;
                    break;
                case sf::Keyboard::Down: //pan downward
                    command = 4;
                    cout << "DOWN ARROW" << endl;
                    break;
                case sf::Keyboard::Space: //zoom in
                    command = 5;
                    cout << "ZOOM IN" << endl;
                    break;
                case sf::Keyboard::RShift: //zoom out
                    command = 6;
                    cout << "ZOOM OUT" << endl;
                    break;
                case sf::Keyboard::LControl: //zoom out
                    command = 6;
                    cout << "ZOOM OUT" << endl;
                    break;
                case sf::Keyboard::Return: //user done inputting
                    command = 10;
                    cout << "input equation: " << inputString << endl;
                    info->set_equation(inputString);
                    myTextLabel.setString(info->equation);
                    break;
                case sf::Keyboard::Escape:
                    window.close();
                break;
                }

                default:
                    break;

            myTextLabel.setString(info->equation);
        }
        //event handler for sidebar
        if (sidebar.handleEvent(window, event)) {
            command = 10;
            myTextLabel.setString(info->equation);
        }
    }
       
}
void animate::run()
{
   while (window.isOpen())
   {
       processEvents();
       update();
       render(); //clear/draw/display
   }
   cout << endl<<"-------ANIMATE MAIN LOOP EXITING ------------"<<endl;
}
