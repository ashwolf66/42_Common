/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:49:33 by jacha             #+#    #+#             */
/*   Updated: 2025/05/18 17:49:35 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>

class Bureaucrat
{
private:
	std::string _name;
	int _grade;

public:
	Bureaucrat();
	~Bureaucrat();

	void GradeTooHighException();
	void GradeTooLowException();
	std::string getName();
	int getGrade();
};

#endif
