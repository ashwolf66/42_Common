/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_handle_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:54:49 by jacha             #+#    #+#             */
/*   Updated: 2025/03/28 14:30:58 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	length_check(t_data *data)
{
	if (data->map->cub_map[(int)data->player.pos_y]
		[(int)data->player.pos_x] == '1')
	{
		return (1);
	}
	return (0);
}
