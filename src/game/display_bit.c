/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:02:28 by oissa             #+#    #+#             */
/*   Updated: 2025/05/07 18:42:47 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void draw_walls(t_main *main)
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
                texture = main->game.texture_west; // غرب
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
        if ((side == 0 && main->raycasting.ray_dir_x[x] > 0) ||
            (side == 1 && main->raycasting.ray_dir_y[x] < 0))
            texX = texture->width - texX - 1;
        y = 0;
        while (y < SCREEN_HEIGHT)
        {
            static int i = 0;
            if (main->time.now[TIME_COLOR] - main->time.last_time[TIME_COLOR] >= 2.0)
            {
                main->game.night_and_day[0] = 0xFFFAF0FF; // Sunrise (Light Golden)
                main->game.night_and_day[1] = 0x87CEEBFF; // Morning (Sky Blue)
                main->game.night_and_day[2] = 0xFFD70088; // Sunset (Golden with transparency)
                main->game.night_and_day[3] = 0xFF450088; // Evening (Orange Red with transparency)
                main->game.night_and_day[4] = 0x2F4F4FFF; // Night (Dark Slate Gray)
                main->time.last_time[TIME_COLOR] = main->time.now[TIME_COLOR];
                i++;
                if (i == 5)
                    i = 0;
            }
            if (PUT_CEILING == true && y < main->raycasting.drawStart[x])
                mlx_put_pixel(main->game.image, x, y, main->game.night_and_day[i]);
            else if (PUT_CEILING == false && y > main->raycasting.drawEnd[x])
                mlx_put_pixel(main->game.image, x, y, main->game.color_ceiling);
            else if (y >= main->raycasting.drawStart[x] && y <= main->raycasting.drawEnd[x])
            {
                int d = y * 256 - SCREEN_HEIGHT * 128 + main->raycasting.lineHeight[x] * 128;
                texY = (int)((float)((d * texture->height) / main->raycasting.lineHeight[x]) / 256.0f);

                size_t offset = (texY * texture->width + texX) * 4;
                // unsigned int *pixels = (unsigned int *)texture->pixels;
                // uint32_t color = pixels[texY * texture->width + texX];
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
                    float currentDist = (float)SCREEN_HEIGHT / (2.0f * y - SCREEN_HEIGHT);

                    // حساب موقع الأرضية في الخريطة
                    float floorX = main->player.x + currentDist * main->raycasting.ray_dir_x[x];
                    float floorY = main->player.y + currentDist * main->raycasting.ray_dir_y[x];

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
                    mlx_put_pixel(main->game.image, x, y, main->game.color_floor);
            }

            y++;
        }
        x++;
    }
}
