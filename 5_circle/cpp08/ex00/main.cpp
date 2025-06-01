/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:31:47 by jacha             #+#    #+#             */
/*   Updated: 2025/06/01 13:33:35 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

int main() {
    std::vector<int> vector;
    for (int i = 0; i < 5; ++i)
        vector.push_back(i);

    try {
        std::vector<int>::iterator it = easyfind(vector, 3);
        std::cout << "Found in vector: " << *it << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    std::list<int> list;
    for (int i = 10; i < 15; ++i)
        list.push_back(i);

    try {
        std::list<int>::iterator it = easyfind(list, 11);
        std::cout << "Found in list: " << *it << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return (0);
}
