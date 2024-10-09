/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 09:09:02 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:44:08 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void	*ms_malloc(size_t sz)
{
	void	*new;
	t_list	**gc;

	new = malloc(sz);
	gc = ms_glob();
	if (new == NULL)
	{
		return (NULL);
	}
	else
	{
		ms_lstadd_back(gc, ms_lstnew(new));
	}
	return (new);
}
