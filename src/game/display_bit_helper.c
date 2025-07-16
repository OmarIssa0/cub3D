/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bit_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:00:00 by oissa             #+#    #+#             */
/*   Updated: 2025/07/16 21:20:03 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_wall_texture(t_main *main)
{
	main->draw_bit.texture = NULL;
	if (main->draw_bit.side == 0)
	{
		if (main->raycasting.ray_dir_x[main->draw_bit.x] > 0)
			main->draw_bit.texture = main->game.texture_west;
		else
			main->draw_bit.texture = main->game.texture_east;
	}
	else
	{
		if (main->raycasting.ray_dir_y[main->draw_bit.x] > 0)
			main->draw_bit.texture = main->game.texture_north;
		else
			main->draw_bit.texture = main->game.texture_south;
	}
	if (!main->draw_bit.texture || !main->draw_bit.texture->pixels)
		exit_and_print("Texture not loaded", main, DONT_CLOSE_FD);
}

void	calculate_tex_x(t_main *main)
{
	main->draw_bit.tex_x = (int)(main->draw_bit.wall_x
			* main->draw_bit.texture->width);
	if ((main->draw_bit.side == 0
			&& main->raycasting.ray_dir_x[main->draw_bit.x] > 0)
		|| (main->draw_bit.side == 1
			&& main->raycasting.ray_dir_y[main->draw_bit.x] < 0))
		main->draw_bit.tex_x = main->draw_bit.texture->width
			- main->draw_bit.tex_x - 1;
	if (main->draw_bit.tex_x < 0)
		main->draw_bit.tex_x = 0;
	if (main->draw_bit.tex_x >= (int)main->draw_bit.texture->width)
		main->draw_bit.tex_x = main->draw_bit.texture->width - 1;
}

void	select_wall_texture(t_main *main, int i)
{
	if (PUT_CEILING == true && main->raycasting.is_door[main->draw_bit.x])
	{
		if (main->raycasting.is_door[main->draw_bit.x] == 2)
			main->draw_bit.texture = main->game.texture_door_close;
		else if (main->raycasting.is_door[main->draw_bit.x] == 1)
			main->draw_bit.texture = main->game.texture_door_open;
	}
	else if (PUT_CEILING == true && i < 2)
		main->draw_bit.texture = main->game.texture_light_wall;
	else if (PUT_CEILING == true && i == 2)
		main->draw_bit.texture = main->game.texture_mid_wall;
	else if (PUT_CEILING == true && i <= 4)
		main->draw_bit.texture = main->game.texture_north;
	if (!main->draw_bit.texture || !main->draw_bit.texture->pixels)
		exit_and_print("Wall texture not loaded", main, DONT_CLOSE_FD);
}

void	draw_ceiling(t_main *main, int i)
{
	if (PUT_CEILING == true)
		mlx_put_pixel(main->game.image, main->draw_bit.x, main->draw_bit.y,
			main->game.night_and_day[i]);
	else
		mlx_put_pixel(main->game.image, main->draw_bit.x, main->draw_bit.y,
			main->game.color_ceiling);
}
