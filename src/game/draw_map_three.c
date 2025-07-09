/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_three.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 21:38:25 by oissa             #+#    #+#             */
/*   Updated: 2025/07/09 21:38:30 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line_and_rectangle(t_main *main, int x, int y)
{
	t_rectangle	rect;
	t_line		line;

	ft_bzero(&rect, sizeof(t_rectangle));
	ft_bzero(&line, sizeof(t_line));
	rect.x = main->map_2d.offsetX + x * TILE_SIZE;
	rect.y = main->map_2d.offsetY + y * TILE_SIZE;
	rect.width = TILE_SIZE;
	rect.height = TILE_SIZE;
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
	main->map_2d.map_size = 12;
	main->map_2d.offsetY = SCREEN_HEIGHT - (main->map_2d.map_size * TILE_SIZE)
		- 10;
	main->map_2d.offsetX = 10;
}

void	draw_map_row(t_main *main, int y)
{
	int	x;

	x = 0;
	while (x < main->map_2d.map_size)
	{
		if (calculate_mapx_mapy(main, &x, y) == EXIT_SUCCESS)
			continue ;
		if (give_color(main, &x, y) == 2)
			continue ;
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
