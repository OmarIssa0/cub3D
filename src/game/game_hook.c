/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:12:36 by oissa             #+#    #+#             */
/*   Updated: 2025/07/12 18:00:43 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	calculate_time(t_time *time, int number_array)
{
	clock_gettime(CLOCK_MONOTONIC, &time->current_time[number_array]);
	time->now[number_array] = time->current_time[number_array].tv_sec
		+ (time->current_time[number_array].tv_nsec / 1e9);
	if (time->last_time[number_array] == 0.0)
		time->last_time[number_array] = time->now[number_array];
}

void	draw_aim(t_main *m)
{
	m->draw_aim.centerX = SCREEN_WIDTH / 2;
	m->draw_aim.centerY = SCREEN_HEIGHT / 2;
	m->draw_aim.size = 5;
	m->draw_aim.thickness = 10;
	m->draw_aim.color = 0xFF0000FF;
	m->draw_aim.i = -1;
	while (++(m->draw_aim.i) < m->draw_aim.size)
	{
		m->draw_aim.y = 0;
		while (m->draw_aim.y < m->draw_aim.thickness)
		{
			if (m->draw_aim.i == SCREEN_WIDTH / 2
				|| m->draw_aim.y == SCREEN_HEIGHT / 2)
				continue ;
			mlx_put_pixel(m->game.image, m->draw_aim.centerX
				+ m->draw_aim.i, m->draw_aim.centerY, m->draw_aim.color);
			mlx_put_pixel(m->game.image, m->draw_aim.centerX
				- m->draw_aim.i, m->draw_aim.centerY, m->draw_aim.color);
			mlx_put_pixel(m->game.image, m->draw_aim.centerX,
				m->draw_aim.centerY + m->draw_aim.i, m->draw_aim.color);
			mlx_put_pixel(m->game.image, m->draw_aim.centerX,
				m->draw_aim.centerY - m->draw_aim.i, m->draw_aim.color);
			m->draw_aim.y++;
		}
	}
}

static void	toggle_door_if_player_near(t_main *main, int cornerX, int cornerY)
{
	int	z;

	z = 0;
	while (z < main->file.nb_door)
	{
		if (main->file.pos_doors[z].x == cornerX
			&& main->file.pos_doors[z].y == cornerY
			&& !((int)main->player.x == cornerX
				&& (int)main->player.y == cornerY))
		{
			main->file.pos_doors[z].is_open = !main->file.pos_doors[z].is_open;
			break ;
		}
		z++;
	}
}

void	is_player_near_door(t_main *main)
{
	int	i;
	int	j;
	int	corner_x;
	int	corner_y;

	i = (int)main->player.x;
	j = (int)main->player.y;
	corner_x = i - 1;
	while (corner_x <= i + 1)
	{
		corner_y = j - 1;
		while (corner_y <= j + 1)
		{
			if (main->file.map[corner_y][corner_x] == 'D')
			{
				toggle_door_if_player_near(main, corner_x, corner_y);
			}
			corner_y++;
		}
		corner_x++;
	}
}
