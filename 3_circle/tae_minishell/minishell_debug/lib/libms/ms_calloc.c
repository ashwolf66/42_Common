/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:06:29 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:46:52 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void	*ms_calloc(size_t nmemb, size_t size)
{
	size_t	total_len;
	void	*addr;

	total_len = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (ms_malloc(0));
	if (total_len / nmemb != size)
		return (NULL);
	addr = ms_malloc(total_len);
	if (addr == NULL)
		return (NULL);
	ms_bzero(addr, total_len);
	return (addr);
}
