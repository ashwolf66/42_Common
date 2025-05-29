#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <sstream>

class RPN
{
private:
    std::stack<int> _stack;

public:
    RPN();
    RPN(const RPN &other);
    RPN &operator=(const RPN &other);
    ~RPN();
    int evaluate(const std::string& expression);
};
#endif