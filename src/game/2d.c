/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:48:36 by oissa             #+#    #+#             */
/*   Updated: 2025/07/09 22:14:37 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_draw_rectangle(mlx_image_t *image, t_rectangle *rect)
{
	int	i;
	int	j;

	i = 0;
	while (i < rect->height)
	{
		j = 0;
		while (j < rect->width)
		{
			mlx_put_pixel(image, rect->x + j, rect->y + i, rect->color);
			j++;
		}
		i++;
	}
}

void	mlx_draw_line_thick(mlx_image_t *img, t_line line)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	half_thick;
	int	px;
	int	py;
	int	e2;

	dx = abs(line.x1 - line.x0);
	dy = -abs(line.y1 - line.y0);
	sx = line.x0 < line.x1 ? 1 : -1;
	sy = line.y0 < line.y1 ? 1 : -1;
	err = dx + dy;
	half_thick = line.thickness / 2;
	while (1)
	{
		int i = -half_thick;
		while (i <= half_thick)
		{
			int j = -half_thick;
			while (j <= half_thick)
			{
				px = line.x0 + i;
				py = line.y0 + j;
				if (px >= 0 && px < SCREEN_WIDTH && py >= 0
					&& py < SCREEN_HEIGHT)
					mlx_put_pixel(img, px, py, line.color);
				j++;
			}
			i++;
		}
		if (line.x0 == line.x1 && line.y0 == line.y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			line.x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			line.y0 += sy;
		}
	}
}

void	draw_2D_view(t_main *main)
{
	draw_map(main);
	draw_rays_2D(main);
}