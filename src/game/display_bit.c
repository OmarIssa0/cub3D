/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/04/15 17:02:28 by oissa             #+#    #+#             */
/*   Updated: 2025/05/07 18:42:47 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>


void	draw_walls(t_main *main)
{
	int x = 0;
	while (x < SCREEN_WIDTH)
	{
		int texX, texY, y;
		float wallX = main->raycasting.wall_x[x];
		int side = main->raycasting.side[x];

		// اختيار التكستشر الصحيح حسب الاتجاه
		mlx_texture_t *texture;
		if (side == 0) // جدار أفقي
		{
			if (main->raycasting.ray_dir_x[x] > 0)
			{
				texture = main->game.texture_west; // غرب
			}
			else
				texture = main->game.texture_east; // شرق
		}
		else // جدار عمودي
		{
			if (main->raycasting.ray_dir_y[x] > 0)
				texture = main->game.texture_north; // شمال
			else
				texture = main->game.texture_south; // جنوب
		}

		texX = (int)(wallX * texture->width);

		// عكس اتجاه الصورة حسب الاتجاه
		if ((side == 0 && main->raycasting.ray_dir_x[x] > 0) || (side == 1
				&& main->raycasting.ray_dir_y[x] < 0))
			texX = texture->width - texX - 1;
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			static int i = 0;
			if (PUT_CEILING == true && main->time.now[TIME_COLOR]
				- main->time.last_time[TIME_COLOR] >= 1.0)
			{
               
				main->game.night_and_day[0] = 0x0A0A1AFF;
				main->game.night_and_day[1] = 0x1A1A3AFF;
				main->game.night_and_day[2] = 0x2A2A5AFF;
				main->game.night_and_day[3] = 0x3A3A7AFF;
				main->game.night_and_day[4] = 0x4A4A9AFF;
				main->game.night_and_day[5] = 0x5A5ABAFF;
				main->game.night_and_day[6] = 0x6A6ADAFF;
				main->game.night_and_day[7] = 0x7ABAF0FF;
				main->game.night_and_day[8] = 0x8ADAF4FF;
				main->game.night_and_day[9] = 0x9AEAF8FF;
				main->game.night_and_day[10] = 0xAADAF4FF;
				main->game.night_and_day[11] = 0xBACAF0FF;
				main->game.night_and_day[12] = 0xEBD084FF; 
				main->game.night_and_day[13] = 0xF3DE74FF;
				main->game.night_and_day[14] = 0xF4E394FF;
				main->game.night_and_day[15] = 0xF5E8B4FF;
				main->game.night_and_day[16] = 0xE8D488FF;
				main->game.night_and_day[17] = 0xC4B470FF;
				main->game.night_and_day[18] = 0xA09458FF;
				main->game.night_and_day[19] = 0x7C7440FF;
				main->game.night_and_day[20] = 0x585428FF;
				main->game.night_and_day[21] = 0x343410FF;
				main->game.night_and_day[22] = 0x1A1A08FF;
				main->game.night_and_day[23] = 0x000000FF; 
				main->game.night_and_day[24] = 0x000000FF; 
				main->time.last_time[TIME_COLOR] = main->time.now[TIME_COLOR];
				i++;
				if (i == 25)
					i = 0;
			}
			if ( y < main->raycasting.drawStart[x])
			{
				if (PUT_CEILING == true)
					mlx_put_pixel(main->game.image, x, y,
						main->game.night_and_day[i]);
				else
					mlx_put_pixel(main->game.image, x, y,
						main->game.color_ceiling);
			}
			else if (y >= main->raycasting.drawStart[x]
				&& y <= main->raycasting.drawEnd[x])
			{
				if (PUT_CEILING == true && main->raycasting.is_door[x])
				{
					if (main->raycasting.is_door[x] == 2)
						texture = main->game.texture_door_close;
					else if (main->raycasting.is_door[x] == 1)
						texture = main->game.texture_door_open;
				}
				else if (PUT_CEILING == true && i < 2)
				{
					texture = main->game.texture_light_wall;
				} else if (PUT_CEILING == true && i == 2)
                {
                    texture = main->game.texture_mid_wall;
                }
                else if (PUT_CEILING == true && i <= 4)
                    texture = main->game.texture_north;
				int d = y * 256 - SCREEN_HEIGHT * 128
					+ main->raycasting.lineHeight[x] * 128;
				texY = (int)((float)((d * texture->height)
							/ main->raycasting.lineHeight[x]) / 256.0f);
				size_t offset = (texY * texture->width + texX) * 4;
				uint8_t r = texture->pixels[offset];
				uint8_t g = texture->pixels[offset + 1];
				uint8_t b = texture->pixels[offset + 2];
				// فصل RGBA

				// إصلاح الألوان بدون شفافية
				uint32_t fixed_color = (r << 24) | (g << 16) | (b << 8) | 0xFF;

				mlx_put_pixel(main->game.image, x, y, fixed_color);
			}
			else
			{
				if (PUT_FLOOR == true)
				{
					texture = main->game.texture_floor;

					// حساب نسبة المسافة من الكاميرا إلى الأرضية
					float currentDist = (float)SCREEN_HEIGHT / (2.0f * y
							- SCREEN_HEIGHT);

					// حساب موقع الأرضية في الخريطة
					float floorX = main->player.x + currentDist
						* main->raycasting.ray_dir_x[x];
					float floorY = main->player.y + currentDist
						* main->raycasting.ray_dir_y[x];

					// تحويل لإحداثيات التكستشر
					texX = (int)(floorX * texture->width) % texture->width;
					texY = (int)(floorY * texture->height) % texture->height;

					// التحقق من أن pixels ليست NULL
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
