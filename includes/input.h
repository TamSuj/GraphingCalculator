// #ifndef INPUT_H
// #define INPUT_H

// #include <SFML/Graphics.hpp>
// #include <iostream>
// #include <string>
// #include <vector>

// #include "token/function.h"
// #include "token/operator.h"
// #include "token/integer.h"
// #include "token/variable.h"
// #include "token/leftparen.h"
// #include "token/rightparen.h"
// #include "graph_info.cpp"

// using namespace std;

// class input{

// public:
//     string userInput;

//     input(){
//         graph_info info;
//         userInput = info.equation;
//         cout << "(input) user input " << userInput << endl;
//     }
//     Queue<Token*> convertToEquation()
//     {
//         Queue<Token*> calc;

//         string input = userInput;
//         string var = "";

//         vector<char> operators = {'+', '-', '*', '^', '/'};

//         int i = 0;
//         while(i < input.length()){
//             // cout << "i = " << input[i] << endl;

//             //Unary negative sign
//             if(input[i] == '-' && i == 0 ) 
//             {
//                 calc.push(new Integer("-1"));
//                 calc.push(new Operator("*"));
//                 i++;
//             }
//             else if(input[i] == '-' && input[i+1] == '-'){
//                 calc.push(new Operator("+"));
//                 i += 2;
//             }else if(input[i] == '-' && input[i+1] == '+' || input[i] == '+' && input[i+1] == '-'){
//                 calc.push(new Operator("-"));
//                 i += 2;
//             }else if(input[i] == '-' && input[i+1] == '('){
//                 calc.push(new Integer("-1"));
//                 calc.push(new Operator("*"));
//                 i++;
//             }

//             if (isdigit(input[i])) //if integer
//             {
//                 while(isdigit(input[i]) || input[i] == '.'){
//                     var += input[i];
//                     i++;
//                 }

//                 double num = stod(var);

//                 //if it's implicit multiplication
//                 if(i < input.length() && (isalpha(input[i]) || input[i] == '('))
//                     calc.push(new Operator("*"));

//                 // cout << "I'm implementing " << stod(var) << endl;
//                 calc.push(new Integer(num));
//             }
//             else if(toupper(input[i]) == 'X' || toupper(input[i]) == 'Y') //if variable
//             {
//                 //if it's a multiplication sign, not function
//                 //ex: (3) x5

//                 //if front and back or x is a number, push * (implicit multiplication)
//                 if(isdigit(input[i-1]) && isdigit(input[i+1])){
//                     calc.push(new Operator("*"));
//                     i++;
//                 }
//                 else{
//                     var += toupper(input[i]);

//                     //if it's implicit multiplication
//                     if(isdigit(input[i-1]))
//                         calc.push(new Operator("*"));

//                     calc.push(new Variable(var));
//                     i++;
//                 }
//             }
//             else if(input[i] == '('){
//                 calc.push(new LeftParen());
//                 i++;
//             }
//             else if(input[i] == ')'){
//                 calc.push(new RightParen());
//                 i++;
//             }
//             else if(isalpha(input[i]))//if paren or function (ex: cos, sin, tan)
//             {
//                 var += input[i];
//                 i++;

//                 while(isalpha(input[i]))
//                 {
//                     var += input[i];
//                     i++;
//                 }

//                 calc.push(new Function(var));

//             }else if(input[i] == ' ') //ignore whitespace
//                 i++;
//             else{ //operators
//                 // cout << "Detected " << input[i] << " operator" << endl;

//                 auto it = find(operators.begin(), operators.end(), input[i]);

//                 if (it != operators.end()) {
//                     var += input[i];
//                     calc.push(new Operator(var));
//                 } else {
//                     throw "Invalid input";
//                 }
//                 i++;
//             }
//             var = "";
//         }

//         return calc;

//     }

//     Queue<Token*> convertToEquation(string newInput){
//         userInput = newInput;
//         convertToEquation();
//     }
    
    
// };

// #endif