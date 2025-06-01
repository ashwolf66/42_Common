/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:34:39 by jacha             #+#    #+#             */
/*   Updated: 2025/06/01 13:34:40 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN &other)
{
    this->_stack = other._stack;
}

RPN &RPN::operator=(const RPN &other)
{
    this->_stack = other._stack;
    return (*this);
}

RPN::~RPN()
{
}

int RPN::evaluate(const std::string &expression)
{
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token)
    {
        if (token.length() == 1 && std::isdigit(token[0]))
            _stack.push(token[0] - '0');
        else if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (_stack.size() < 2)
                throw std::runtime_error("Not enough operands");
            int b = _stack.top();
            _stack.pop();
            int a = _stack.top();
            _stack.pop();
            int result;
            if (token == "+")
                result = a + b;
            else if (token == "-")
                result = a - b;
            else if (token == "*")
                result = a * b;
            else
            {
                if (b == 0)
                    throw std::runtime_error("Division by zero");
                result = a / b;
            }
            _stack.push(result);
        }
        else
        {
            throw std::runtime_error("Invalid token");
        }
    }
    if (_stack.size() != 1)
        throw std::runtime_error("Invalid expression");

    return _stack.top();
}
