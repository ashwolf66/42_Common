/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 23:14:43 by hchin             #+#    #+#             */
/*   Updated: 2024/02/28 23:22:13 by hchin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	start_point(char const *str, char const *set)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (set[i])
	{
		if (str[start] == set[i])
		{
			start++;
			i = 0;
		}
		else
			i++;
	}
	return (start);
}

static int	end_point(char const *str, char const *set)
{
	int	i;
	int	end;

	i = 0;
	end = ft_strlen(str) - 1;
	while (set[i])
	{
		if (str[end] == set[i] && end != 0)
		{
			end--;
			i = 0;
		}
		else
			i++;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	char	*result;
	int		start;
	int		end;

	start = start_point(s1, set);
	end = end_point(s1, set);
	if (start > end)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!str)
		return (NULL);
	result = str;
	while (end - start + 1 > 0)
		*str++ = *(s1 + start++);
	*str = '\0';
	return (result);
}
/*
#include <stdio.h>
int	main()
{
	char	str[] = "abcaafgdefgff";
	char	set[] = "abfg";
	printf("%s\n", ft_strtrim(str, set));
	return 0;
}
*/
