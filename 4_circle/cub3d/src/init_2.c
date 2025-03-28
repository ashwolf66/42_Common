/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:56:08 by jacha             #+#    #+#             */
/*   Updated: 2025/03/28 14:56:13 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_vector(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	else if (dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
}

void	camere_plane(t_player *player, char dir)
{
	if (dir == 'N' || dir == 'S')
	{
		if (dir == 'N')
			player->pla_x = 0.66;
		else if (dir == 'S')
			player->pla_x = -0.66;
		player->pla_y = 0;
	}
	else if (dir == 'E' || dir == 'W')
	{
		player->pla_x = 0;
		if (dir == 'E')
			player->pla_y = 0.66;
		else if (dir == 'W')
			player->pla_y = -0.66;
	}
}
