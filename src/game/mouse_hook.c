/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:11:03 by oissa             #+#    #+#             */
/*   Updated: 2025/05/09 01:33:41 by lalhindi         ###   ########.fr       */
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
double	calculate_distance_player_wall(t_main *main, double x, double y)
{
	double	distance;
	int		map_x;
	int		map_y;

	distance = 0.0;
	double dx, dy;
	map_x = (int)x;
	map_y = (int)y;
	while (map_x >= 0 && map_x < main->game.width_map && map_y >= 0
		&& map_y < main->game.height_map)
	{
		if (main->file.map[map_y][map_x] == '1')
		{
			dx = map_x + 0.5 - x;
			dy = map_y + 0.5 - y;
			distance = sqrt(dx * dx + dy * dy);
			break ;
		}
		if (x > main->player.x)
			map_x++;
		else if (x < main->player.x)
			map_x--;
		if (y > main->player.y)
			map_y++;
		else if (y < main->player.y)
			map_y--;
	}
	return (distance);
}
void	move_player(t_main *main, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = main->player.x + move_x;
	new_y = main->player.y + move_y;
	if (calculate_distance_player_wall(main, new_x, main->player.y) < 0.8)
		return ;
	if (new_x < 0 || new_x >= main->game.width_map || new_y < 0
		|| new_y >= main->game.height_map)
		return ;
	if (main->file.map[(int)new_y][(int)main->player.x] != '1'
		&& !(main->file.map[(int)new_y][(int)main->player.x] == 'D'
			&& !find_specific_door(main, main->player.x, new_y)))
		main->player.y = new_y;
	if (main->file.map[(int)main->player.y][(int)new_x] != '1'
		&& !(main->file.map[(int)main->player.y][(int)new_x] == 'D'
			&& !find_specific_door(main, new_x, main->player.y)))
		main->player.x = new_x;
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
		rotate_player(&main->player, angle); // دالة تدور اتجاه اللاعب
	}
	// نعيد ضبط المؤشر للمنتصف كل مرة (لأنه ما يخرجش)
	mlx_set_mouse_pos(main->game.mlx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	last_x = SCREEN_WIDTH / 2;
}
