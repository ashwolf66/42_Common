/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 23:44:08 by jacha             #+#    #+#             */
/*   Updated: 2024/01/31 21:14:07 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strcmp(int min, int j, char *str[])
{
	int	i;

	i = 0;
	while (str[min][i] != '\0' || str[j][i] != '\0')
	{
		if (str[min][i] > str[j][i])
			return (str[min][i] - str[j][i]);
		else if (str[min][i] < str[j][i])
			return (str[min][i] - str[j][i]);
		i++;
	}
	return (str[min][i] - str[j][i]);
}

void	put_char(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			write(1, &argv[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int		i;
	int		j;
	int		min;
	char	*temp;

	i = 1;
	while (i < argc - 1)
	{
		j = i + 1;
		min = i;
		while (j < argc)
		{
			if (ft_strcmp(min, j, argv) > 0)
				min = j;
			j++;
		}
		temp = argv[min];
		argv[min] = argv[i];
		argv[i] = temp;
		i++;
	}
	put_char(argc, argv);
}
