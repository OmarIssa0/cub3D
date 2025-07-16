/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_too.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 22:02:56 by oissa             #+#    #+#             */
/*   Updated: 2025/07/16 21:06:01 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_horizontal_line(t_main *main, int x, int y, t_line *line)
{
	line->x0 = main->map_2d.offset_x + x * TILE_SIZE;
	line->y0 = main->map_2d.offset_y + y * TILE_SIZE;
	line->x1 = main->map_2d.offset_x + (x + 1) * TILE_SIZE;
	line->y1 = main->map_2d.offset_y + y * TILE_SIZE;
	line->color = main->map_2d.border;
	line->thickness = 1;
	mlx_draw_line_thick(main->game.image, *line);
}

void	draw_vertical_line(t_main *main, int x, int y, t_line *line)
{
	line->x0 = main->map_2d.offset_x + x * TILE_SIZE;
	line->y0 = main->map_2d.offset_y + y * TILE_SIZE;
	line->x1 = main->map_2d.offset_x + x * TILE_SIZE;
	line->y1 = main->map_2d.offset_y + (y + 1) * TILE_SIZE;
	line->color = main->map_2d.border;
	line->thickness = 1;
	mlx_draw_line_thick(main->game.image, *line);
}

void	draw_player_rectangle(t_main *t)
{
	t_rectangle	player_rect;

	t->map_2d.px = t->map_2d.offset_x + (t->player.x - (int)t->player.x)
		* TILE_SIZE + t->map_2d.map_size / 2 * TILE_SIZE;
	t->map_2d.py = t->map_2d.offset_y + (t->player.y - (int)t->player.y)
		* TILE_SIZE + t->map_2d.map_size / 2 * TILE_SIZE;
	player_rect.x = t->map_2d.px - 3;
	player_rect.y = t->map_2d.py - 3;
	player_rect.width = 6;
	player_rect.height = 6;
	player_rect.color = 0xFF0000FF;
	mlx_draw_rectangle(t->game.image, &player_rect);
}
