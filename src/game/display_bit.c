/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:02:28 by oissa             #+#    #+#             */
/*   Updated: 2025/04/15 22:37:26 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*void draw_walls(t_main *main)
{
    int x;
    int y;

    x = 0;
    while (x < SCREEN_WIDTH)
    {
        y = 0;
        while (y < SCREEN_HEIGHT)
        {
            if (y < main->raycasting.drawStart[x])
                mlx_put_pixel(main->game.image, x, y, main->game.color_ceiling);
            else if (y >= main->raycasting.drawStart[x] && y <= main->raycasting.drawEnd[x])
                mlx_put_pixel(main->game.image, x, y, rgb_32bit(143, 98, 28, main));
            else
                mlx_put_pixel(main->game.image, x, y, main->game.color_floor);
            y++;
        }
        x++;
    }
}*/
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
            if (y < main->raycasting.drawStart[x])
                mlx_put_pixel(main->game.image, x, y, main->game.color_ceiling);
            else if (y >= main->raycasting.drawStart[x] && y <= main->raycasting.drawEnd[x])
            {
                int d = y * 256 - SCREEN_HEIGHT * 128 + main->raycasting.lineHeight[x] * 128;
                texY = ((d * texture->height) / main->raycasting.lineHeight[x]) / 256;

                unsigned int *pixels = (unsigned int *)texture->pixels;
                uint32_t color = pixels[texY * texture->width + texX];

                // فصل RGBA
                uint8_t r = (color >> 24) & 0xFF;
                uint8_t g = (color >> 16) & 0xFF;
                uint8_t b = (color >> 8) & 0xFF;

                // إصلاح الألوان بدون شفافية
                uint32_t fixed_color = (0xFF << 24) | (r << 16) | (g << 8) | b;

                mlx_put_pixel(main->game.image, x, y, fixed_color);
            }
            else
                mlx_put_pixel(main->game.image, x, y, main->game.color_floor);
            y++;
        }
        x++;
    }
}
