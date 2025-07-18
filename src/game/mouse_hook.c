/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:11:03 by oissa             #+#    #+#             */
/*   Updated: 2025/07/18 19:05:04 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	rotate_player(t_player *p, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(angle) - p->plane_y
		* sin(angle);
	p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}

int	find_specific_door(t_main *main, double x, double y)
{
	int	i;

	i = 0;
	while (i < main->file.nb_door)
	{
		if (main->file.pos_doors[i].x == (int)x
			&& main->file.pos_doors[i].y == (int)y
			&& main->file.pos_doors[i].is_open == 1)
			return (1);
		i++;
	}
	return (0);
}

void	move_player(t_main *m, double move_x, double move_y)
{
	m->mouse.new_x = m->player.x + move_x;
	m->mouse.new_y = m->player.y + move_y;
	m->mouse.col_x_min = m->mouse.new_x - 0.05;
	m->mouse.col_x_max = m->mouse.new_x + 0.05;
	m->mouse.col_y_min = m->mouse.new_y - 0.05;
	m->mouse.col_y_max = m->mouse.new_y + 0.05;
	if (m->file.map[(int)m->player.y][(int)m->mouse.col_x_min] != '1'
		&& m->file.map[(int)m->player.y][(int)m->mouse.col_x_max] != '1'
		&& !(m->file.map[(int)m->player.y][(int)m->mouse.col_x_min] == 'D'
			&& !find_specific_door(m, m->mouse.col_x_min, m->player.y))
		&& !(m->file.map[(int)m->player.y][(int)m->mouse.col_x_max] == 'D'
			&& !find_specific_door(m, m->mouse.col_x_max, m->player.y)))
		m->player.x = m->mouse.new_x;
	if (m->file.map[(int)m->mouse.col_y_min][(int)m->player.x] != '1'
		&& m->file.map[(int)m->mouse.col_y_max][(int)m->player.x] != '1'
		&& !(m->file.map[(int)m->mouse.col_y_min][(int)m->player.x] == 'D'
			&& !find_specific_door(m, m->player.x, m->mouse.col_y_min))
		&& !(m->file.map[(int)m->mouse.col_y_max][(int)m->player.x] == 'D'
			&& !find_specific_door(m, m->player.x, m->mouse.col_y_max)))
		m->player.y = m->mouse.new_y;
}

void	handle_mouse_rotation(t_main *m)
{
	static int	last_x;

	last_x = SCREEN_WIDTH / 2;
	mlx_get_mouse_pos(m->game.mlx, &m->mouse.current_x, &m->mouse.current_y);
	m->mouse.delta_x = m->mouse.current_x - last_x;
	last_x = m->mouse.current_x;
	if (m->mouse.delta_x != 0)
	{
		m->mouse.sensitivity = 0.0005f;
		m->mouse.angle = m->mouse.delta_x * m->mouse.sensitivity;
		rotate_player(&m->player, m->mouse.angle);
	}
	mlx_set_mouse_pos(m->game.mlx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	last_x = SCREEN_WIDTH / 2;
}
