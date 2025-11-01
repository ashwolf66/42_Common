/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:22:55 by jacha             #+#    #+#             */
/*   Updated: 2024/03/05 15:47:34 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	size_t			s_len;
	char			*result;
	size_t			alloc_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if ((size_t)start >= s_len)
		return (ft_strdup(""));
	/* only allocate the needed amount: min(len, s_len - start) + 1 */
	if (s_len - (size_t)start < len)
		alloc_len = s_len - (size_t)start;
	else
		alloc_len = len;
	result = (char *)malloc(sizeof(char) * (alloc_len + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < alloc_len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
