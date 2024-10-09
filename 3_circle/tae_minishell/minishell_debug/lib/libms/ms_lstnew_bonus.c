/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:22:01 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:46:52 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

t_list	*ms_lstnew(void *content)
{
	t_list	*p_lst;

	p_lst = (t_list *)malloc(sizeof(t_list) * 1);
	if (p_lst == NULL)
		return (NULL);
	p_lst->content = content;
	p_lst->next = NULL;
	return (p_lst);
}
