/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_three.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 21:38:25 by oissa             #+#    #+#             */
/*   Updated: 2025/07/19 03:03:08 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line_and_rectangle(t_main *main, int x, int y)
{
	t_rectangle	rect;
	t_line		line;

	ft_bzero(&rect, sizeof(t_rectangle));
	ft_bzero(&line, sizeof(t_line));
	rect.x = main->map_2d.offset_x + x * main->map_2d.tile_size;
	rect.y = main->map_2d.offset_y + y * main->map_2d.tile_size;
	rect.width = main->map_2d.tile_size;
	rect.height = main->map_2d.tile_size;
	rect.color = main->map_2d.color;
	mlx_draw_rectangle(main->game.image, &rect);
	main->map_2d.border = 0x000000FF;
	draw_horizontal_line(main, x, y, &line);
	draw_vertical_line(main, x, y, &line);
}

void	draw_thik(t_main *main)
{
	t_line	line;

	draw_player_rectangle(main);
	line.x0 = main->map_2d.px;
	line.y0 = main->map_2d.py;
	line.x1 = main->map_2d.px + main->player.dir_x * 1;
	line.y1 = main->map_2d.py + main->player.dir_y * 1;
	line.color = 0xFF0000FF;
	line.thickness = 4;
	mlx_draw_line_thick(main->game.image, line);
}

void	init_map_params(t_main *main)
{
	int	minimap_size;

	if (SCREEN_WIDTH < SCREEN_HEIGHT)
		minimap_size = (SCREEN_WIDTH * 20) / 100;
	else
		minimap_size = (SCREEN_HEIGHT * 20) / 100;
	main->map_2d.map_size = 15;
	main->map_2d.tile_size = minimap_size / main->map_2d.map_size;
	if (main->map_2d.tile_size < 1)
		main->map_2d.tile_size = 1;
	main->map_2d.offset_y = SCREEN_HEIGHT - (main->map_2d.map_size
			* main->map_2d.tile_size) - 10;
	main->map_2d.offset_x = 10;
}

void	draw_map_row(t_main *main, int y)
{
	int	x;

	x = 0;
	while (x < main->map_2d.map_size)
	{
		if (calculate_map_x_map_y(main, &x, y) == EXIT_FAILURE)
		{
			x++;
			continue ;
		}
		if (give_color(main, &x, y) == 2)
		{
			x++;
			continue ;
		}
		draw_line_and_rectangle(main, x, y);
		x++;
	}
}

void	draw_map(t_main *main)
{
	int	y;

	init_map_params(main);
	y = 0;
	while (y < main->map_2d.map_size)
	{
		draw_map_row(main, y);
		y++;
	}
	draw_thik(main);
}
