/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:49:26 by oissa             #+#    #+#             */
/*   Updated: 2025/04/15 21:47:24 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void init_mlx(t_main *main)
{
    if (DEGUGGING == true)
        main->game.mlx = mlx_init((main->game.width_map - 1) * TILE_SIZE, main->game.height_map * TILE_SIZE, "Cub3D", true);
    else
        main->game.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", true);
    if (main->game.mlx == NULL)
        exit_and_print((char *)mlx_strerror(mlx_errno), main, 0);
    main->raycasting.lineHeight = ft_calloc(sizeof(int), SCREEN_WIDTH);
    if (main->raycasting.lineHeight == NULL)
        exit_and_print("malloc error", main, 0);
}

static void init_texture(t_main *main)
{
    main->game.image = mlx_new_image(main->game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (main->game.image == NULL)
        exit_and_print((char *)mlx_strerror(mlx_errno), main, 0);

    main->game.texture_west = mlx_load_png(main->file.west_texture);

    main->game.texture_north = mlx_load_png(main->file.north_texture);
    main->game.texture_north = mlx_load_png("assets/image/1.png");
    if (main->game.texture_north == NULL)
        exit_and_print("trexture north :(", main, 0);
    main->game.texture_east = mlx_load_png(main->file.east_texture);
    main->game.texture_east = mlx_load_png("assets/image/2.png");
    if (main->game.texture_east == NULL)
        exit_and_print("trexture east :(", main, 0);
    main->game.texture_south = mlx_load_png(main->file.south_texture);
    main->game.texture_south = mlx_load_png("assets/image/3.png");
    if (main->game.texture_south == NULL)
        exit_and_print("trexture south :(", main, 0);
    main->game.texture_west = mlx_load_png("assets/image/4.png");
    if (main->game.texture_west == NULL)
        exit_and_print("trexture west :(", main, 0);
    /*
        ! check image --> NULL
    */
}

void init_game(t_main *main)
{
    init_mlx(main);
    init_player(main);
    cast_rays(main);
    init_texture(main);

    if (DEGUGGING == true)
        draw_2D_view(main);
    else
        draw_walls(main);
    mlx_image_to_window(main->game.mlx, main->game.image, 0, 0);
    draw_2D_view(main);
    mlx_loop_hook(main->game.mlx, &handle_keys, main);
    mlx_set_cursor_mode(main->game.mlx, MLX_MOUSE_DISABLED);
    mlx_set_mouse_pos(main->game.mlx, SCREEN_WIDTH / 2, SCHAR_MAX / 2);
}
