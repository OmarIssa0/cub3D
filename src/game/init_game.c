/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:49:26 by oissa             #+#    #+#             */
/*   Updated: 2025/04/05 19:04:52 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void init_player(t_main *main)
{
    if (main->game.player_direction == 'N')
    {
        main->player.dir_x = 0;
        main->player.dir_y = -1;
        main->player.plane_x = 0.66;
        main->player.plane_y = 0;
    }
    else if (main->game.player_direction == 'S')
    {
        main->player.dir_x = 0;
        main->player.dir_y = 1;
        main->player.plane_x = -0.66;
        main->player.plane_y = 0;
    }
    else if (main->game.player_direction == 'E')
    {
        main->player.dir_x = 1;
        main->player.dir_y = 0;
        main->player.plane_x = 0;
        main->player.plane_y = -0.66;
    }
    else if (main->game.player_direction == 'W')
    {
        main->player.dir_x = -1;
        main->player.dir_y = 0;
        main->player.plane_x = 0;
        main->player.plane_y = 0.66;
    }
    main->player.x = main->game.player_x + 0.5;
    main->player.y = main->game.player_y + 0.5;
    main->file.map[main->game.player_y][main->game.player_x] = '0';
    // printf("Player Position: (%f, %f)\n", main->player.p, main->player.posY);
    printf("Player Direction: (%f, %f)\n", main->player.dir_x, main->player.dir_y);
    printf("Camera Plane: (%f, %f)\n", main->player.plane_x, main->player.plane_y);
}

void cast_rays(t_main *main)
{
    for (int x = 0; x < SCREEN_WIDTH; x++) // لكل عمود في الشاشة
    {
        // 1️⃣ حساب اتجاه الشعاع لكل عمود
        double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
        double rayDirX = main->player.dir_x + main->player.plane_x * cameraX;
        double rayDirY = main->player.dir_y + main->player.plane_y * cameraX;

        // 2️⃣ تحديد موقع اللاعب في الخريطة
        int mapX = (int)main->player.x; // كان main->game.player_x
        int mapY = (int)main->player.y; // كان main->game.player_y

        // 3️⃣ حساب خطوات الأشعة والمسافات
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        double sideDistX, sideDistY;
        int stepX, stepY;

        // تحديد اتجاه الأشعة
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (main->player.x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - main->player.x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (main->player.y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - main->player.y) * deltaDistY;
        }

        // 4️⃣ تنفيذ خوارزمية DDA
        int hit = 0, side;
        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0; // الجدار في الاتجاه الأفقي
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1; // الجدار في الاتجاه العمودي
            }

            if (main->file.map[mapY][mapX] == '1') // التحقق من الاصطدام بالجدار
                hit = 1;
        }

        // 5️⃣ حساب المسافة إلى الجدار
        double perpWallDist;
        if (side == 0)
            perpWallDist = (mapX - main->player.x + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - main->player.y + (1 - stepY) / 2) / rayDirY;

        // 6️⃣ حساب ارتفاع الجدار بناءً على المسافة
        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
        main->raycasting.lineHeight[x] = lineHeight;

        // 7️⃣ حساب أعلى وأسفل الجدار على الشاشة لكل عمود
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT)
            drawEnd = SCREEN_HEIGHT - 1;

        main->raycasting.drawStart[x] = drawStart;
        main->raycasting.drawEnd[x] = drawEnd;
    }
}

// void draw_walls(t_main *main)
// {
//     uint32_t color_c = (main->file.ceiling_color[0] << 24) | (main->file.ceiling_color[1] << 16) | (main->file.ceiling_color[2] << 8) | 0xFF;
//     uint32_t color_f = (main->file.floor_color[0] << 24) | (main->file.floor_color[1] << 16) | (main->file.floor_color[2] << 8) | 0xFF;

//     for (int x = 0; x < SCREEN_WIDTH; x++)
//     {
//         int draw_start = main->raycasting.drawStart[x];
//         int draw_end = main->raycasting.drawEnd[x];
//         int line_height = draw_end - draw_start;

//         // 🔸 اختيار الـ texture المناسب حسب الاتجاه
//         mlx_texture_t *texture;
//         if (main->raycasting.side[x] == 0) // ضرب جدار عمودي (شرق/غرب)
//         {
//             if (main->raycasting.ray_dir_x[x] > 0)
//                 texture = main->game.texture_west;
//             else
//                 texture = main->game.texture_east;
//         }
//         else // ضرب جدار أفقي (شمال/جنوب)
//         {
//             if (main->raycasting.ray_dir_y[x] > 0)
//                 texture = main->game.texture_north;
//             else
//                 texture = main->game.texture_south;
//         }

//         // 🔸 حساب texture_x
//         float wall_x = main->raycasting.wall_x[x]; // القيمة بين 0 و 1
//         int tex_x = (int)(wall_x * (float)texture->width);
//         if ((main->raycasting.side[x] == 0 && main->raycasting.ray_dir_x[x] > 0) ||
//             (main->raycasting.side[x] == 1 && main->raycasting.ray_dir_y[x] < 0))
//         {
//             tex_x = texture->width - tex_x - 1;
//         }

//         for (int y = 0; y < SCREEN_HEIGHT; y++)
//         {
//             if (y < draw_start)
//                 mlx_put_pixel(main->game.image, x, y, color_c);
//             else if (y >= draw_start && y <= draw_end)
//             {
//                 int d = y * 256 - SCREEN_HEIGHT * 128 + line_height * 128;
//                 int tex_y = ((d * texture->height) / line_height) / 256;

//                 int pixel_index = (tex_y * texture->width + tex_x) * 4;
//                 uint8_t r = texture->pixels[pixel_index + 0];
//                 uint8_t g = texture->pixels[pixel_index + 1];
//                 uint8_t b = texture->pixels[pixel_index + 2];
//                 uint8_t a = texture->pixels[pixel_index + 3];

//                 uint32_t color = (r << 24) | (g << 16) | (b << 8) | a;
//                 mlx_put_pixel(main->game.image, x, y, color);
//             }
//             else
//                 mlx_put_pixel(main->game.image, x, y, color_f);
//         }
//     }
// }

void draw_walls(t_main *main)
{
    uint32_t color_c = (main->file.ceiling_color[0] << 24) | (main->file.ceiling_color[1] << 16) | (main->file.ceiling_color[2] << 8) | (0xFF);
    uint32_t color_f = (main->file.floor_color[0] << 24) | (main->file.floor_color[1] << 16) | (main->file.floor_color[2] << 8) | (0xFF);
    uint32_t color_w = (133 << 24) | (98 << 16) | (28 << 8) | (0xFF);


    int x = 0;
    while (x < SCREEN_WIDTH)
    {
        int y = 0;
        while (y < SCREEN_HEIGHT)
        {
            if (y < main->raycasting.drawStart[x])
                mlx_put_pixel(main->game.image, x, y, color_c);
            else if (y >= main->raycasting.drawStart[x] && y <= main->raycasting.drawEnd[x])
                mlx_put_pixel(main->game.image, x, y, color_w);
            else
                mlx_put_pixel(main->game.image, x, y, color_f);
            y++;
        }
        x++;
    }
}


void rotate_player(t_player *player, double angle)
{
    double old_dir_x = player->dir_x;
    player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
    player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);
    
    double old_plane_x = player->plane_x;
    player->plane_x = player->plane_x * cos(angle) - player->plane_y * sin(angle);
    player->plane_y = old_plane_x * sin(angle) + player->plane_y * cos(angle);
}

void move_player(t_main *main, double move_x, double move_y)
{
    
    
    double new_x = main->player.x + move_x;
    double new_y = main->player.y + move_y;
    if (new_x < 0 || new_x >= main->game.width_map ||
        new_y < 0 || new_y >= main->game.height_map) 
        return;
    // التحقق من الاصطدام مع الجدران
    if (main->file.map[(int)new_y][(int)main->player.x] != '1')
    main->player.y = new_y;
    if (main->file.map[(int)main->player.y][(int)new_x] != '1')
    main->player.x = new_x;
}
void handle_keys(void *param)
{
    t_main *main = (t_main *)param;
    double move_step = MOV_SPEED * 0.05;
    double rot_step = ROT_SPEED * 0.05;

    // if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    // {
        // EXIT
        if (mlx_is_key_down(main->game.mlx, MLX_KEY_ESCAPE)  /*|| mlx_is_key_down(main->game.mlx, MLX_KEY_Q)*/ )

        {
            free_all(main);
            exit(0);
        }

        // الحركة الأمامية والخلفية
        if (mlx_is_key_down(main->game.mlx, MLX_KEY_W) )
            move_player(main, main->player.dir_x * move_step, main->player.dir_y * move_step);
        if (mlx_is_key_down(main->game.mlx, MLX_KEY_S) )
            move_player(main, -main->player.dir_x * move_step, -main->player.dir_y * move_step);
        
        // الحركة الجانبية
        if (mlx_is_key_down(main->game.mlx, MLX_KEY_Q))
            move_player(main, main->player.dir_y * move_step, -main->player.dir_x * move_step);
        if (mlx_is_key_down(main->game.mlx, MLX_KEY_E))
            move_player(main, -main->player.dir_y * move_step, main->player.dir_x * move_step);
        
        // تدوير الكاميرا
        if (mlx_is_key_down(main->game.mlx, MLX_KEY_LEFT) || mlx_is_key_down(main->game.mlx,  MLX_KEY_A))
            rotate_player(&main->player, -rot_step);
        if (mlx_is_key_down(main->game.mlx, MLX_KEY_RIGHT)  || mlx_is_key_down(main->game.mlx,  MLX_KEY_D))
            rotate_player(&main->player, rot_step);
        // draw_walls(main);
        // إعادة رسم الشاشة
        cast_rays(main);
        
        if (DEGUGGING == true)
            draw_2D_view(main);
        else
            draw_walls(main);
        
        // int radius = SCREEN_WIDTH / 25;
        // int centerX = SCREEN_WIDTH / 11; // Centered horizontally
        // int centerY = SCREEN_HEIGHT - radius -SCREEN_WIDTH / 15; // Positioned 10 pixels above the bottom
        // int padding = 100; // Padding around the map

        // for (int y = -radius; y <= radius; y++)
        // {
        //     for (int x = -radius; x <= radius; x++)
        //     {
        //     if (x * x + y * y <= radius * radius)
        //     {
        //         int mapX = (int)(main->player.x + (double)x * main->game.width_map / (2 * radius));
        //         int mapY = (int)(main->player.y + (double)y * main->game.height_map / (2 * radius));

        //         if (mapX >= -padding && mapX < main->game.width_map  + padding && 
        //         mapY >= -padding && mapY < main->game.height_map + padding)
        //         {
        //         int squareSize = 2; // Size of the square for each map cell
        //         for (int sy = 0; sy < squareSize; sy++)
        //         {
        //             for (int sx = 0; sx < squareSize; sx++)
        //             {
        //             if (mapX < 0 || mapX >= main->game.width_map || 
        //                 mapY < 0 || mapY >= main->game.height_map)
        //                 mlx_put_pixel(main->game.image, centerX + x * squareSize + sx, centerY + y * squareSize + sy, 0x00000000); // Padding color
        //             else if (main->file.map[mapY][mapX] == '1')
        //                 mlx_put_pixel(main->game.image, centerX + x * squareSize + sx, centerY + y * squareSize + sy, 0xFF0000FF); // Wall color
        //             else if ((int)main->player.x == mapX && (int)main->player.y == mapY)
        //                 mlx_put_pixel(main->game.image, centerX + x * squareSize + sx, centerY + y * squareSize + sy, 0x00FF00FF); // Player color
        //             else
        //                 mlx_put_pixel(main->game.image, centerX + x * squareSize + sx, centerY + y * squareSize + sy, 0xFFFFFFFF); // Floor color
        //             }
        //         }
        //         }
        //     }
        //     }
        // }
        draw_2D_view(main);
        // draw_minimap(main);     
    // }
    
}

