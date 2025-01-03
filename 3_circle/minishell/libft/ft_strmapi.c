/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchin <hchin@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:43:02 by hchin             #+#    #+#             */
/*   Updated: 2024/03/02 17:52:39 by hchin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len;
	char			*str;

	i = 0;
	len = (unsigned int)(ft_strlen(s));
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
char	f1(unsigned int i, char c)
{
	char str;
	str = c + 1;
	return (str);
}

char	f2(unsigned int i, char c)
{
  char str;
  str = c + '0';
  return (str);
}


int main()
{
	char str1[] = "123";
	char* str2;
	str2 = ft_strmapi(str1, *f1);
	printf("%s\n", str2);
	str2 = ft_strmapi(str1, *f2);
	printf("%s\n", str2);
}
*/
