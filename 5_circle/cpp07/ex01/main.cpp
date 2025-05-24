/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:32:44 by jacha             #+#    #+#             */
/*   Updated: 2025/05/24 16:32:46 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

int main() {
    int intArray[5] = {1, 2, 3, 4, 5};
    std::string strArray[4] = {"jacha", "student", "5circle", "fighting"};

    ::iter(intArray, 5, printElement);
    ::iter(strArray, 4, printElement);

    return 0;
}