void handle_mouse(void *param)
{
    t_main *main = (t_main *)param;

    static int last_x = SCREEN_WIDTH / 2;
    int current_x, current_y;

    mlx_get_mouse_pos(main->game.mlx, &current_x, &current_y);

    int delta_x = current_x - last_x;
    if (delta_x != 0)
        rotate_player(&main->player, delta_x * -0.002); // Adjust sensitivity by changing the multiplier

    last_x = current_x;
}

void init_game(t_main *main)
{
    if (DEGUGGING == true)
        main->game.mlx = mlx_init((main->game.width_map  - 1) * TILE_SIZE, main->game.height_map * TILE_SIZE, "Cub3D", true);
    else
        main->game.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", true);
    if (main->game.mlx == NULL)
        exit_and_print((char *)mlx_strerror(mlx_errno), main, 0);
    main->raycasting.drawStart = ft_calloc(sizeof(int) , SCREEN_WIDTH);
    main->raycasting.drawEnd = ft_calloc(sizeof(int) , SCREEN_WIDTH);
    main->raycasting.lineHeight = ft_calloc(sizeof(int) , SCREEN_WIDTH);
    if (main->raycasting.drawStart == NULL || main->raycasting.drawEnd == NULL || main->raycasting.lineHeight == NULL)
    {
        free_all(main);
        exit_and_print("malloc error", main, 0);
    }
    init_player(main);
    cast_rays(main);
    main->game.image = mlx_new_image(main->game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (main->game.image == NULL)
    {
        free_all(main);
        exit_and_print((char *)mlx_strerror(mlx_errno), main, 0);
    }
    main->game.texture_north = mlx_load_png(main->file.north_texture);
    main->game.texture_east = mlx_load_png("assets/image/ice.png");
    main->game.texture_south = mlx_load_png("assets/image/ice.png");
    main->game.texture_west = mlx_load_png("assets/image/ice.png");
    /*
        ! check image --> NULL
    */   
    if (main->game.texture_north == NULL)
        exit_and_print("trexture north :(", main, 0);
    if (main->game.texture_east == NULL)
        exit_and_print("trexture east :(", main, 0);
    if (main->game.texture_south == NULL)
        exit_and_print("trexture south :(", main, 0);
    if (main->game.texture_west == NULL)
        exit_and_print("trexture west :(", main, 0);

    if (DEGUGGING == true)
        draw_2D_view(main);
    else
        draw_walls(main);
    mlx_image_to_window(main->game.mlx, main->game.image, 0, 0);
    draw_2D_view(main);
    // mlx_key_hook(main->game.mlx, &handle_keys, main);
    mlx_loop_hook(main->game.mlx, &handle_keys, main);
    mlx_set_cursor_mode(main->game.mlx, MLX_MOUSE_HIDDEN);
    mlx_set_mouse_pos(main->game.mlx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    // mlx_mouse_hook(main->game.mlx, &handle_keys, main);
}
