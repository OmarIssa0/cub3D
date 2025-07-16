/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:13:05 by oissa             #+#    #+#             */
/*   Updated: 2025/07/16 20:50:39 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	calculate_camx_rays(t_main *main, int x)
{
	main->math.camera_x = 2 * x / (float)SCREEN_WIDTH - 1;
	main->math.ray_dir_x = main->player.dir_x + main->player.plane_x
		* main->math.camera_x;
	main->math.ray_dir_y = main->player.dir_y + main->player.plane_y
		* main->math.camera_x;
}

void	calulate_delta_dist_and_side(t_main *main)
{
	if (main->math.ray_dir_x == 0)
		main->math.delta_dist_x = MAX_FLOAT;
	else
		main->math.delta_dist_x = fabs(1 / main->math.ray_dir_x);
	if (main->math.ray_dir_y == 0)
		main->math.delta_dist_y = MAX_FLOAT;
	else
		main->math.delta_dist_y = fabs(1 / main->math.ray_dir_y);
	if (main->math.ray_dir_x < 0)
	{
		main->math.step_x = -1;
		main->math.side_dist_x = (main->player.x - main->math.map_x)
			* main->math.delta_dist_x;
	}
	else
	{
		main->math.step_x = 1;
		main->math.side_dist_x = (main->math.map_x + 1.0 - main->player.x)
			* main->math.delta_dist_x;
	}
	calulate_delta_dist_and_side_tow(main);
}

void	dda_algorithm(t_main *main, int x)
{
	int	i;
	int	found;

	main->math.hit = 0;
	while (main->math.hit == 0)
	{
		if (main->math.side_dist_x < main->math.side_dist_y)
		{
			main->math.side_dist_x += main->math.delta_dist_x;
			main->math.map_x += main->math.step_x;
			main->math.side = 0;
		}
		else
		{
			main->math.side_dist_y += main->math.delta_dist_y;
			main->math.map_y += main->math.step_y;
			main->math.side = 1;
		}
		if (main->file.map[main->math.map_y][main->math.map_x] == '1'
			|| main->file.map[main->math.map_y][main->math.map_x] == 'D')
			main->math.hit = 1;
	}
	dda_algorithm_tow(main, x, &i, &found);
	main->raycasting.side[x] = main->math.side;
}

void	calculate_wall(t_main *main)
{
	if (main->math.side == 0)
		main->math.perp_wall_dist = (main->math.map_x - main->player.x + (1
					- main->math.step_x) / 2) / main->math.ray_dir_x;
	else
		main->math.perp_wall_dist = (main->math.map_y - main->player.y + (1
					- main->math.step_y) / 2) / main->math.ray_dir_y;
}

void	calculate_height_and_down_for_wall(t_main *main, int x)
{
	main->math.draw_start = -main->math.line_height / 2 + SCREEN_HEIGHT / 2;
	if (main->math.draw_start < 0)
		main->math.draw_start = 0;
	main->math.draw_end = main->math.line_height / 2 + SCREEN_HEIGHT / 2;
	if (main->math.draw_end >= SCREEN_HEIGHT)
		main->math.draw_end = SCREEN_HEIGHT - 1;
	main->raycasting.draw_start[x] = main->math.draw_start;
	main->raycasting.draw_end[x] = main->math.draw_end;
	if (main->math.side == 0)
		main->math.wall_x = main->player.y + main->math.perp_wall_dist
			* main->math.ray_dir_y;
	else
		main->math.wall_x = main->player.x + main->math.perp_wall_dist
			* main->math.ray_dir_x;
	main->math.wall_x -= floor(main->math.wall_x);
	main->raycasting.wall_x[x] = main->math.wall_x;
	main->raycasting.ray_dir_x[x] = main->math.ray_dir_x;
	main->raycasting.ray_dir_y[x] = main->math.ray_dir_y;
}
