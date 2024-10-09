/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:17:10 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/16 11:25:12 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_vector	*ms_vector_create(void)
{
	t_vector	*vector;

	vector = ms_malloc(sizeof(t_vector));
	vector->data = ms_malloc(sizeof(void *) * 2);
	vector->size = 0;
	vector->capacity = 2;
	return (vector);
}

void	ms_vector_resize(t_vector *vector, size_t new_capacity)
{
	void	**new_data;
	size_t	idx;

	new_data = ms_malloc(sizeof(void *) * new_capacity);
	idx = 0;
	while (idx < vector->size)
	{
		new_data[idx] = vector->data[idx];
		++idx;
	}
	vector->data = new_data;
	vector->capacity = new_capacity;
}

void	ms_vector_add(t_vector *vector, void *item)
{
	if (vector->size == vector->capacity)
	{
		ms_vector_resize(vector, vector->capacity * 2);
	}
	vector->data[vector->size] = item;
	vector->size++;
}

void	ms_vector_remove(t_vector *vector, size_t index)
{
	size_t	idx;

	if (index < vector->size)
	{
		idx = index;
		while (idx < vector->size - 1)
		{
			vector->data[idx] = vector->data[idx + 1];
			++idx;
		}
		vector->size--;
		if (vector->size > 0 && vector->size == vector->capacity / 4)
		{
			ms_vector_resize(vector, vector->capacity / 2);
		}
	}
}

void	*ms_vector_get(t_vector *vector, size_t index)
{
	if (index < vector->size)
	{
		return (vector->data[index]);
	}
	return (NULL);
}
