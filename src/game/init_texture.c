/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:07:07 by oissa             #+#    #+#             */
/*   Updated: 2025/05/13 13:16:03 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_wall(t_main *main)
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
	main->game.texture_light_wall
		= mlx_load_png("assets/image/wall_horror3.png");
	if (main->game.texture_light_wall == NULL)
		exit_and_print("texture light wall :(", main, 0);
	main->game.texture_mid_wall = mlx_load_png("assets/image/wall_horror2.png");
	if (main->game.texture_light_wall == NULL)
		exit_and_print("texture light wall :(", main, 0);
}

void	init_weapon(t_main *main)
{
	int	i;

	i = -1;
	while (++i < 28)
	{
		main->helper.itoa = ft_itoa(i + 1);
		if (main->helper.itoa == NULL)
			exit_and_print("Malloc failed", main, 0);
		main->helper.path = ft_strjoin(PATH, main->helper.itoa);
		if (main->helper.path == NULL)
			exit_and_print("Malloc failed", main, 0);
		main->helper.temp = ft_strjoin(main->helper.path, "_upscaled.png");
		if (main->helper.temp == NULL)
			exit_and_print("Malloc failed", main, 0);
		main->game.texture_weapon[i] = mlx_load_png(main->helper.temp);
		if (main->game.texture_weapon[i] == NULL)
			exit_and_print("texture weapon :(", main, 0);
		free(main->helper.path);
		free(main->helper.temp);
		free(main->helper.itoa);
		main->helper.path = NULL;
		main->helper.temp = NULL;
		main->helper.itoa = NULL;
	}
}

void	init_door(t_main *main)
{
	main->game.texture_door_close = mlx_load_png("assets/image/door_close.png");
	if (main->game.texture_door_close == NULL)
		exit_and_print("texture door close :(", main, 0);
	main->game.texture_door_open = mlx_load_png("assets/image/door_open.png");
	if (main->game.texture_door_open == NULL)
		exit_and_print("texture door open :(", main, 0);
}

void	init_texture(t_main *main)
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
