/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:10:46 by oissa             #+#    #+#             */
/*   Updated: 2025/07/16 20:50:58 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	calculate_mapx_mapy(t_main *m, int *x, int y)
{
	t_rectangle	rect;

	m->map_2d.mapY = (int)(m->player.y - m->map_2d.map_size / 2 + y);
	m->map_2d.mapX = (int)(m->player.x - m->map_2d.map_size / 2
			+ (*x));
	if (m->map_2d.mapY < 0 || m->map_2d.mapY >= m->game.height_map
		|| m->map_2d.mapX < 0 || !m->file.map
		|| !m->file.map[m->map_2d.mapY]
		|| m->map_2d.mapX >= (int)ft_strlen(m->file.map[m->map_2d.mapY]))
	{
		rect.x = m->map_2d.offsetX + (*x) * TILE_SIZE;
		rect.y = m->map_2d.offsetY + y * TILE_SIZE;
		rect.width = TILE_SIZE;
		rect.height = TILE_SIZE;
		rect.color = 0x000000FF;
		mlx_draw_rectangle(m->game.image, &rect);
		(*x)++;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

void	color_door(t_main *main)
{
	if (PUT_CEILING == true && main->file.pos_doors)
	{
		main->map_2d.door_index = 0;
		while (main->file.pos_doors[main->map_2d.door_index].x
			!= main->map_2d.mapX
			|| main->file.pos_doors[main->map_2d.door_index].y
			!= main->map_2d.mapY)
			main->map_2d.door_index++;
		if (main->file.pos_doors[main->map_2d.door_index].is_open == 1)
			main->map_2d.color = 0x0000FFFF;
		else
			main->map_2d.color = 0xFF0000FF;
	}
	else
		main->map_2d.color = 0xFFFFFF00;
}

int	onther_draw_map(t_main *main, int *x, int y)
{
	t_rectangle	rect;

	rect.x = main->map_2d.offsetX + (*x) * TILE_SIZE;
	rect.y = main->map_2d.offsetY + y * TILE_SIZE;
	rect.width = TILE_SIZE;
	rect.height = TILE_SIZE;
	rect.color = 0x000000FF;
	mlx_draw_rectangle(main->game.image, &rect);
	(*x)++;
	return (EXIT_SUCCESS);
}

int	give_color(t_main *main, int *x, int y)
{
	main->map_2d.tile = main->file.map[main->map_2d.mapY][main->map_2d.mapX];
	main->map_2d.color = 0;
	if (main->map_2d.tile == '1')
		main->map_2d.color = 0xFFFFFF00;
	else if (main->map_2d.tile == '0')
		main->map_2d.color = 0x009000FF;
	else if (main->map_2d.tile == 'N' || main->map_2d.tile == 'S'
		|| main->map_2d.tile == 'E' || main->map_2d.tile == 'W')
		main->map_2d.color = 0xFFFF00FF;
	else if (main->map_2d.tile == 'D')
		color_door(main);
	else
	{
		if (onther_draw_map(main, x, y) == EXIT_SUCCESS)
			return (2);
	}
	return (EXIT_SUCCESS);
}
