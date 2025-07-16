/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bit_helper2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:00:00 by oissa             #+#    #+#             */
/*   Updated: 2025/07/16 21:20:03 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_colors_part1(uint32_t *colors)
{
	colors[0] = 0x0A0A1AFF;
	colors[1] = 0x1A1A3AFF;
	colors[2] = 0x2A2A5AFF;
	colors[3] = 0x3A3A7AFF;
	colors[4] = 0x4A4A9AFF;
	colors[5] = 0x5A5ABAFF;
	colors[6] = 0x6A6ADAFF;
	colors[7] = 0x7ABAF0FF;
	colors[8] = 0x8ADAF4FF;
	colors[9] = 0x9AEAF8FF;
	colors[10] = 0xAADAF4FF;
	colors[11] = 0xBACAF0FF;
	colors[12] = 0xEBD084FF;
}

static void	init_colors_part2(uint32_t *colors)
{
	colors[13] = 0xF3DE74FF;
	colors[14] = 0xF4E394FF;
	colors[15] = 0xF5E8B4FF;
	colors[16] = 0xE8D488FF;
	colors[17] = 0xC4B470FF;
	colors[18] = 0xA09458FF;
	colors[19] = 0x7C7440FF;
	colors[20] = 0x585428FF;
	colors[21] = 0x343410FF;
	colors[22] = 0x1A1A08FF;
	colors[23] = 0x000000FF;
	colors[24] = 0x000000FF;
}

void	update_day_night_cycle(t_main *main, int *i)
{
	uint32_t	colors[25];
	int			j;

	if (PUT_CEILING == true && main->time.now[TIME_COLOR]
		- main->time.last_time[TIME_COLOR] >= main->time.speed)
	{
		init_colors_part1(colors);
		init_colors_part2(colors);
		j = -1;
		while (++j < 25)
			main->game.night_and_day[j] = colors[j];
		main->time.last_time[TIME_COLOR] = main->time.now[TIME_COLOR];
		*i = (*i + 1) % 25;
	}
}

void	draw_wall_pixel(t_main *main)
{
	int			d;
	size_t		offset;
	uint32_t	color;

	d = main->draw_bit.y * 256 - SCREEN_HEIGHT * 128
		+ main->raycasting.line_height[main->draw_bit.x] * 128;
	main->draw_bit.tex_y = (int)((float)(d * main->draw_bit.texture->height)
			/ main->raycasting.line_height[main->draw_bit.x] / 256.0f);
	if (main->draw_bit.tex_y < 0)
		main->draw_bit.tex_y = 0;
	if (main->draw_bit.tex_y >= (int)main->draw_bit.texture->height)
		main->draw_bit.tex_y = main->draw_bit.texture->height - 1;
	offset = (main->draw_bit.tex_y * main->draw_bit.texture->width
			+ main->draw_bit.tex_x) * 4;
	color = (main->draw_bit.texture->pixels[offset] << 24)
		| (main->draw_bit.texture->pixels[offset + 1] << 16)
		| (main->draw_bit.texture->pixels[offset + 2] << 8) | 0xFF;
	mlx_put_pixel(main->game.image, main->draw_bit.x, main->draw_bit.y, color);
}
