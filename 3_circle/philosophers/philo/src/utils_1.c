/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:57:52 by jacha             #+#    #+#             */
/*   Updated: 2024/08/21 20:11:37 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *n)
{
	int	i;
	int	num;
	int	sign;

	i = 0;
	num = 0;
	sign = 1;
	while ((((char *)n)[i] >= 9 && ((char *)n)[i] <= 13) || \
			((char *)n)[i] == 32)
		i++;
	if (((char *)n)[i] == '+' || ((char *)n)[i] == '-')
	{
		if (((char *)n)[i] == '-')
			sign = -1;
		i++;
	}
	while (((char *)n)[i] >= '0' && ((char *)n)[i] <= '9')
	{
		num = num * 10 + (((char *)n)[i] - '0');
		i++;
	}
	if (((char *)n)[i] != '\0')
		return (-1);
	return (num * sign);
}

void	the_end(t_philo *philo, t_common *common)
{
	int	i;

	i = 0;
	while (i < common->num)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < common->num)
	{
		pthread_mutex_destroy(&(common->fork[i]));
		i++;
	}
	pthread_mutex_destroy(&(common->eat_check));
	pthread_mutex_destroy(&(common->print));
	pthread_mutex_destroy(&(common->check));
	pthread_mutex_destroy(&(common->done_check));
	pthread_mutex_destroy(&(common->die_check));
	pthread_mutex_destroy(&(common->count));
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	philo_print(t_common *common, int id, char *chr)
{
	pthread_mutex_lock(&(common->print));
	pthread_mutex_lock(&(common->die_check));
	if (1)
	{
		if (common->die)
		{
			pthread_mutex_unlock(&(common->die_check));
			pthread_mutex_unlock(&(common->print));
			return ;
		}
		printf("%lli ", timestamp() - common->start_time);
		printf("%d ", id);
		printf("%s\n", chr);
	}
	pthread_mutex_unlock(&(common->die_check));
	pthread_mutex_unlock(&(common->print));
}

void	check_time(long long time, t_common *common)
{
	long long	i;

	i = timestamp();
	while (1)
	{
		pthread_mutex_lock(&(common->die_check));
		if (common->die)
		{
			pthread_mutex_unlock(&(common->die_check));
			break ;
		}
		pthread_mutex_unlock(&(common->die_check));
		if (timestamp() - i >= time)
			break ;
		usleep(100);
	}
}
