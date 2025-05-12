/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:48:36 by oissa             #+#    #+#             */
/*   Updated: 2025/05/12 21:31:16 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_draw_rectangle(mlx_image_t *image, int x, int y, int width,
		int height, uint32_t color)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			mlx_put_pixel(image, x + j, y + i, color);
		}
	}
}

// دالة رسم الخط بسمك معين
void	mlx_draw_line_thick(mlx_image_t *img, int x0, int y0, int x1, int y1,
		uint32_t color, int thickness)
{
	int	dx;
	int	dy;
	int	err;
	int	half_thick;
	int	e2;
	int	sx;
	int	sy;

	dx = abs(x1 - x0);
	dy = -abs(y1 - y0);
	dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	err = dx + dy;
	half_thick = thickness / 2;
	while (1)
	{
		for (int i = -half_thick; i <= half_thick; ++i)
		{
			for (int j = -half_thick; j <= half_thick; ++j)
			{
				if (x0 + i >= 0 && x0 + i < SCREEN_WIDTH && y0 + j >= 0 && y0
					+ j < SCREEN_HEIGHT)
				{
					mlx_put_pixel(img, x0 + i, y0 + j, color);
				}
			}
		}
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_rays_2D(t_main *main)
{
	float	cameraX;
	float	rayDirX;
	float	rayDirY;
	int		mapX;
	int		mapY;
	float	deltaDistX;
	float	deltaDistY;
	int		hit;
	int		side;
	float	perpWallDist;
	float	rayStartX;
	float	rayStartY;
	float	rayEndX;
	float	rayEndY;
	float	minX;
	float	minY;
	float	maxX;
	float	maxY;
	int		map_size;
	int		offsetY;
	int		offsetX;

	map_size = 12;
	// حجم الخريطة المصغرة (10x10)
	offsetY = SCREEN_HEIGHT - (map_size * TILE_SIZE) - 10;
	// وضع الخريطة في الجزء السفلي مع مسافة صغيرة
	offsetX = 10;
	// مسافة صغيرة من الجانب الأيسر
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		cameraX = 2 * x / (float)SCREEN_WIDTH - 1;
		rayDirX = main->player.dir_x + main->player.plane_x * cameraX;
		rayDirY = main->player.dir_y + main->player.plane_y * cameraX;
		mapX = (int)main->player.x;
		mapY = (int)main->player.y;
		deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		float sideDistX, sideDistY;
		int stepX, stepY;
		hit = 0;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (main->player.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - main->player.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (main->player.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - main->player.y) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (main->file.map[mapY][mapX] == '1'
				|| main->file.map[mapY][mapX] == 'D')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - main->player.x + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - main->player.y + (1 - stepY) / 2) / rayDirY;
		// حساب نقاط البداية والنهاية بالنسبة للخريطة المصغرة
		rayStartX = offsetX + (main->player.x - (int)main->player.x) * TILE_SIZE
			+ map_size / 2 * TILE_SIZE;
		rayStartY = offsetY + (main->player.y - (int)main->player.y) * TILE_SIZE
			+ map_size / 2 * TILE_SIZE;
		rayEndX = rayStartX + rayDirX * perpWallDist * TILE_SIZE;
		rayEndY = rayStartY + rayDirY * perpWallDist * TILE_SIZE;
		// التحقق من أن الشعاع داخل حدود الخريطة المصغرة
		minX = offsetX;
		minY = offsetY;
		maxX = offsetX + map_size * TILE_SIZE;
		maxY = offsetY + map_size * TILE_SIZE;
		if (rayEndX < minX)
			rayEndX = minX;
		if (rayEndX > maxX)
			rayEndX = maxX;
		if (rayEndY < minY)
			rayEndY = minY;
		if (rayEndY > maxY)
			rayEndY = maxY;
		// رسم الشعاع بسمك 2 بكسل داخل الخريطة المصغرة
		mlx_draw_line_thick(main->game.image, (int)rayStartX, (int)rayStartY,
			(int)rayEndX, (int)rayEndY, 0xffff00ff, 2);
	}
}

void	draw_map(t_main *main)
{
	int			map_size;
	int			offsetY;
	int			offsetX;
	int			mapY;
	int			mapX;
	char		tile;
	uint32_t	color;
	int			door_index;
	uint32_t	border;
	int			px;
	int			py;

	map_size = 12;
	offsetY = SCREEN_HEIGHT - (map_size * TILE_SIZE) - 10;
	offsetX = 10;
	for (int y = 0; y < map_size; y++)
	{
		for (int x = 0; x < map_size; x++)
		{
			mapY = (int)(main->player.y - map_size / 2 + y);
			mapX = (int)(main->player.x - map_size / 2 + x);
			if (mapY < 0 || mapY >= main->game.height_map || mapX < 0
				|| mapX >= main->game.width_map - 1 || !main->file.map
				|| !main->file.map[mapY])
			{
				mlx_draw_rectangle(main->game.image, offsetX + x * TILE_SIZE,
					offsetY + y * TILE_SIZE, TILE_SIZE, TILE_SIZE, 0x000000FF);
				continue ;
			}
			tile = main->file.map[mapY][mapX];
			color = 0;
			if (tile == '1')
				color = 0xFFFFFF00; // لون الجدران
			else if (tile == '0')
				color = 0x009000FF; // لون الأرضية
			else if (tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
				color = 0xFFFF00FF;
			else if (tile == 'D')
			{
				if (PUT_CEILING == true &&  main->file.pos_doors)
				{
					door_index = 0;
					while (main->file.pos_doors[door_index].x != mapX
						|| main->file.pos_doors[door_index].y != mapY)
						door_index++;
					if (main->file.pos_doors[door_index].is_open == 1)
						color = 0x0000FFFF; // لون الأبواب المفتوحة
					else
						color = 0xFF0000FF; // لون الأبواب المغلقة
				} 
				else
					color = 0xFFFFFF00;
			}
			else
			{
				mlx_draw_rectangle(main->game.image, offsetX + x * TILE_SIZE,
					offsetY + y * TILE_SIZE, TILE_SIZE, TILE_SIZE, 0x000000FF);
				continue ;
			}
			// رسم البلاط
			mlx_draw_rectangle(main->game.image, offsetX + x * TILE_SIZE,
				offsetY + y * TILE_SIZE, TILE_SIZE, TILE_SIZE, color);
			// رسم الحدود
			border = 0x000000FF;
			mlx_draw_line_thick(main->game.image, offsetX + x * TILE_SIZE,
				offsetY + y * TILE_SIZE, offsetX + (x + 1) * TILE_SIZE, offsetY
				+ y * TILE_SIZE, border, 1);
			mlx_draw_line_thick(main->game.image, offsetX + x * TILE_SIZE,
				offsetY + y * TILE_SIZE, offsetX + x * TILE_SIZE, offsetY + (y
					+ 1) * TILE_SIZE, border, 1);
		}
	}
	px = offsetX + (main->player.x - (int)main->player.x) * TILE_SIZE + map_size
		/ 2 * TILE_SIZE;
	py = offsetY + (main->player.y - (int)main->player.y) * TILE_SIZE + map_size
		/ 2 * TILE_SIZE;
	mlx_draw_rectangle(main->game.image, px - 3, py - 3, 6, 6, 0xFF0000FF);
	// رسم اتجاه النظر الرئيسي
	mlx_draw_line_thick(main->game.image, px, py, px + main->player.dir_x * 1,
		py + main->player.dir_y * 1, 0xFF0000FF, 4);
}

void	draw_2D_view(t_main *main)
{
		draw_map(main);
		draw_rays_2D(main);
}