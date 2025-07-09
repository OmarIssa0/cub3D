/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:09:47 by oissa             #+#    #+#             */
/*   Updated: 2025/05/12 21:09:47 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_walls(t_main *main)
{
	int x = 0;
	while (x < SCREEN_WIDTH)
	{
		int texX, texY, y;
		float wallX = main->raycasting.wall_x[x];
		int side = main->raycasting.side[x];

		mlx_texture_t *texture = NULL;
		if (side == 0)
		{
			if (main->raycasting.ray_dir_x[x] > 0)
			{
				texture = main->game.texture_west;
			}
			else
				texture = main->game.texture_east;
		}
		else
		{
			if (main->raycasting.ray_dir_y[x] > 0)
				texture = main->game.texture_north;
			else
				texture = main->game.texture_south;
		}
        if (!texture || !texture->pixels)
			exit_and_print("Texture not loaded", main, DONT_CLOSE_FD);
		texX = (int)(wallX * texture->width);

		if ((side == 0 && main->raycasting.ray_dir_x[x] > 0) || (side == 1
				&& main->raycasting.ray_dir_y[x] < 0))
			texX = texture->width - texX - 1;
        if (texX < 0) texX = 0;
        if (texX >= (int)texture->width) texX = texture->width - 1;
            y = 0;
        static int i = 0;
		if (PUT_CEILING == true && main->time.now[TIME_COLOR]
			- main->time.last_time[TIME_COLOR] >= main->time.speed)
		{
               
				uint32_t colors[] = {
                    0x0A0A1AFF, 0x1A1A3AFF, 0x2A2A5AFF, 0x3A3A7AFF, 0x4A4A9AFF,
                    0x5A5ABAFF, 0x6A6ADAFF, 0x7ABAF0FF, 0x8ADAF4FF, 0x9AEAF8FF,
                    0xAADAF4FF, 0xBACAF0FF, 0xEBD084FF, 0xF3DE74FF, 0xF4E394FF,
                    0xF5E8B4FF, 0xE8D488FF, 0xC4B470FF, 0xA09458FF, 0x7C7440FF,
                    0x585428FF, 0x343410FF, 0x1A1A08FF, 0x000000FF, 0x000000FF
                };
                for (int j = 0; j < 25; j++)
                    main->game.night_and_day[j] = colors[j];
                main->time.last_time[TIME_COLOR] = main->time.now[TIME_COLOR];
                i = (i + 1) % 25;
		}
		while (y < SCREEN_HEIGHT)
		{
			
			if ( y < main->raycasting.draw_start[x])
			{
				if (PUT_CEILING == true)
					mlx_put_pixel(main->game.image, x, y,
						main->game.night_and_day[i]);
				else
					mlx_put_pixel(main->game.image, x, y,
						main->game.color_ceiling);
			}
			else if (y >= main->raycasting.draw_start[x]
				&& y <= main->raycasting.draw_end[x])
			{
				if (PUT_CEILING == true && main->raycasting.is_door[x])
				{
					if (main->raycasting.is_door[x] == 2)
						texture = main->game.texture_door_close;
					else if (main->raycasting.is_door[x] == 1)
						texture = main->game.texture_door_open;
				}
				else if (PUT_CEILING == true && i < 2)
					texture = main->game.texture_light_wall;
				else if (PUT_CEILING == true && i == 2)
                    texture = main->game.texture_mid_wall;
                else if (PUT_CEILING == true && i <= 4)
                    texture = main->game.texture_north;
                if (!texture || !texture->pixels)
					exit_and_print("Wall texture not loaded", main, DONT_CLOSE_FD);
				int d = y * 256 - SCREEN_HEIGHT * 128
					+ main->raycasting.line_height[x] * 128;
                texY = (int)((float)(d * texture->height) / main->raycasting.line_height[x] / 256.0f);
                if (texY < 0) texY = 0;
                if (texY >= (int)texture->height) texY = texture->height - 1;
				size_t offset = (texY * texture->width + texX) * 4;
				uint8_t r = texture->pixels[offset];
				uint8_t g = texture->pixels[offset + 1];
				uint8_t b = texture->pixels[offset + 2];

				uint32_t fixed_color = (r << 24) | (g << 16) | (b << 8) | 0xFF;

				mlx_put_pixel(main->game.image, x, y, fixed_color);
			}
			else
			{
				if (PUT_FLOOR == true)
				{
					texture = main->game.texture_floor;

					float currentDist = (float)SCREEN_HEIGHT / (2.0f * y
							- SCREEN_HEIGHT);

					float floorX = main->player.x + currentDist
						* main->raycasting.ray_dir_x[x];
					float floorY = main->player.y + currentDist
						* main->raycasting.ray_dir_y[x];

					texX = (int)(floorX * texture->width) % texture->width;
					texY = (int)(floorY * texture->height) % texture->height;

					if (texture->pixels != NULL)
					{
						size_t offset = (texY * texture->width + texX) * 4;
						uint8_t r = texture->pixels[offset];
						uint8_t g = texture->pixels[offset + 1];
						uint8_t b = texture->pixels[offset + 2];

						uint32_t fixed_color = (r << 24) | (g << 16) | (b << 8) | 0xFF;
						mlx_put_pixel(main->game.image, x, y, fixed_color);
					}
					else
					{
						exit_and_print("Texture pixels not loaded", main, 1);
					}
				}
				else
					mlx_put_pixel(main->game.image, x, y,
						main->game.color_floor);
			}

			y++;
		}
		x++;
	}
}
