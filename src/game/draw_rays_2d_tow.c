/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays_2d_tow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:46:13 by oissa             #+#    #+#             */
/*   Updated: 2025/07/16 21:06:31 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rays_2d(t_main *m)
{
	t_line	line;
	int		x;

	m->rays_2d.map_size = 12;
	m->rays_2d.offset_y = SCREEN_HEIGHT - (m->rays_2d.map_size * TILE_SIZE)
		- 10;
	m->rays_2d.offset_x = 10;
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		calculate_camx(m, x);
		cauculate_step_and_side_dist(m);
		calculate_hit(m);
		side(m);
		calculate_ray_end_x_ray_end_y(m);
		line.x0 = (int)m->rays_2d.ray_start_x;
		line.y0 = (int)m->rays_2d.ray_start_y;
		line.x1 = (int)m->rays_2d.ray_end_x;
		line.y1 = (int)m->rays_2d.ray_end_y;
		line.color = 0xffff00ff;
		line.thickness = 2;
		mlx_draw_line_thick(m->game.image, line);
		x++;
	}
}
