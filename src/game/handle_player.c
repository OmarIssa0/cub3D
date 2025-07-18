/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:32:12 by oissa             #+#    #+#             */
/*   Updated: 2025/07/18 17:15:57 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	init_player_value(t_player *player, float dir_x, float dir_y,
		float plane_x)
{
	player->dir_x = dir_x;
	player->dir_y = dir_y;
	player->plane_x = plane_x;
}

void	init_player(t_main *main)
{
	if (main->game.player_direction == 'N')
	{
		init_player_value(&main->player, 0, -1, 0.66);
		main->player.plane_y = 0;
	}
	else if (main->game.player_direction == 'S')
	{
		init_player_value(&main->player, 0, 1, -0.66);
		main->player.plane_y = 0;
	}
	else if (main->game.player_direction == 'E')
	{
		init_player_value(&main->player, 1, 0, 0);
		main->player.plane_y = 0.66;
	}
	else if (main->game.player_direction == 'W')
	{
		init_player_value(&main->player, -1, 0, 0);
		main->player.plane_y = -0.66;
	}
	main->player.x = main->game.player_x + 0.5;
	main->player.y = main->game.player_y + 0.5;
	main->file.map[main->game.player_y][main->game.player_x] = '0';
}
