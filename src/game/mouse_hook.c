/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:11:03 by oissa             #+#    #+#             */
/*   Updated: 2025/05/09 20:15:36 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	rotate_player(t_player *player, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(angle) - player->plane_y
		* sin(angle);
	player->plane_y = old_plane_x * sin(angle) + player->plane_y * cos(angle);
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

void	move_player(t_main *main, double move_x, double move_y)
{
	double	new_x;
	double	new_y;
	double	col_x_min;
	double	col_x_max;
	double	col_y_min;
	double	col_y_max;

	new_x = main->player.x + move_x;
	new_y = main->player.y + move_y;
	col_x_min = new_x - 0.05;
	col_x_max = new_x + 0.05;
	col_y_min = new_y - 0.05;
	col_y_max = new_y + 0.05;
	if (main->file.map[(int)main->player.y][(int)col_x_min] != '1'
		&& main->file.map[(int)main->player.y][(int)col_x_max] != '1'
		&& !(main->file.map[(int)main->player.y][(int)col_x_min] == 'D'
			&& !find_specific_door(main, col_x_min, main->player.y))
		&& !(main->file.map[(int)main->player.y][(int)col_x_max] == 'D'
			&& !find_specific_door(main, col_x_max, main->player.y)))
		main->player.x = new_x;
	if (main->file.map[(int)col_y_min][(int)main->player.x] != '1'
		&& main->file.map[(int)col_y_max][(int)main->player.x] != '1'
		&& !(main->file.map[(int)col_y_min][(int)main->player.x] == 'D'
			&& !find_specific_door(main, main->player.x, col_y_min))
		&& !(main->file.map[(int)col_y_max][(int)main->player.x] == 'D'
			&& !find_specific_door(main, main->player.x, col_y_max)))
		main->player.y = new_y;
}
void	handle_mouse_rotation(t_main *main)
{
	static int	last_x = SCREEN_WIDTH / 2;
	int			delta_x;
	float		sensitivity;
	float		angle;

	int current_x, current_y;
	mlx_get_mouse_pos(main->game.mlx, &current_x, &current_y);
	delta_x = current_x - last_x;
	last_x = current_x;
	if (delta_x != 0)
	{
		sensitivity = 0.0005f;
		angle = delta_x * sensitivity;
		rotate_player(&main->player, angle);
	}
	mlx_set_mouse_pos(main->game.mlx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	last_x = SCREEN_WIDTH / 2;
}
