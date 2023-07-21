#include "plot.h"
#include <cmath>

#include "token/function.h"
#include "token/operator.h"
#include "token/integer.h"
#include "token/variable.h"
#include "token/leftparen.h"
#include "token/rightparen.h"
#include "shunting_yard/shunting_yard.h"
#include "rpn/rpn.h"

vector<sf::Vector2f> plot::operator()(){
    
    vector<sf::Vector2f> plot_points;
    Queue<Token*> calc;

    //------------------------------------------------
    // string input = "cos(1/x)";
    if(info == nullptr)
        throw invalid_argument("plot info = null");

    string input = info->get_equation();
    string var = "";

    vector<char> operators = {'+', '-', '*', '^', '/'};

    int i = 0;
    while(i < input.length()){
        // // cout << "index: " << i << endl;
        // // cout << "item: " << input[i] << endl;

        //Unary negative sign
        if(input[i] == '-' && i == 0 ) 
        {
            calc.push(new Integer("-1"));
            calc.push(new Operator("*"));
            // infix += "-1 * ";
            i++;
        }
        else if(input[i] == '-' && input[i+1] == '-'){
            calc.push(new Operator("+"));
            // infix += "+ ";
            i += 2;
        }else if(input[i] == '-' && input[i+1] == '+' || input[i] == '+' && input[i+1] == '-'){
            calc.push(new Operator("-"));
            // infix += "- ";
            i += 2;
        }else if(input[i] == '-' && input[i+1] == '('){
            calc.push(new Integer("-1"));
            calc.push(new Operator("*"));
            // infix += "-1 * ";
            i++;
        }

        if (isdigit(input[i])) //if integer
        {
            while(isdigit(input[i]) || input[i] == '.'){
                var += input[i];
                i++;
            }

            double num = stod(var);

            //if it's implicit multiplication
            // if(isalpha((input[i]) || input[i] == '(')){
            //     // cout << "explicit multiplication" << endl;
            //     calc.push(new Operator("*"));
            //     // infix += " * ";
            //     // cout << "pushing * " << endl;
            // }

            // cout << "I'm implementing " << stod(var) << endl;
            // infix += var;
            calc.push(new Integer(num));
        }
        else if(toupper(input[i]) == 'X' || toupper(input[i]) == 'Y') //if variable
        {
            //if it's a multiplication sign, not function
            //ex: 3x5

            //if front and back or x is a number, push * (implicit multiplication)
            if(isdigit(input[i-1]) || isdigit(input[i+1])){
                calc.push(new Operator("*"));
                calc.push(new Variable("X"));
                // cout << "pushing * X" << endl;
                // infix += " * X";
            }
            else{
                var += toupper(input[i]);

                calc.push(new Variable(var));
                // infix += var;
                // cout << "pushing " << var << endl;
            }
            i++;
        }
        else if(input[i] == '('){
            calc.push(new LeftParen());
            // cout << "pushing ( " << endl;
            i++;
        }
        else if(input[i] == ')'){
            calc.push(new RightParen());
            // cout << "pushing ) " << endl;
            i++;
        }
        else if(isalpha(input[i]))//if paren or function (ex: cos, sin, tan)
        {
            var += input[i];
            // infix += input[i];
            i++;

            while(isalpha(input[i]))
            {
                var += input[i];
                // infix += input[i];
                i++;
            }

            calc.push(new Function(var));
            // cout << "pushing " << var << endl;

        }else if(input[i] == ' ') //ignore whitespace
            i++;
        else{ //operators
            // cout << "Detected " << input[i] << " operator" << endl;

            auto it = find(operators.begin(), operators.end(), input[i]);

            if (it != operators.end()) {
                var += input[i];
                calc.push(new Operator(var));
                // infix += var;
            } else {
                throw "Invalid input";
            }
            i++;
        }
        var = "";
    }

    //------------------------------------

    // equa.push(new Operator("cos"));
    // equa.push(new LeftParen());
    // equa.push(new Integer("1"));
    // equa.push(new Operator("/"));
    // equa.push(new Variable("X"));
    // equa.push(new RightParen());

    ShuntingYard sy;
    Queue<Token*> postfix = sy.postfix(calc);   

    RPN rpn(postfix);  

    y_int = rpn(0.1) + info->shift.x;

    //--------------------------------
    sf::Vector2f plot_domain = info->domain;
    sf::Vector2f old_domain = plot_domain;

    plot_domain.x *= info->zoom;
    plot_domain.y *= info->zoom;

    //map cartesian to screen size
    int scale_factor = WORK_PANEL / (plot_domain.y - plot_domain.x);

    //shift left/right
    float min = plot_domain.x + info->shift.x;
    float max = plot_domain.y - info->shift.x;

    if(min > max){
        min = plot_domain.x - info->shift.x;
        max = plot_domain.y + info->shift.x;
    }

    // if(max - min >= 2 && max - min <= 150)
    // {    
        for (float x = min ; x <= max; x += 0.003f) {
            if(x != 0)
            {
                sf::Vector2f point(x * scale_factor, rpn(x) * scale_factor);
            
                //shift left/right/up/down
                point.x += info->shift.x;
                point.y += info->shift.y;

                plot_points.push_back(toSFML(point));
            }
        }
    //     info->points = plot_points;
    // }else{
    //     plot_points = info->points;
    // }

    return plot_points;
}

