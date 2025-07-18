/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 21:59:53 by oissa             #+#    #+#             */
/*   Updated: 2025/07/18 19:47:40 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_camx(t_main *main, int x)
{
	main->rays_2d.camera_x = 2 * x / (float)SCREEN_WIDTH - 1;
	main->rays_2d.ray_dir_x = main->player.dir_x + main->player.plane_x
		* main->rays_2d.camera_x;
	main->rays_2d.ray_dir_y = main->player.dir_y + main->player.plane_y
		* main->rays_2d.camera_x;
	main->rays_2d.map_x = (int)main->player.x;
	main->rays_2d.map_y = (int)main->player.y;
	if (main->rays_2d.ray_dir_x == 0)
		main->rays_2d.delta_dist_x = 1e30;
	else
		main->rays_2d.delta_dist_x = fabs(1 / main->rays_2d.ray_dir_x);
	if (main->rays_2d.ray_dir_y == 0)
		main->rays_2d.delta_dist_y = 1e30;
	else
		main->rays_2d.delta_dist_y = fabs(1 / main->rays_2d.ray_dir_y);
	main->rays_2d.hit = 0;
}

void	cauculate_step_and_side_dist(t_main *main)
{
	if (main->rays_2d.ray_dir_x < 0)
	{
		main->rays_2d.step_x = -1;
		main->rays_2d.side_dist_x = (main->player.x - main->rays_2d.map_x)
			* main->rays_2d.delta_dist_x;
	}
	else
	{
		main->rays_2d.step_x = 1;
		main->rays_2d.side_dist_x = (main->rays_2d.map_x + 1.0 - main->player.x)
			* main->rays_2d.delta_dist_x;
	}
	if (main->rays_2d.ray_dir_y < 0)
	{
		main->rays_2d.step_y = -1;
		main->rays_2d.side_dist_y = (main->player.y - main->rays_2d.map_y)
			* main->rays_2d.delta_dist_y;
	}
	else
	{
		main->rays_2d.step_y = 1;
		main->rays_2d.side_dist_y = (main->rays_2d.map_y + 1.0 - main->player.y)
			* main->rays_2d.delta_dist_y;
	}
}

void	calculate_hit(t_main *main)
{
	while (main->rays_2d.hit == 0)
	{
		if (main->rays_2d.side_dist_x < main->rays_2d.side_dist_y)
		{
			main->rays_2d.side_dist_x += main->rays_2d.delta_dist_x;
			main->rays_2d.map_x += main->rays_2d.step_x;
			main->rays_2d.side = 0;
		}
		else
		{
			main->rays_2d.side_dist_y += main->rays_2d.delta_dist_y;
			main->rays_2d.map_y += main->rays_2d.step_y;
			main->rays_2d.side = 1;
		}
		if (main->file.map[main->rays_2d.map_y][main->rays_2d.map_x] == '1'
			|| main->file.map[main->rays_2d.map_y][main->rays_2d.map_x] == 'D')
			main->rays_2d.hit = 1;
	}
}

void	calculate_ray_end_x_ray_end_y(t_main *m)
{
	m->rays_2d.ray_end_x = m->rays_2d.ray_start_x + m->rays_2d.ray_dir_x
		* m->rays_2d.perp_wall_dist * TILE_SIZE;
	m->rays_2d.ray_end_y = m->rays_2d.ray_start_y + m->rays_2d.ray_dir_y
		* m->rays_2d.perp_wall_dist * TILE_SIZE;
	m->rays_2d.min_x = m->rays_2d.offset_x;
	m->rays_2d.min_y = m->rays_2d.offset_y;
	m->rays_2d.max_x = m->rays_2d.offset_x + m->rays_2d.map_size
		* TILE_SIZE;
	m->rays_2d.max_y = m->rays_2d.offset_y + m->rays_2d.map_size
		* TILE_SIZE;
	if (m->rays_2d.ray_end_x < m->rays_2d.min_x)
		m->rays_2d.ray_end_x = m->rays_2d.min_x;
	if (m->rays_2d.ray_end_x > m->rays_2d.max_x)
		m->rays_2d.ray_end_x = m->rays_2d.max_x;
	if (m->rays_2d.ray_end_y < m->rays_2d.min_y)
		m->rays_2d.ray_end_y = m->rays_2d.min_y;
	if (m->rays_2d.ray_end_y > m->rays_2d.max_y)
		m->rays_2d.ray_end_y = m->rays_2d.max_y;
}

void	side(t_main *m)
{
	if (m->rays_2d.side == 0)
		m->rays_2d.perp_wall_dist = (m->rays_2d.map_x - m->player.x + (1
					- m->rays_2d.step_x) / 2) / m->rays_2d.ray_dir_x;
	else
		m->rays_2d.perp_wall_dist = (m->rays_2d.map_y - m->player.y + (1
					- m->rays_2d.step_y) / 2) / m->rays_2d.ray_dir_y;
	m->rays_2d.ray_start_x = m->rays_2d.offset_x + (m->player.x
			- (int)m->player.x) * TILE_SIZE + m->rays_2d.map_size / 2
		* TILE_SIZE;
	m->rays_2d.ray_start_y = m->rays_2d.offset_y + (m->player.y
			- (int)m->player.y) * TILE_SIZE + m->rays_2d.map_size / 2
		* TILE_SIZE;
}
