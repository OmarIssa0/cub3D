/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:48:36 by oissa             #+#    #+#             */
/*   Updated: 2025/07/14 20:59:11 by oissa            ###   ########.fr       */
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

static void	set_data(t_line_thick *thick_line, t_line *line)
{
	ft_bzero(thick_line, sizeof(t_line_thick));
	thick_line->dx = abs(line->x1 - line->x0);
	thick_line->dy = -abs(line->y1 - line->y0);
	if (line->x0 < line->x1)
		thick_line->sx = 1;
	else
		thick_line->sx = -1;
	if (line->y0 < line->y1)
		thick_line->sy = 1;
	else
		thick_line->sy = -1;
	thick_line->err = thick_line->dx + thick_line->dy;
	thick_line->half_thick = line->thickness / 2;
	thick_line->px = line->x0;
	thick_line->py = line->y0;
}

static int	check_line_statment(t_line *line, t_line_thick *thick_line)
{
	if (line->x0 == line->x1 && line->y0 == line->y1)
		return (EXIT_SUCCESS);
	thick_line->e2 = 2 * thick_line->err;
	if (thick_line->e2 >= thick_line->dy)
	{
		thick_line->err += thick_line->dy;
		line->x0 += thick_line->sx;
	}
	if (thick_line->e2 <= thick_line->dx)
	{
		thick_line->err += thick_line->dx;
		line->y0 += thick_line->sy;
	}
	return (EXIT_FAILURE);
}

void	mlx_draw_line_thick(mlx_image_t *img, t_line line)
{
	t_line_thick	t;
	int				i;
	int				j;

	set_data(&t, &line);
	while (1)
	{
		i = -t.half_thick;
		while (i <= t.half_thick)
		{
			j = -t.half_thick;
			while (j <= t.half_thick)
			{
				t.px = line.x0 + i;
				t.py = line.y0 + j;
				if (t.px >= 0 && t.px < SCREEN_WIDTH && t.py >= 0
					&& t.py < SCREEN_HEIGHT)
					mlx_put_pixel(img, t.px, t.py, line.color);
				j++;
			}
			i++;
		}
		if (check_line_statment(&line, &t) == EXIT_SUCCESS)
			break ;
	}
}

void	draw_2d_view(t_main *main)
{
	draw_map(main);
	draw_rays_2d(main);
}
