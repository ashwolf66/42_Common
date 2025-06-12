/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:34:41 by jacha             #+#    #+#             */
/*   Updated: 2025/06/01 13:34:42 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
