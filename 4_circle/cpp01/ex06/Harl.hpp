/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:52:58 by jacha             #+#    #+#             */
/*   Updated: 2025/04/29 16:53:01 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef HARL_CPP
#  define HARL_CPP

# include<iostream>

class Harl
{
private:
	void	debug(void);
	void	info(void);
	void	warning(void);
	void	error(void);
public:
	Harl();
	~Harl();
	void	complain(std::string level);
};

# endif