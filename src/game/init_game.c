/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/03/27 16:49:26 by oissa             #+#    #+#             */
/*   Updated: 2025/05/07 16:56:06 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void	init_mlx(t_main *main)
{
	main->game.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", true);
	if (main->game.mlx == NULL)
		exit_and_print((char *)mlx_strerror(mlx_errno), main, 0);
	main->raycasting.lineHeight = ft_calloc(sizeof(int), SCREEN_WIDTH);
	if (main->raycasting.lineHeight == NULL)
		exit_and_print("malloc error", main, 0);
}

static void	init_wall(t_main *main)
{
	main->game.texture_north = mlx_load_png("assets/image/wall_horror1.png");
	if (main->game.texture_north == NULL)
		exit_and_print("texture north :(", main, 0);
	main->game.texture_south = mlx_load_png("assets/image/wall_horror1.png");
	if (main->game.texture_south == NULL)
		exit_and_print("texture south :(", main, 0);
	main->game.texture_west = mlx_load_png("assets/image/wall_horror1.png");
	if (main->game.texture_west == NULL)
		exit_and_print("texture west :(", main, 0);
	main->game.texture_east = mlx_load_png("assets/image/wall_horror1.png");
	if (main->game.texture_east == NULL)
		exit_and_print("texture east :(", main, 0);
	main->game.texture_floor = mlx_load_png("assets/image/new/floor.png");
	if (main->game.texture_floor == NULL)
		exit_and_print("texture floor :(", main, 0);
	main->game.texture_light_wall = mlx_load_png("assets/image/wall_horror3.png");
	if (main->game.texture_light_wall == NULL)
		exit_and_print("texture light wall :(", main, 0);
	main->game.texture_mid_wall = mlx_load_png("assets/image/wall_horror2.png");
	if (main->game.texture_light_wall == NULL)
		exit_and_print("texture light wall :(", main, 0);
}

static void	init_weapon(t_main *main)
{
	int i = 0;
	while (i < 28)
	{
		string path = ft_strjoin("assets/image/Super Shotgun/", ft_itoa(i
					+ 1));
		path = ft_strjoin(path, "_upscaled.png");
		if (path == NULL)
		{
			free(path);
			exit_and_print("Malloc failed", main, 0);
		}
		main->game.texture_weapon[i] = mlx_load_png(path);
		if (main->game.texture_weapon[i] == NULL)
		{
			free(path);
			exit_and_print("texture weapon :(", main, 0);
		}
		free(path);
		i++;
	}
}
static void	init_door(t_main *main)
{
	main->game.texture_door_close = mlx_load_png("assets/image/door_close.png");
	if (main->game.texture_door_close == NULL)
		exit_and_print("texture door close :(", main, 0);
	main->game.texture_door_open = mlx_load_png("assets/image/door_open.png");
	if (main->game.texture_door_open == NULL)
		exit_and_print("texture door open :(", main, 0);
}

static void	init_texture(t_main *main)
{
	if (PUT_CEILING == false)
	{
		main->game.texture_north = mlx_load_png(main->file.north_texture);
		if (main->game.texture_north == NULL)
			exit_and_print("texture north :(", main, 0);
		main->game.texture_east = mlx_load_png(main->file.east_texture);
		if (main->game.texture_east == NULL)
			exit_and_print("texture east :(", main, 0);
		main->game.texture_south = mlx_load_png(main->file.south_texture);
		if (main->game.texture_south == NULL)
			exit_and_print("texture south :(", main, 0);
		main->game.texture_west = mlx_load_png(main->file.west_texture);
		if (main->game.texture_west == NULL)
			exit_and_print("texture west :(", main, 0);
	}
	else
	{
		init_wall(main);
		init_weapon(main);
		init_door(main);
	}
}

void	exit_clean(void *param)
{
	t_main *main;

	main = (t_main *)param;
	free_all(main);
	exit(EXIT_SUCCESS);
}

void	init_game(t_main *main)
{
	init_texture(main);
	init_mlx(main);
	main->game.image = mlx_new_image(main->game.mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	if (main->game.image == NULL)
		exit_and_print((char *)mlx_strerror(mlx_errno), main, 0);
	init_player(main);
	cast_rays(main);
	draw_walls(main);
	mlx_image_to_window(main->game.mlx, main->game.image, 0, 0);
	mlx_loop_hook(main->game.mlx, &handle_keys, main);
	mlx_close_hook(main->game.mlx, &exit_clean, main);
	mlx_set_cursor_mode(main->game.mlx, MLX_MOUSE_DISABLED);
	mlx_set_mouse_pos(main->game.mlx, SCREEN_WIDTH / 2, SCHAR_MAX / 2);
}
