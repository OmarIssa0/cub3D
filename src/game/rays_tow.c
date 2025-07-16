/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_tow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:55:48 by oissa             #+#    #+#             */
/*   Updated: 2025/07/12 16:06:37 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calulate_delta_dist_and_side_tow(t_main *main)
{
	if (main->math.ray_dir_y < 0)
	{
		main->math.step_y = -1;
		main->math.side_dist_y = (main->player.y - main->math.map_y)
			* main->math.delta_dist_y;
	}
	else
	{
		main->math.step_y = 1;
		main->math.side_dist_y = (main->math.map_y + 1.0 - main->player.y)
			* main->math.delta_dist_y;
	}
}

void	dda_algorithm_tow(t_main *main, int x, int *i, int *found)
{
	if (main->file.map[main->math.map_y][main->math.map_x] == 'D')
	{
		*i = 0;
		*found = 0;
		while (*i < main->file.nb_door)
		{
			if (main->file.pos_doors[*i].x == main->math.map_x
				&& main->file.pos_doors[*i].y == main->math.map_y)
			{
				*found = 1;
				if (main->file.pos_doors[*i].is_open == 1)
					main->raycasting.is_door[x] = 1;
				else
					main->raycasting.is_door[x] = 2;
				break ;
			}
			(*i)++;
		}
		if (!found)
			main->raycasting.is_door[x] = 2;
	}
	else
		main->raycasting.is_door[x] = 0;
}

void	cast_rays(t_main *main)
{
	int	x;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		calculate_camx_rays(main, x);
		main->math.map_x = (int)main->player.x;
		main->math.map_y = (int)main->player.y;
		calulate_delta_dist_and_side(main);
		dda_algorithm(main, x);
		calculate_wall(main);
		main->math.line_height = (int)(SCREEN_HEIGHT
				/ main->math.perp_wall_dist);
		main->raycasting.line_height[x] = main->math.line_height;
		calculate_height_and_down_for_wall(main, x);
	}
}
