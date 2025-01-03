/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 23:36:07 by hchin             #+#    #+#             */
/*   Updated: 2024/03/01 00:17:17 by hchin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free_sp(char **s)
{
	unsigned int	i;

	i = 0;
	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static size_t	ft_wordcnt(const char *s, char d)
{
	size_t	cnt;
	size_t	i;

	cnt = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != d)
		{
			cnt++;
			while (s[i] && s[i] != d)
				i++;
		}
		else
			i++;
	}
	return (cnt);
}

static char	*ft_worddup(const char *s, char d)
{
	size_t	len;
	char	*ptr;

	len = 0;
	while (s[len] && s[len] != d)
		len++;
	ptr = (char *)ft_calloc(sizeof(char), len + 1);
	if (!ptr)
	{
		write(1, "ft_split: Memory allocation failed\n", 36);
		return (NULL);
	}
	ft_strlcpy(ptr, s, len + 1);
	return (ptr);
}

char	**ft_split(const char *s, char d)
{
	char	**ptr;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	len = ft_wordcnt(s, d);
	ptr = (char **)ft_calloc(sizeof(char *), len + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	j = -1;
	while (i < len && s[++j])
	{
		if (s[j] != d)
		{
			ptr[i] = ft_worddup(&(s[j]), d);
			if (!ptr[i++])
				return (ft_free_sp(ptr));
			while (s[j] && s[j] != d)
				j++;
		}
	}
	return (ptr);
}

// #include <stdio.h>
// int main()
// {
// 	char **s = ft_split("hello world", ' ');
// 	int i = 0;
// 	while (s[i])
// 	{
// 		printf("%s\n", s[i]);
// 		i++;
// 	}
// 	return 0;
// }
