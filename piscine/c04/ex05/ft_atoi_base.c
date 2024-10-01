/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:25:27 by jacha             #+#    #+#             */
/*   Updated: 2024/02/03 19:26:45 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	str_check(char str, char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (str == base[i])
			return (i);
		i++;
	}
	return (-1);
}

int	plain_atoi(char *str, char *base, int num)
{
	int	i;
	int	bu;
	int	nbr;

	i = 0;
	bu = 0;
	nbr = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			bu++;
		i++;
	}
	while (str_check(str[i], base) != -1)
	{
		nbr = nbr * num + str_check(str[i], base);
		i++;
	}
	if (bu % 2 != 0)
		nbr *= -1;
	return (nbr);
}

int	base_check(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i] != '\0')
	{
		j = i + 1;
		if ((base[i] >= 9 && base[i] <= 13) || base[i] == 32)
			return (-1);
		if (base[i] == '+' || base[i] == '-')
			return (-1);
		while (base[j] != '\0')
		{
			if (base[i] == base[j])
				return (-1);
			j++;
		}
		i++;
	}
	if (i < 2)
		return (-1);
	return (i);
}

int	ft_atoi_base(char *str, char *base)
{
	int	num;

	num = base_check(base);
	if (num == -1)
		return (0);
	return (plain_atoi(str, base, num));
}
