/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays_2d_tow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:46:13 by oissa             #+#    #+#             */
/*   Updated: 2025/07/16 20:51:55 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rays_2d(t_main *main)
{
	t_line	line;
	int		x;

	main->rays_2d.map_size = 12;
	main->rays_2d.offsetY = SCREEN_HEIGHT - (main->rays_2d.map_size * TILE_SIZE)
		- 10;
	main->rays_2d.offsetX = 10;
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		calculate_camx(main, x);
		cauculate_step_and_side_dist(main);
		calculate_hit(main);
		side(main);
		calculate_rayendx_rayendy(main);
		line.x0 = (int)main->rays_2d.rayStartX;
		line.y0 = (int)main->rays_2d.rayStartY;
		line.x1 = (int)main->rays_2d.rayEndX;
		line.y1 = (int)main->rays_2d.rayEndY;
		line.color = 0xffff00ff;
		line.thickness = 2;
		mlx_draw_line_thick(main->game.image, line);
		x++;
	}
}
