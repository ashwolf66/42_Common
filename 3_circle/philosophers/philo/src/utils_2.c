/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:41:59 by jacha             #+#    #+#             */
/*   Updated: 2024/09/02 10:46:14 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	select_fork(t_common *common, t_philo *philo)
{
	if (philo->l_f < philo->r_f)
	{
		pthread_mutex_lock(&(common->fork[philo->l_f]));
		philo_print(common, philo->id, "has taken a fork");
		pthread_mutex_lock(&(common->fork[philo->r_f]));
		philo_print(common, philo->id, "has taken a fork");
		return (1);
	}
	else
	{
		pthread_mutex_lock(&(common->fork[philo->r_f]));
		philo_print(common, philo->id, "has taken a fork");
		if (common->num == 1)
		{
			pthread_mutex_unlock(&(common->fork[philo->r_f]));
			return (0);
		}
		pthread_mutex_lock(&(common->fork[philo->l_f]));
		philo_print(common, philo->id, "has taken a fork");
		return (1);
	}
	return (0);
}

void	select_un_fork(t_common *common, t_philo *philo)
{
	if (philo->l_f < philo->r_f)
	{
		pthread_mutex_unlock(&(common->fork[philo->r_f]));
		pthread_mutex_unlock(&(common->fork[philo->l_f]));
	}
	else
	{
		pthread_mutex_unlock(&(common->fork[philo->l_f]));
		pthread_mutex_unlock(&(common->fork[philo->r_f]));
	}
}
