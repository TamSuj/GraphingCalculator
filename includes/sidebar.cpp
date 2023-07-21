#include "sidebar.h"
#include "constants.h"

Sidebar::Sidebar() {}

Sidebar::Sidebar(float left, float width, graph_info *info_ptr) : _left(left), _width(width), info(info_ptr), help(false), buttonText("Help", font, 24), isButtonPressed(false) {

    cout << "Sidebar CTOR: TOP" << endl;
    items.reserve(50);

    //set up the sidebar rectangle:
    rect.setFillColor(sf::Color(39, 39, 39)); //(192,192,192)); //silver
    rect.setPosition(sf::Vector2f(left, 0));
    rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));
    cout << "Sidebar CTOR: about to load font." << endl;

    if (!font.loadFromFile("Roboto-Thin.ttf")) {
        cout << "Sidebar() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }
    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    cout << "Sidebar CTOR: loaded font." << endl;

    //. . . . . text / font problems: . . . . . . . .
    //initializing text object in this way caused problems
    // (hangs!)
    //only when sb_text was a private member and worked fine
    //when it was a public member. Probably not releavant,
    //but still strange!
    //
    //sb_text = sf::Text("Initial String for myTextLabel", font);
    //
    //. . . . . . . . . . . . . . . . . . . . . . . . .
    cout << "Sidebar CTOR: Text object initialized." << endl;
    sb_text.setFont(font);
    sb_text.setCharacterSize(24);
    sb_text.setStyle(sf::Text::Bold);
    sb_text.setFillColor(sf::Color::White);

    ////this is how you would position text on screen:
    //sb_text.setPosition(sf::Vector2f(10, SCREEN_HEIGHT-sb_text.getLocalBounds().height-5));

    items.push_back("History");
    //Fill the items vector with empty strings so that we can use [] to read them:
    for (int i = 0; i < 30; i++) {
        items.push_back("");
    }
    
    helpButton.setPosition(sf::Vector2f(SCREEN_WIDTH - 80, SCREEN_HEIGHT - 80));

    cout << "Sidebar: CTOR: Exit." << endl;
}

void Sidebar::draw(sf::RenderWindow &window) {

    const double LEFT_MARGIN = 15.0;

    window.draw(rect);
    window.draw(helpButton);

    // draw help_text if button is pressed
    window.draw(help_text); 

    float height = 10;

    //terminology: enhanced for loop
    for (const auto &eq: info->history) {
        bool blank = false;
        if (eq.length() == 0) {
            blank = true;
            sb_text.setString("BLANK");
        } else {
            sb_text.setString(eq);
//            sb_text.setString(it->c_str());
        }
        sb_text.setPosition(sf::Vector2f(_left + LEFT_MARGIN, height));
        height += sb_text.getCharacterSize() + VERTICAL_LINE_SPACING;
        if (!blank) {
            string tmp = sb_text.getString();
            sf::Text tmpText(tmp, font);
            tmpText.setPosition(sb_text.getPosition());
            tmpText.setCharacterSize(27);
            window.draw(tmpText);
//            window.draw(sb_text);
        }

    }
}

string &Sidebar::operator[](int index) {
    return items[index];
}

bool Sidebar::handleEvent(sf::RenderWindow &window, sf::Event event) {
    
    if (event.type == sf::Event::MouseButtonPressed) {

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (event.mouseButton.button == sf::Mouse::Left) {
            //get the mouse position
            
            //check if the mouse position is within the bounds of the sidebar (history of equations)
             //if mouse clicked, and the mouse position is at a valid history equation, set the equation to that equation
            if (mousePos.x >= _left && mousePos.x <= _left + _width) {
                //calculate the index of the eqa item string based on the position
                //initial height = 10, each line is character size + LINE_SPACING
                int index = (mousePos.y - 10) / (sb_text.getCharacterSize() + VERTICAL_LINE_SPACING);
                int size = info->history.size();
                if (index >= 1 && index < size) {
                    //set the equation to the equation at that index
                    info->equation = info->history[index];
                    // cout << "index: " << index<< endl;
                    cout << "Equation set to: " << info->equation << endl;
                    return true;
                }
            }

            //help button
            if (mousePos.x >= _left + _width - 70 && mousePos.x <= _left + _width - 20 &&
                mousePos.y >= SCREEN_HEIGHT - 70 && mousePos.y <= SCREEN_HEIGHT - 20) {
                // display help text
                help_text.setString("space: zoom in\nshift: zoom out\nClick on any key to enter input");
                cout << "help key pressed" << endl;
                // window.draw(help_text); // draw the help text
            }
        }
    }
    return false;
}
