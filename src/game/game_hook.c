/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:07:21 by oissa             #+#    #+#             */
/*   Updated: 2025/04/29 23:42:20 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void map_cir(t_main *main)
{
    int radius = SCREEN_WIDTH / 25;
    int centerX = SCREEN_WIDTH - radius - SCREEN_WIDTH / 15;  // Positioned on the right side
    int centerY = SCREEN_HEIGHT - radius - SCREEN_WIDTH / 15; // Positioned 10 pixels above the bottom
    int padding = 100;                                        // Padding around the map

    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
            {
                int mapX = (int)(main->player.x + (double)x * main->game.width_map / (2 * radius));
                int mapY = (int)(main->player.y + (double)y * main->game.height_map / (2 * radius));

                if (mapX >= -padding && mapX < main->game.width_map + padding &&
                    mapY >= -padding && mapY < main->game.height_map + padding)
                {
                    int squareSize = 2; // Size of the square for each map cell
                    for (int sy = 0; sy < squareSize; sy++)
                    {
                        for (int sx = 0; sx < squareSize; sx++)
                        {
                            if (mapX < 0 || mapX >= main->game.width_map - 1 ||
                                mapY < 0 || mapY >= main->game.height_map)
                                mlx_put_pixel(main->game.image, centerX + x * squareSize + sx, centerY + y * squareSize + sy, 0x00000000); // Padding color
                            else if (main->file.map[mapY][mapX] == '1')
                                mlx_put_pixel(main->game.image, centerX + x * squareSize + sx, centerY + y * squareSize + sy, 0xFF0000FF); // Wall color
                            else if ((int)main->player.x == mapX && (int)main->player.y == mapY)
                                mlx_put_pixel(main->game.image, centerX + x * squareSize + sx, centerY + y * squareSize + sy, 0x00FF00FF); // Player color
                            else
                                mlx_put_pixel(main->game.image, centerX + x * squareSize + sx, centerY + y * squareSize + sy, 0xFFFFFFFF); // Floor color
                        }
                    }
                }
            }
        }
    }
}


void display_fps(void)
{
    static int frame_count = 0;       // عدد الإطارات
    static double last_time = 0.0;   // الوقت السابق
    static double fps = 0.0;         // عدد الإطارات في الثانية

    // الحصول على الوقت الحالي
    struct timespec current_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    double now = current_time.tv_sec + (current_time.tv_nsec / 1e9);

    // إذا كانت هذه أول مرة، قم بتعيين الوقت السابق
    if (last_time == 0.0)
        last_time = now;

    frame_count++;

    // إذا مرّت ثانية واحدة، قم بحساب FPS
    if (now - last_time >= 1.0)
    {
        fps = frame_count / (now - last_time);
        frame_count = 0;
        last_time = now;

        // طباعة عدد الإطارات في الثانية
        printf("FPS: %.2f\n", fps);
    }
}

void handle_keys(void *param)
{
    t_main *main = (t_main *)param;
    double move_step = MOV_SPEED * 0.05;
    double rot_step = ROT_SPEED * 0.05;

    handle_mouse_rotation(main);
    if (mlx_is_key_down(main->game.mlx, MLX_KEY_ESCAPE))
    {
        free_all(main);
        exit(0);
    }
    // ? Front & Back
    if (mlx_is_key_down(main->game.mlx, MLX_KEY_W) || mlx_is_key_down(main->game.mlx, MLX_KEY_UP))
        move_player(main, main->player.dir_x * move_step, main->player.dir_y * move_step);
    if (mlx_is_key_down(main->game.mlx, MLX_KEY_S) || mlx_is_key_down(main->game.mlx, MLX_KEY_DOWN))
        move_player(main, -main->player.dir_x * move_step, -main->player.dir_y * move_step);

    // ? Side
    if (mlx_is_key_down(main->game.mlx, MLX_KEY_Q))
        move_player(main, main->player.dir_y * move_step, -main->player.dir_x * move_step);
    if (mlx_is_key_down(main->game.mlx, MLX_KEY_E))
        move_player(main, -main->player.dir_y * move_step, main->player.dir_x * move_step);

    // ? Cam
    if (mlx_is_key_down(main->game.mlx, MLX_KEY_LEFT) || mlx_is_key_down(main->game.mlx, MLX_KEY_A))
        rotate_player(&main->player, -rot_step);
    if (mlx_is_key_down(main->game.mlx, MLX_KEY_RIGHT) || mlx_is_key_down(main->game.mlx, MLX_KEY_D))
        rotate_player(&main->player, rot_step);

    // ? Display map
    cast_rays(main);

    draw_walls(main);
    // ? Display circler map
    // map_cir(main);
    draw_2D_view(main);
    display_fps();
}