/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:32:03 by jacha             #+#    #+#             */
/*   Updated: 2025/06/01 13:33:53 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"

int main()
{
	MutantStack<int> mstack;

	mstack.push(5);
	mstack.push(17);

	std::cout << "TOP : " << mstack.top() << std::endl;
	std::cout << "SIZE : " << mstack.size() << std::endl;
	std::cout << std::endl;

	mstack.pop();

	std::cout << "TOP : " << mstack.top() << std::endl;
	std::cout << "SIZE : " << mstack.size() << std::endl;
	std::cout << std::endl;

	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);

	MutantStack<int>::iterator it = mstack.begin();
	std::cout << "Begin : " << *it << std::endl;
	MutantStack<int>::iterator ite = mstack.end();
	std::cout << "End : " << *(ite - 1) << std::endl;
	std::cout << std::endl;

	++it;
	std::cout << "Oper_Begin : " << *it << std::endl;
	--it;
	std::cout << "Oper_Begin : " << *it << std::endl;
	std::cout << std::endl;

	std::cout << "Stack : ";
	while (it != ite)
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;

	return 0;
}
