/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:09:45 by jacha             #+#    #+#             */
/*   Updated: 2025/05/07 14:58:17 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

bool bsp(Point const a, Point const b, Point const c, Point const point);

int main(void)
{
    Point a(0.0f, 0.0f);
    Point b(10.0f, 0.0f);
    Point c(0.0f, 10.0f);

    Point test1(2.0f, 2.0f);
    Point test2(0.0f, 5.0f);
    Point test3(0.0f, 0.0f);
    Point test4(10.0f, 10.0f);

    std::cout << "Testing point inside triangle: ";
    std::cout << (bsp(a, b, c, test1) ? "Inside" : "Outside") << std::endl;

    std::cout << "Testing point inside triangle: ";
    std::cout << (bsp(a, b, c, test2) ? "Inside" : "Outside") << std::endl;

    std::cout << "Testing point inside triangle: ";
    std::cout << (bsp(a, b, c, test3) ? "Inside" : "Outside") << std::endl;

    std::cout << "Testing point inside triangle: ";
    std::cout << (bsp(a, b, c, test4) ? "Inside" : "Outside") << std::endl;

    return (0);
}
