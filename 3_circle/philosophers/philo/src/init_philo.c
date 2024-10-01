/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:04:07 by jacha             #+#    #+#             */
/*   Updated: 2024/08/27 12:34:34 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_thread(t_common *common)
{
	int	i;

	i = 0;
	while (i < common->num)
	{
		common->philo[i].id = i + 1;
		common->philo[i].eat_count = 0;
		common->philo[i].l_f = i;
		common->philo[i].r_f = (i + 1) % common->num;
		common->philo[i].life = 0;
		common->philo[i].common = common;
		i++;
	}
	return (0);
}

int	init_mu(t_common *common)
{
	int	i;

	i = 0;
	while (i < common->num)
	{
		if (pthread_mutex_init(&(common->fork[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(common->eat_check), NULL))
		return (1);
	if (pthread_mutex_init(&(common->print), NULL))
		return (1);
	if (pthread_mutex_init(&(common->check), NULL))
		return (1);
	if (pthread_mutex_init(&(common->done_check), NULL))
		return (1);
	if (pthread_mutex_init(&(common->die_check), NULL))
		return (1);
	if (pthread_mutex_init(&(common->count), NULL))
		return (1);
	return (0);
}

int	init_philo(t_common *common, char **argv)
{
	common->num = ft_atoi(argv[1]);
	common->die_time = ft_atoi(argv[2]);
	common->eat_time = ft_atoi(argv[3]);
	common->sleep_time = ft_atoi(argv[4]);
	common->die = 0;
	common->done = 0;
	if (common->num < 1 || common->num > 200 || common->die_time < 0 || \
		common->eat_time < 0 || common->sleep_time < 0)
		return (1);
	if (argv[5])
	{
		common->max_eat = ft_atoi(argv[5]);
		if (common->max_eat < 1)
			return (1);
	}
	else
		common->max_eat = -1;
	if (init_mu(common))
		return (1);
	init_thread(common);
	return (0);
}
