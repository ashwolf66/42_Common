/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:56:25 by jacha             #+#    #+#             */
/*   Updated: 2024/08/27 12:35:09 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo(t_common *common)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = common->philo;
	common->start_time = timestamp();
	while (i < common->num)
	{
		if (pthread_create(&(philo[i].thread), NULL, philoing, &(philo[i])))
			return (1);
		pthread_mutex_lock(&(common->check));
		philo[i].life = timestamp();
		pthread_mutex_unlock(&(common->check));
		i++;
	}
	moni(common, common->philo);
	the_end(philo, common);
	return (0);
}

void	*philoing(void *philo)
{
	t_philo		*actphilo;
	t_common	*common;

	actphilo = (t_philo *)philo;
	common = actphilo->common;
	if (!(actphilo->id % 2))
		usleep(100 * common->num);
	while (actphilo->eat_count != common->max_eat)
	{
		usleep(100 * common->num);
		pthread_mutex_lock(&(common->die_check));
		if (common->die)
		{
			pthread_mutex_unlock(&(common->die_check));
			break ;
		}
		pthread_mutex_unlock(&(common->die_check));
		if (eating(actphilo) || common->done)
			break ;
		philo_print(common, actphilo->id, "is sleeping");
		check_time((long long)common->sleep_time, common);
		philo_print(common, actphilo->id, "is thinking");
	}
	return (NULL);
}

int	eating(t_philo *philo)
{
	t_common	*common;

	common = philo->common;
	if (!select_fork(common, philo))
		return (1);
	pthread_mutex_lock(&(common->eat_check));
	life_up(philo, common);
	pthread_mutex_unlock(&(common->eat_check));
	check_time((long long)common->eat_time, common);
	eat_count(philo, common);
	pthread_mutex_lock(&(common->count));
	if (philo->eat_count == common->max_eat)
	{
		pthread_mutex_unlock(&(common->count));
		select_un_fork(common, philo);
		return (1);
	}
	pthread_mutex_unlock(&(common->count));
	select_un_fork(common, philo);
	return (0);
}

void	eat_count(t_philo *philo, t_common *common)
{
	pthread_mutex_lock(&(common->count));
	(philo->eat_count)++;
	pthread_mutex_unlock(&(common->count));
}

void	life_up(t_philo *philo, t_common *common)
{
	if (!(common->die))
	{
		philo_print(common, philo->id, "is eating");
		pthread_mutex_lock(&(common->check));
		philo->life = timestamp();
		pthread_mutex_unlock(&(common->check));
	}
}
