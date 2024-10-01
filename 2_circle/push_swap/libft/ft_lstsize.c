/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:58:14 by jacha             #+#    #+#             */
/*   Updated: 2024/06/23 09:19:11 by logname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	if (!lst || !(lst->next))
		return (0);
	count = 1;
	while (lst->next != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}
