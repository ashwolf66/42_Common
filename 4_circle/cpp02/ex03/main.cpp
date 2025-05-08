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

bool	bsp(Point const a, Point const b, Point const c, Point const point);

int	main(void) {
    Point a(0.0f, 0.0f);
    Point b(10.0f, 0.0f);
    Point c(0.0f, 10.0f);

    Point inside(2.0f, 2.0f);
    Point edge(0.0f, 5.0f);
    Point vertex(0.0f, 0.0f);
    Point outside(10.0f, 10.0f);

    std::cout << "Testing point inside triangle: ";
    std::cout << (bsp(a, b, c, inside) ? "Inside" : "Outside") << std::endl;

    std::cout << "Testing point on edge: ";
    std::cout << (bsp(a, b, c, edge) ? "Inside" : "Outside") << std::endl;

    std::cout << "Testing point on vertex: ";
    std::cout << (bsp(a, b, c, vertex) ? "Inside" : "Outside") << std::endl;

    std::cout << "Testing point outside triangle: ";
    std::cout << (bsp(a, b, c, outside) ? "Inside" : "Outside") << std::endl;

    return (0);
}
