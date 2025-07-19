/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_too.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 22:02:56 by oissa             #+#    #+#             */
/*   Updated: 2025/07/19 03:03:16 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_horizontal_line(t_main *main, int x, int y, t_line *line)
{
	line->x0 = main->map_2d.offset_x + x * main->map_2d.tile_size;
	line->y0 = main->map_2d.offset_y + y * main->map_2d.tile_size;
	line->x1 = main->map_2d.offset_x + (x + 1) * main->map_2d.tile_size;
	line->y1 = main->map_2d.offset_y + y * main->map_2d.tile_size;
	line->color = main->map_2d.border;
	line->thickness = 1;
	mlx_draw_line_thick(main->game.image, *line);
}

void	draw_vertical_line(t_main *main, int x, int y, t_line *line)
{
	line->x0 = main->map_2d.offset_x + x * main->map_2d.tile_size;
	line->y0 = main->map_2d.offset_y + y * main->map_2d.tile_size;
	line->x1 = main->map_2d.offset_x + x * main->map_2d.tile_size;
	line->y1 = main->map_2d.offset_y + (y + 1) * main->map_2d.tile_size;
	line->color = main->map_2d.border;
	line->thickness = 1;
	mlx_draw_line_thick(main->game.image, *line);
}

void	draw_player_rectangle(t_main *t)
{
	t_rectangle	player_rect;

	t->map_2d.px = t->map_2d.offset_x + (t->player.x - (int)t->player.x)
		* t->map_2d.tile_size + t->map_2d.map_size / 2 * t->map_2d.tile_size;
	t->map_2d.py = t->map_2d.offset_y + (t->player.y - (int)t->player.y)
		* t->map_2d.tile_size + t->map_2d.map_size / 2 * t->map_2d.tile_size;
	player_rect.x = t->map_2d.px - 3;
	player_rect.y = t->map_2d.py - 3;
	player_rect.width = 6;
	player_rect.height = 6;
	player_rect.color = 0xFF0000FF;
	mlx_draw_rectangle(t->game.image, &player_rect);
}
