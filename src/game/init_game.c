/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:49:26 by oissa             #+#    #+#             */
/*   Updated: 2025/04/19 12:42:06 by oissa            ###   ########.fr       */
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
    // ! image screen in game "core image"
    main->game.image = mlx_new_image(main->game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (main->game.image == NULL)
        exit_and_print((char *)mlx_strerror(mlx_errno), main, 0);
    // ! texture (NO, EA, SO, WE)
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
    main->game.texture_floor = mlx_load_png("assets/image/floor.png");
    if (main->game.texture_floor == NULL)
        exit_and_print("trexture floor :(", main, 0);
    main->game.texture_sky= mlx_load_png("assets/image/sky.png");
    if (main->game.texture_floor == NULL)
        exit_and_print("trexture sky :(", main, 0);
}

void init_game(t_main *main)
{
    init_mlx(main);
    init_player(main);
    cast_rays(main);
    init_texture(main);
    draw_walls(main);
    mlx_image_to_window(main->game.mlx, main->game.image, 0, 0);
    draw_2D_view(main);
    mlx_loop_hook(main->game.mlx, &handle_keys, main);
    mlx_set_cursor_mode(main->game.mlx, MLX_MOUSE_DISABLED);
    mlx_set_mouse_pos(main->game.mlx, SCREEN_WIDTH / 2, SCHAR_MAX / 2);
}
