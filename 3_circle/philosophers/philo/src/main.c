/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:46:57 by jacha             #+#    #+#             */
/*   Updated: 2024/08/21 17:52:36 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_common	common;

	if (argc != 5 && argc != 6)
		return (0);
	if (init_philo(&common, argv))
		return (0);
	if (philo(&common))
		return (0);
	return (0);
}
