/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moni.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:53:16 by jacha             #+#    #+#             */
/*   Updated: 2024/08/27 11:41:25 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	moni(t_common *common, t_philo *philo)
{
	int	i;

	while (!(common->done))
	{
		i = -1;
		while (++i < common->num && !(common->die))
		{
			pthread_mutex_lock(&(common->eat_check));
			if (timestamp() - philo[i].life > common->die_time)
			{
				if (escape_loop(common, &(philo[i])))
					break ;
				philo_print(common, i + 1, "died");
				pthread_mutex_lock(&(common->die_check));
				common->die = 1;
				pthread_mutex_unlock(&(common->die_check));
			}
			pthread_mutex_unlock(&(common->eat_check));
			usleep(100);
		}
		if (die_check(common))
			break ;
		done_check(common, philo);
	}
}

int	die_check(t_common *common)
{
	pthread_mutex_lock(&(common->die_check));
	if (common->die)
	{
		pthread_mutex_unlock(&(common->die_check));
		return (1);
	}
	pthread_mutex_unlock(&(common->die_check));
	return (0);
}

void	done_check(t_common *common, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(common->count));
	while (common->max_eat != -1 && i < common->num && \
			philo[i].eat_count >= common->max_eat)
		i++;
	pthread_mutex_unlock(&(common->count));
	if (i == common->num)
	{
		pthread_mutex_lock(&(common->done_check));
		common->done = 1;
		pthread_mutex_unlock(&(common->done_check));
	}
}

int	escape_loop(t_common *common, t_philo *philo)
{
	pthread_mutex_lock(&(common->count));
	if (philo->eat_count == common->max_eat)
	{
		pthread_mutex_unlock(&(common->count));
		pthread_mutex_unlock(&(common->eat_check));
		return (1);
	}
	pthread_mutex_unlock(&(common->count));
	return (0);
}
