#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H

#include <SFML/Graphics.hpp>
#include "constants.h"
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

class graph_info{

public:
    graph_info() : graph_info("((0.3*x)^2)+1") { }
    graph_info(string calculateMe) : domain(-5, 5), equation(calculateMe), shift(0,0){
        history.push_back("History");
        //sample equation
        history.push_back("cos(1/x)");
        history.push_back("x^3");
        history.push_back("tan(x)");
    }

    void set_equation(const string& Input){ 
        equation = Input;
        history.push_back(Input);
    }

    string get_domain(){ 
        double current_x = round(domain.x * zoom);
        double current_y = round(domain.y * zoom);

        string current_domain = "(" + to_string(current_x) + " , " + to_string(current_y) + ")";

        return current_domain;
    }

    void set_domain(float x, float y) {
        domain.x = x;
        domain.y = y;
    }
    string get_equation(){ return equation; }

    sf::Vector2f domain;
    string equation;

    double zoom = 1;
    sf::Vector2f shift;

    vector<string> history;

    vector<sf::Vector2f> points;
};

#endif