/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:48:36 by oissa             #+#    #+#             */
/*   Updated: 2025/04/05 15:04:03 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



void mlx_draw_rectangle(mlx_image_t *image, int x, int y, int width, int height, uint32_t color)
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            mlx_put_pixel(image, x + j, y + i, color);
        }
    }
}

// دالة رسم الخط بسمك معين
void mlx_draw_line_thick(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color, int thickness) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1; 
    int err = dx + dy, e2;
    int half_thick = thickness / 2;

    while (1) {
        for (int i = -half_thick; i <= half_thick; ++i) {
            for (int j = -half_thick; j <= half_thick; ++j) {
                if (x0 + i >= 0 && x0 + i < SCREEN_WIDTH && 
                    y0 + j >= 0 && y0 + j < SCREEN_HEIGHT) {
                    mlx_put_pixel(img, x0 + i, y0 + j, color);
                }
            }
        }
        
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void draw_rays_2D(t_main *main) {
    for (int x = 0; x < SCREEN_WIDTH; x++) { 
        double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
        double rayDirX = main->player.dir_x + main->player.plane_x * cameraX;
        double rayDirY = main->player.dir_y + main->player.plane_y * cameraX;

        int mapX = (int)main->player.x;
        int mapY = (int)main->player.y;

        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        
        double sideDistX, sideDistY;
        int stepX, stepY;
        int hit = 0;
        int side;

        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (main->player.x - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - main->player.x) * deltaDistX;
        }

        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (main->player.y - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - main->player.y) * deltaDistY;
        }

        while (hit == 0) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (main->file.map[mapY][mapX] == '1') hit = 1;
        }

        // حساب المسافة العمودية للجدار
        double perpWallDist;
        if (side == 0)
            perpWallDist = (mapX - main->player.x + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - main->player.y + (1 - stepY) / 2) / rayDirY;

        // حساب نقاط البداية والنهاية
        double rayStartX = main->player.x * TILE_SIZE ;
        double rayStartY = main->player.y * TILE_SIZE;
        double rayEndX = rayStartX + rayDirX * perpWallDist * TILE_SIZE;
        double rayEndY = rayStartY + rayDirY * perpWallDist * TILE_SIZE;

        // رسم الشعاع بسمك 2 بكسل
        mlx_draw_line_thick(main->game.image, 
            (int)rayStartX, (int)rayStartY,
            (int)rayEndX, (int)rayEndY,
            0xffff00ff, 2);
    }
}

void draw_map(t_main *main) {
    for (int y = 0; y < main->game.height_map; y++) {
        for (int x = 0; x < main->game.width_map; x++) {
            char tile = main->file.map[y][x];
            uint32_t color = 0;

            if (tile == '1') color = 0xFFFFFF00;
            else if (tile == '0') color = 0x009000FF;
            else if (tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W') color = 0xFF0000FF;
            else color = 0x000000FF;

            mlx_draw_rectangle(main->game.image, 
                x * TILE_SIZE, y * TILE_SIZE, 
                TILE_SIZE, TILE_SIZE, color);

            // رسم الحدود
            uint32_t border = 0x000000FF;
            mlx_draw_line_thick(main->game.image, x*TILE_SIZE, y*TILE_SIZE, (x+1)*TILE_SIZE, y*TILE_SIZE, border, 1);
            mlx_draw_line_thick(main->game.image, x*TILE_SIZE, y*TILE_SIZE, x*TILE_SIZE, (y+1)*TILE_SIZE, border, 1);
        }
    }

    // رسم اللاعب
    int px = main->player.x * TILE_SIZE;
    int py = main->player.y * TILE_SIZE;
    mlx_draw_rectangle(main->game.image, px-3, py-3, 6, 6, 0xFF0000FF);

    // رسم اتجاه النظر الرئيسي
    mlx_draw_line_thick(main->game.image, 
        px, py,
        px + main->player.dir_x * 20,
        py + main->player.dir_y * 20,
        0xFF0000FF, 3);
}

void draw_2D_view(t_main *main)
{
    draw_map(main);
    draw_rays_2D(main);
}