sf::VertexArray plot::generateAxis(){
    sf::VertexArray axis(sf::Lines, 10);

    // x-axis
    axis[0].position = sf::Vector2f(0, SCREEN_HEIGHT / 2 - info->shift.y);
    axis[1].position = sf::Vector2f(WORK_PANEL, SCREEN_HEIGHT / 2 - info->shift.y);

    //y-axis
    //change according to the graph and shift
    sf::Vector2f y_startPoint = toSFML(sf::Vector2f(y_int, 0));
    axis[2].position = sf::Vector2f(y_startPoint.x, 0);
    axis[3].position = sf::Vector2f(y_startPoint.x, SCREEN_HEIGHT);


    //[  -------Ticks-----------  ]
    std::vector<double> tick_x;
    std::vector<double> tick_y;

    // calculate tick for x-axis 
    // 1) from y-intercept to the right
    for(int i = y_startPoint.x; i <= WORK_PANEL; i += 170){
        tick_x.push_back(i);
    }
    // 2) from y-intercept to the left
    for(int i = y_startPoint.x; i >= 0; i -= 170){
        tick_x.push_back(i);
    }

    for (int i = 0; i < tick_x.size(); i++) {
        axis.append(sf::Vertex(sf::Vector2f(tick_x[i], (SCREEN_HEIGHT / 2) - 7 - info->shift.y)));
        axis.append(sf::Vertex(sf::Vector2f(tick_x[i], (SCREEN_HEIGHT / 2) + 7 - info->shift.y)));
    }

    //calculate tick for y-axis
    // 1) from y-intercept to the top
    for(int i = y_startPoint.y; i <= SCREEN_HEIGHT; i += 140){
        tick_y.push_back(i);
    }
    // 2) from y-intercept to the bottom
    for(int i = y_startPoint.y; i >= 0; i -= 140){
        tick_y.push_back(i);
    }

    //ticks on y-axis
    for (int i = 0; i < tick_y.size(); i++) {
        axis.append(sf::Vertex(sf::Vector2f(y_startPoint.x - 7, tick_y[i])));
        axis.append(sf::Vertex(sf::Vector2f(y_startPoint.x + 7, tick_y[i])));
    }

    //[  -------Ticks-----------  ]

    // Set the color of the lines to grey
    for (int i = 0; i < axis.getVertexCount(); i++) {
        axis[i].color = sf::Color(176, 176, 176);
    }

    return axis;
}

sf::VertexArray plot::grid(){
    sf::VertexArray grid(sf::Lines);

    sf::Vector2f y_startPoint = toSFML(sf::Vector2f(y_int, 0));

    std::vector<double> grid_x;
    std::vector<double> grid_y;

    // 1) from y-intercept to the right
    for(double i = y_startPoint.x; i <= WORK_PANEL; i += 42.5){
        grid_x.push_back(i);
    }
    // 2) from y-intercept to the left
    for(double i = y_startPoint.x; i >= 0; i -= 42.5){
        grid_x.push_back(i);
    }

    for (int i = 0; i < grid_x.size(); i++) {
        grid.append(sf::Vertex(sf::Vector2f(grid_x[i], 0)));
        grid.append(sf::Vertex(sf::Vector2f(grid_x[i], SCREEN_HEIGHT)));
    }

    //calculate tick for y-axis
    // 1) from y-intercept to the top
    for(int i = y_startPoint.y; i <= SCREEN_HEIGHT; i += 35){
        grid_y.push_back(i);
    }
    // 2) from y-intercept to the bottom
    for(double i = y_startPoint.y; i >= 0; i -= 35){
        grid_y.push_back(i);
    }

    //ticks on y-axis
    for (int i = 0; i < grid_y.size(); i++) {
        grid.append(sf::Vertex(sf::Vector2f(0, grid_y[i])));
        grid.append(sf::Vertex(sf::Vector2f(WORK_PANEL, grid_y[i])));
    }

    //[  -------Ticks-----------  ]

    // Set the color of the lines to grey
    for (int i = 0; i < grid.getVertexCount(); i++) {
        grid[i].color = sf::Color(59, 59, 59);
    }

    return grid;
}

sf::Vector2f plot::toSFML(sf::Vector2f original){
    //convert Cartesian coordinate to SFML
    return sf::Vector2f(original.x + WORK_PANEL / 2, SCREEN_HEIGHT / 2 - original.y);
}
