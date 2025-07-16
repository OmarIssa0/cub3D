/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 21:59:53 by oissa             #+#    #+#             */
/*   Updated: 2025/07/16 20:51:49 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_camx(t_main *main, int x)
{
	main->rays_2d.cameraX = 2 * x / (float)SCREEN_WIDTH - 1;
	main->rays_2d.rayDirX = main->player.dir_x + main->player.plane_x
		* main->rays_2d.cameraX;
	main->rays_2d.rayDirY = main->player.dir_y + main->player.plane_y
		* main->rays_2d.cameraX;
	main->rays_2d.mapX = (int)main->player.x;
	main->rays_2d.mapY = (int)main->player.y;
	if (main->rays_2d.rayDirX == 0)
		main->rays_2d.deltaDistX = 1e30;
	else
		main->rays_2d.deltaDistX = fabs(1 / main->rays_2d.rayDirX);
	if (main->rays_2d.rayDirY == 0)
		main->rays_2d.deltaDistY = 1e30;
	else
		main->rays_2d.deltaDistY = fabs(1 / main->rays_2d.rayDirY);
	main->rays_2d.hit = 0;
}

void	cauculate_step_and_side_dist(t_main *main)
{
	if (main->rays_2d.rayDirX < 0)
	{
		main->rays_2d.stepX = -1;
		main->rays_2d.sideDistX = (main->player.x - main->rays_2d.mapX)
			* main->rays_2d.deltaDistX;
	}
	else
	{
		main->rays_2d.stepX = 1;
		main->rays_2d.sideDistX = (main->rays_2d.mapX + 1.0 - main->player.x)
			* main->rays_2d.deltaDistX;
	}
	if (main->rays_2d.rayDirY < 0)
	{
		main->rays_2d.stepY = -1;
		main->rays_2d.sideDistY = (main->player.y - main->rays_2d.mapY)
			* main->rays_2d.deltaDistY;
	}
	else
	{
		main->rays_2d.stepY = 1;
		main->rays_2d.sideDistY = (main->rays_2d.mapY + 1.0 - main->player.y)
			* main->rays_2d.deltaDistY;
	}
}

void	calculate_hit(t_main *main)
{
	while (main->rays_2d.hit == 0)
	{
		if (main->rays_2d.sideDistX < main->rays_2d.sideDistY)
		{
			main->rays_2d.sideDistX += main->rays_2d.deltaDistX;
			main->rays_2d.mapX += main->rays_2d.stepX;
			main->rays_2d.side = 0;
		}
		else
		{
			main->rays_2d.sideDistY += main->rays_2d.deltaDistY;
			main->rays_2d.mapY += main->rays_2d.stepY;
			main->rays_2d.side = 1;
		}
		if (main->file.map[main->rays_2d.mapY][main->rays_2d.mapX] == '1'
			|| main->file.map[main->rays_2d.mapY][main->rays_2d.mapX] == 'D')
			main->rays_2d.hit = 1;
	}
}

void	calculate_rayendx_rayendy(t_main *main)
{
	main->rays_2d.rayEndX = main->rays_2d.rayStartX + main->rays_2d.rayDirX
		* main->rays_2d.perpWallDist * TILE_SIZE;
	main->rays_2d.rayEndY = main->rays_2d.rayStartY + main->rays_2d.rayDirY
		* main->rays_2d.perpWallDist * TILE_SIZE;
	main->rays_2d.minX = main->rays_2d.offsetX;
	main->rays_2d.minY = main->rays_2d.offsetY;
	main->rays_2d.maxX = main->rays_2d.offsetX + main->rays_2d.map_size
		* TILE_SIZE;
	main->rays_2d.maxY = main->rays_2d.offsetY + main->rays_2d.map_size
		* TILE_SIZE;
	if (main->rays_2d.rayEndX < main->rays_2d.minX)
		main->rays_2d.rayEndX = main->rays_2d.minX;
	if (main->rays_2d.rayEndX > main->rays_2d.maxX)
		main->rays_2d.rayEndX = main->rays_2d.maxX;
	if (main->rays_2d.rayEndY < main->rays_2d.minY)
		main->rays_2d.rayEndY = main->rays_2d.minY;
	if (main->rays_2d.rayEndY > main->rays_2d.maxY)
		main->rays_2d.rayEndY = main->rays_2d.maxY;
}

void	side(t_main *main)
{
	if (main->rays_2d.side == 0)
		main->rays_2d.perpWallDist = (main->rays_2d.mapX - main->player.x + (1
					- main->rays_2d.stepX) / 2) / main->rays_2d.rayDirX;
	else
		main->rays_2d.perpWallDist = (main->rays_2d.mapY - main->player.y + (1
					- main->rays_2d.stepY) / 2) / main->rays_2d.rayDirY;
	main->rays_2d.rayStartX = main->rays_2d.offsetX + (main->player.x
			- (int)main->player.x) * TILE_SIZE + main->rays_2d.map_size / 2
		* TILE_SIZE;
	main->rays_2d.rayStartY = main->rays_2d.offsetY + (main->player.y
			- (int)main->player.y) * TILE_SIZE + main->rays_2d.map_size / 2
		* TILE_SIZE;
}
