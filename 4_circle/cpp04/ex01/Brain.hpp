/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:54:42 by jacha             #+#    #+#             */
/*   Updated: 2025/05/14 12:54:43 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

#include <iostream>
#include <string>

class Brain
{
	private:
	std::string _ideas[100];
	public:
	    Brain();
    Brain(const Brain& other);
    Brain& operator=(const Brain& other);
    ~Brain();

	std::string	getter(int index) const;
	void	setter(int index, const std::string& idea);
};

# endif
