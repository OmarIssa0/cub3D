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

// uint32_t bilinear_sample(mlx_texture_t *texture, float texX, float texY)
// {
//     int x = (int)texX;
//     int y = (int)texY;
//     float dx = texX - x;
//     float dy = texY - y;

//     int w = texture->width;
//     int h = texture->height;

//     unsigned int *pixels = (unsigned int *)texture->pixels;

//     int x1 = x;
//     int y1 = y;
//     int x2 = (x + 1) % w;
//     int y2 = (y + 1) % h;

//     uint32_t c00 = pixels[y1 * w + x1];
//     uint32_t c10 = pixels[y1 * w + x2];
//     uint32_t c01 = pixels[y2 * w + x1];
//     uint32_t c11 = pixels[y2 * w + x2];

//     float r = ((1 - dx) * ((1 - dy) * ((c00 >> 24) & 0xFF) + dy * ((c01 >> 24) & 0xFF)) +
//                dx * ((1 - dy) * ((c10 >> 24) & 0xFF) + dy * ((c11 >> 24) & 0xFF)));

//     float g = ((1 - dx) * ((1 - dy) * ((c00 >> 16) & 0xFF) + dy * ((c01 >> 16) & 0xFF)) +
//                dx * ((1 - dy) * ((c10 >> 16) & 0xFF) + dy * ((c11 >> 16) & 0xFF)));

//     float b = ((1 - dx) * ((1 - dy) * ((c00 >> 8) & 0xFF) + dy * ((c01 >> 8) & 0xFF)) +
//                dx * ((1 - dy) * ((c10 >> 8) & 0xFF) + dy * ((c11 >> 8) & 0xFF)));

//     return (0xFF << 24) | ((int)r << 16) | ((int)g << 8) | (int)b;
// }
// void draw_walls(t_main *main)
// {
//     int x = 0;
//     while (x < SCREEN_WIDTH)
//     {
//         float texX;
//         int y;
//         float wallX = main->raycasting.wall_x[x];
//         int side = main->raycasting.side[x];

//         // اختيار التكستشر الصحيح حسب الاتجاه
//         mlx_texture_t *texture;
//         if (side == 0) // جدار أفقي
//         {
//             if (main->raycasting.ray_dir_x[x] > 0)
//                 texture = main->game.texture_west; // غرب
//             else
//                 texture = main->game.texture_east; // شرق
//         }
//         else // جدار عمودي
//         {
//             if (main->raycasting.ray_dir_y[x] > 0)
//                 texture = main->game.texture_north; // شمال
//             else
//                 texture = main->game.texture_south; // جنوب
//         }

//         texX = (wallX * texture->width);
//         if ((side == 0 && main->raycasting.ray_dir_x[x] > 0) ||
//             (side == 1 && main->raycasting.ray_dir_y[x] < 0))
//             texX = texture->width - texX - 1;

//         y = 0;
//         while (y < SCREEN_HEIGHT)
//         {
//             if (y < main->raycasting.drawStart[x])
//             {
//                 mlx_put_pixel(main->game.image, x, y, main->game.color_ceiling);
//             }
//             else if (y >= main->raycasting.drawStart[x] && y <= main->raycasting.drawEnd[x])
//             {
//                 int d = y * 256 - SCREEN_HEIGHT * 128 + main->raycasting.lineHeight[x] * 128;
//                 float ty = ((float)d * texture->height) / ((float)main->raycasting.lineHeight[x] * 256.0f);
//                 float tx = texX;

//                 uint32_t color = bilinear_sample(texture, tx, ty);
//                 mlx_put_pixel(main->game.image, x, y, color);
//             }
//             else
//             {
//                 mlx_put_pixel(main->game.image, x, y, main->game.color_floor);
//             }
//             y++;
//         }
//         x++;
//     }
// }

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
                texY = (int)((float)((d * texture->height) / main->raycasting.lineHeight[x]) / 256.0f);

                size_t  offset = (texY * texture->width + texX) * 4;
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
                mlx_put_pixel(main->game.image, x, y, main->game.color_floor);
            y++;
        }
        x++;
    }
}
