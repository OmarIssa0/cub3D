/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:49:26 by oissa             #+#    #+#             */
/*   Updated: 2025/05/07 16:56:06 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void init_mlx(t_main *main)
{
    main->game.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", true);
    if (main->game.mlx == NULL)
        exit_and_print((char *)mlx_strerror(mlx_errno), main, 0);
    main->raycasting.lineHeight = ft_calloc(sizeof(int), SCREEN_WIDTH);
    if (main->raycasting.lineHeight == NULL)
        exit_and_print("malloc error", main, 0);
}

static void init_texture(t_main *main)
{
    main->game.texture_north = mlx_load_png(main->file.north_texture);
    if (main->game.texture_north == NULL)
        exit_and_print("trexture north :(", main, 0);
    main->game.texture_east = mlx_load_png(main->file.east_texture);
    if (main->game.texture_east == NULL)
        exit_and_print("trexture east :(", main, 0);
    main->game.texture_south = mlx_load_png(main->file.south_texture);
    if (main->game.texture_south == NULL)
        exit_and_print("trexture south :(", main, 0);
    main->game.texture_west = mlx_load_png(main->file.west_texture);
    if (main->game.texture_west == NULL)
        exit_and_print("trexture west :(", main, 0);
    // ! init texture bouns
    main->game.texture_floor = mlx_load_png("assets/image/new/floor.png");
    if (main->game.texture_floor == NULL)
        exit_and_print("trexture floor :(", main, 0);
    main->game.texture_sky = mlx_load_png("assets/image/sky.png");
    if (main->game.texture_floor == NULL)
        exit_and_print("trexture sky :(", main, 0);
    main->game.texture_light_wall = mlx_load_png("assets/image/wall_horror2.png");
    if (main->game.texture_light_wall == NULL)
        exit_and_print("trexture light wall :(", main, 0);   
    main->game.texture_weapon[0] = mlx_load_png("assets/image/Super Shotgun/1_upscaled.png");
    main->game.texture_weapon[1] = mlx_load_png("assets/image/Super Shotgun/2_upscaled.png");
    main->game.texture_weapon[2] = mlx_load_png("assets/image/Super Shotgun/3_upscaled.png");
    main->game.texture_weapon[3] = mlx_load_png("assets/image/Super Shotgun/4_upscaled.png");
    main->game.texture_weapon[4] = mlx_load_png("assets/image/Super Shotgun/5_upscaled.png");
    main->game.texture_weapon[5] = mlx_load_png("assets/image/Super Shotgun/6_upscaled.png");
    main->game.texture_weapon[6] = mlx_load_png("assets/image/Super Shotgun/7_upscaled.png");
    main->game.texture_weapon[7] = mlx_load_png("assets/image/Super Shotgun/8_upscaled.png");
    main->game.texture_weapon[8] = mlx_load_png("assets/image/Super Shotgun/9_upscaled.png");
    main->game.texture_weapon[9] = mlx_load_png("assets/image/Super Shotgun/10_upscaled.png");
    main->game.texture_weapon[10] = mlx_load_png("assets/image/Super Shotgun/11_upscaled.png");
    main->game.texture_weapon[11] = mlx_load_png("assets/image/Super Shotgun/12_upscaled.png");
    main->game.texture_weapon[12] = mlx_load_png("assets/image/Super Shotgun/13_upscaled.png");
    main->game.texture_weapon[13] = mlx_load_png("assets/image/Super Shotgun/14_upscaled.png");
    main->game.texture_weapon[14] = mlx_load_png("assets/image/Super Shotgun/15_upscaled.png");
    main->game.texture_weapon[15] = mlx_load_png("assets/image/Super Shotgun/16_upscaled.png");
    main->game.texture_weapon[16] = mlx_load_png("assets/image/Super Shotgun/17_upscaled.png");
    main->game.texture_weapon[17] = mlx_load_png("assets/image/Super Shotgun/18_upscaled.png");
    main->game.texture_weapon[18] = mlx_load_png("assets/image/Super Shotgun/19_upscaled.png");
    main->game.texture_weapon[19] = mlx_load_png("assets/image/Super Shotgun/20_upscaled.png");
    main->game.texture_weapon[20] = mlx_load_png("assets/image/Super Shotgun/21_upscaled.png");
    main->game.texture_weapon[21] = mlx_load_png("assets/image/Super Shotgun/22_upscaled.png");
    main->game.texture_weapon[22] = mlx_load_png("assets/image/Super Shotgun/23_upscaled.png");
    main->game.texture_weapon[23] = mlx_load_png("assets/image/Super Shotgun/24_upscaled.png");
    main->game.texture_weapon[24] = mlx_load_png("assets/image/Super Shotgun/25_upscaled.png");
    main->game.texture_weapon[25] = mlx_load_png("assets/image/Super Shotgun/26_upscaled.png");
    main->game.texture_weapon[26] = mlx_load_png("assets/image/Super Shotgun/27_upscaled.png");
    main->game.texture_weapon[27] = mlx_load_png("assets/image/Super Shotgun/28_upscaled.png");
    main->game.texture_door_close = mlx_load_png("assets/image/door_close.png");
    main->game.texture_door_open = mlx_load_png("assets/image/door_open.png");
    if (main->game.texture_door_open == NULL)
        exit_and_print("trexture door open :(", main, 0);
    if (main->game.texture_door_close == NULL)
        exit_and_print("trexture door close :(", main, 0);
    int i = 0;
    
    while (i < 28)
    {
        if (main->game.texture_weapon[i] == NULL)
            exit_and_print("texture weapon :(", main, 0);
        i++;
    }
}

void exit_clean(void *param)
{
    t_main *main;

    main = (t_main *)param;
    free_all(main);
    exit(EXIT_SUCCESS);
}

void init_game(t_main *main)
{
    init_texture(main);
    init_mlx(main);
    main->game.image = mlx_new_image(main->game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (main->game.image == NULL)
        exit_and_print((char *)mlx_strerror(mlx_errno), main, 0);
    init_player(main);
    cast_rays(main);
    draw_walls(main);
    mlx_image_to_window(main->game.mlx, main->game.image, 0, 0);
    draw_2D_view(main);
    mlx_loop_hook(main->game.mlx, &handle_keys, main);
    mlx_close_hook(main->game.mlx, &exit_clean, main);
    mlx_set_cursor_mode(main->game.mlx, MLX_MOUSE_DISABLED);
    mlx_set_mouse_pos(main->game.mlx, SCREEN_WIDTH / 2, SCHAR_MAX / 2);
}
