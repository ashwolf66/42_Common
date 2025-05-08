/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:58:11 by jacha             #+#    #+#             */
/*   Updated: 2025/05/07 14:58:13 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

bool bsp(Point const a, Point const b, Point const c, Point const point)
{
	bool result1 = ((b.getx() - a.getx()) * (point.gety() - a.gety()) - (b.gety() - a.gety()) * (point.getx() - a.getx())) > 0;
	bool result2 = ((c.getx() - b.getx()) * (point.gety() - b.gety()) - (c.gety() - b.gety()) * (point.getx() - b.getx())) > 0;
	bool result3 = ((a.getx() - c.getx()) * (point.gety() - c.gety()) - (a.gety() - c.gety()) * (point.getx() - c.getx())) > 0;
	return ((result1 == result2) && (result2 == result3));
}