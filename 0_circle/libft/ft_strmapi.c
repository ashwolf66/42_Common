/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:09:13 by jacha             #+#    #+#             */
/*   Updated: 2024/03/02 16:46:24 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ch;
	char			temp;
	unsigned int	len;
	unsigned int	i;

	if (!s)
		return (0);
	len = (unsigned int)ft_strlen(s);
	ch = (char *)malloc(sizeof(char) * len + 1);
	if (ch == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		temp = s[i];
		ch[i] = f(i, temp);
		i++;
	}
	ch[i] = '\0';
	return (ch);
}
