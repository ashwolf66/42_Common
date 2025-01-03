/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchin <hchin@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 22:45:13 by hchin             #+#    #+#             */
/*   Updated: 2024/03/03 22:47:35 by hchin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*str;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst)
	{
		str = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = str;
	}
	*lst = 0;
}
