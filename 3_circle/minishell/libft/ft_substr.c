/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:35:40 by hchin             #+#    #+#             */
/*   Updated: 2024/02/28 15:43:40 by hchin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str1;
	char	*str2;
	size_t	s_len;
	size_t	i;

	s_len = ft_strlen(s);
	if (s == NULL || s_len < start)
		return (ft_strdup(""));
	if (start + len < s_len)
		str1 = (char *)malloc(sizeof(char) * (len + 1));
	else
		str1 = (char *)malloc(sizeof(char) * (s_len - start + 1));
	if (str1 == NULL)
		return (NULL);
	i = start;
	str2 = str1;
	while (i < (start + len) && *(s + i))
		*str2++ = *(s + i++);
	*str2 = '\0';
	return (str1);
}
/*
int main() {
  char src[] = "substr function Implementation";

  int m = 7;
  int n = 12;

  char* dest = ft_substr(src, m, n);

  printf("%s\n", dest);

  return 0;
}
*/
