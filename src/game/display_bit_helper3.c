/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bit_helper3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:00:00 by oissa             #+#    #+#             */
/*   Updated: 2025/07/16 21:22:29 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_floor_coords(t_main *main, float *floor_x, float *floor_y)
{
	float	current_dist;

	current_dist = (float)SCREEN_HEIGHT / (2.0f * main->draw_bit.y
			- SCREEN_HEIGHT);
	*floor_x = main->player.x + current_dist
		* main->raycasting.ray_dir_x[main->draw_bit.x];
	*floor_y = main->player.y + current_dist
		* main->raycasting.ray_dir_y[main->draw_bit.x];
}

static void	draw_floor_texture(t_main *main, float floor_x, float floor_y)
{
	size_t		offset;
	uint32_t	color;

	main->draw_bit.tex_x = (int)(floor_x * main->draw_bit.texture->width)
		% main->draw_bit.texture->width;
	main->draw_bit.tex_y = (int)(floor_y * main->draw_bit.texture->height)
		% main->draw_bit.texture->height;
	offset = (main->draw_bit.tex_y * main->draw_bit.texture->width
			+ main->draw_bit.tex_x) * 4;
	color = (main->draw_bit.texture->pixels[offset] << 24)
		| (main->draw_bit.texture->pixels[offset + 1] << 16)
		| (main->draw_bit.texture->pixels[offset + 2] << 8) | 0xFF;
	mlx_put_pixel(main->game.image, main->draw_bit.x, main->draw_bit.y, color);
}

void	draw_floor_pixel(t_main *main)
{
	float	floor_x;
	float	floor_y;

	main->draw_bit.texture = main->game.texture_floor;
	calculate_floor_coords(main, &floor_x, &floor_y);
	if (main->draw_bit.texture->pixels != NULL)
		draw_floor_texture(main, floor_x, floor_y);
	else
		exit_and_print("Texture pixels not loaded", main, 1);
}

void	draw_column_pixels(t_main *m, int i)
{
	m->draw_bit.y = 0;
	while (m->draw_bit.y < SCREEN_HEIGHT)
	{
		if (m->draw_bit.y < m->raycasting.draw_start[m->draw_bit.x])
			draw_ceiling(m, i);
		else if (m->draw_bit.y >= m->raycasting.draw_start[m->draw_bit.x]
			&& m->draw_bit.y <= m->raycasting.draw_end[m->draw_bit.x])
		{
			select_wall_texture(m, i);
			draw_wall_pixel(m);
		}
		else
		{
			if (PUT_FLOOR == true)
				draw_floor_pixel(m);
			else
				mlx_put_pixel(m->game.image, m->draw_bit.x,
					m->draw_bit.y, m->game.color_floor);
		}
		m->draw_bit.y++;
	}
}
