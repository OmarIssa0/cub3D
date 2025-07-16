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
	main->draw_bit.x = 0;
	while (main->draw_bit.x < SCREEN_WIDTH)
	{
		 main->draw_bit.wallX = main->raycasting.wall_x[main->draw_bit.x];
		main->draw_bit.side = main->raycasting.side[main->draw_bit.x];

		main->draw_bit.texture= NULL;
		if (main->draw_bit.side == 0)
		{
			if (main->raycasting.ray_dir_x[main->draw_bit.x] > 0)
			{
				main->draw_bit.texture = main->game.texture_west;
			}
			else
				main->draw_bit.texture = main->game.texture_east;
		}
		else
		{
			if (main->raycasting.ray_dir_y[main->draw_bit.x] > 0)
				main->draw_bit.texture = main->game.texture_north;
			else
				main->draw_bit.texture = main->game.texture_south;
		}
        if (!main->draw_bit.texture || !main->draw_bit.texture->pixels)
			exit_and_print("Texture not loaded", main, DONT_CLOSE_FD);
		main->draw_bit.texX = (int)(main->draw_bit.wallX * main->draw_bit.texture->width);

		if ((main->draw_bit.side == 0 && main->raycasting.ray_dir_x[main->draw_bit.x] > 0) || (main->draw_bit.side == 1
				&& main->raycasting.ray_dir_y[main->draw_bit.x] < 0))
			main->draw_bit.texX = main->draw_bit.texture->width - main->draw_bit.texX - 1;
        if (main->draw_bit.texX < 0) main->draw_bit.texX = 0;
        if (main->draw_bit.texX >= (int)main->draw_bit.texture->width) main->draw_bit.texX = main->draw_bit.texture->width - 1;
            main->draw_bit.y = 0;
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
		while (main->draw_bit.y < SCREEN_HEIGHT)
		{
			
			if ( main->draw_bit.y < main->raycasting.draw_start[main->draw_bit.x])
			{
				if (PUT_CEILING == true)
					mlx_put_pixel(main->game.image, main->draw_bit.x, main->draw_bit.y,
						main->game.night_and_day[i]);
				else
					mlx_put_pixel(main->game.image, main->draw_bit.x, main->draw_bit.y,
						main->game.color_ceiling);
			}
			else if (main->draw_bit.y >= main->raycasting.draw_start[main->draw_bit.x]
				&& main->draw_bit.y <= main->raycasting.draw_end[main->draw_bit.x])
			{
				if (PUT_CEILING == true && main->raycasting.is_door[main->draw_bit.x])
				{
					if (main->raycasting.is_door[main->draw_bit.x] == 2)
						main->draw_bit.texture = main->game.texture_door_close;
					else if (main->raycasting.is_door[main->draw_bit.x] == 1)
						main->draw_bit.texture = main->game.texture_door_open;
				}
				else if (PUT_CEILING == true && i < 2)
					main->draw_bit.texture = main->game.texture_light_wall;
				else if (PUT_CEILING == true && i == 2)
                    main->draw_bit.texture = main->game.texture_mid_wall;
                else if (PUT_CEILING == true && i <= 4)
                    main->draw_bit.texture = main->game.texture_north;
                if (!main->draw_bit.texture || !main->draw_bit.texture->pixels)
					exit_and_print("Wall texture not loaded", main, DONT_CLOSE_FD);
				int d = main->draw_bit.y * 256 - SCREEN_HEIGHT * 128
					+ main->raycasting.line_height[main->draw_bit.x] * 128;
                main->draw_bit.texY = (int)((float)(d * main->draw_bit.texture->height) / main->raycasting.line_height[main->draw_bit.x] / 256.0f);
                if (main->draw_bit.texY < 0) main->draw_bit.texY = 0;
                if (main->draw_bit.texY >= (int)main->draw_bit.texture->height) main->draw_bit.texY = main->draw_bit.texture->height - 1;
				size_t offset = (main->draw_bit.texY * main->draw_bit.texture->width + main->draw_bit.texX) * 4;
				uint8_t r = main->draw_bit.texture->pixels[offset];
				uint8_t g = main->draw_bit.texture->pixels[offset + 1];
				uint8_t b = main->draw_bit.texture->pixels[offset + 2];

				uint32_t fixed_color = (r << 24) | (g << 16) | (b << 8) | 0xFF;

				mlx_put_pixel(main->game.image, main->draw_bit.x, main->draw_bit.y, fixed_color);
			}
			else
			{
				if (PUT_FLOOR == true)
				{
					main->draw_bit.texture = main->game.texture_floor;

					float currentDist = (float)SCREEN_HEIGHT / (2.0f * main->draw_bit.y
							- SCREEN_HEIGHT);

					float floorX = main->player.x + currentDist
						* main->raycasting.ray_dir_x[main->draw_bit.x];
					float floorY = main->player.y + currentDist
						* main->raycasting.ray_dir_y[main->draw_bit.x];

					main->draw_bit.texX = (int)(floorX * main->draw_bit.texture->width) % main->draw_bit.texture->width;
					main->draw_bit.texY = (int)(floorY * main->draw_bit.texture->height) % main->draw_bit.texture->height;

					if (main->draw_bit.texture->pixels != NULL)
					{
						size_t offset = (main->draw_bit.texY * main->draw_bit.texture->width + main->draw_bit.texX) * 4;
						uint8_t r = main->draw_bit.texture->pixels[offset];
						uint8_t g = main->draw_bit.texture->pixels[offset + 1];
						uint8_t b = main->draw_bit.texture->pixels[offset + 2];

						uint32_t fixed_color = (r << 24) | (g << 16) | (b << 8) | 0xFF;
						mlx_put_pixel(main->game.image, main->draw_bit.x, main->draw_bit.y, fixed_color);
					}
					else
					{
						exit_and_print("Texture pixels not loaded", main, 1);
					}
				}
				else
					mlx_put_pixel(main->game.image, main->draw_bit.x, main->draw_bit.y,
						main->game.color_floor);
			}

			main->draw_bit.y++;
		}
		main->draw_bit.x++;
	}
}
