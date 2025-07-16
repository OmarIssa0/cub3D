/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:18:17 by oissa             #+#    #+#             */
/*   Updated: 2025/07/14 21:03:46 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	display_map_for_hook(t_main *main)
{
	cast_rays(main);
	calculate_time(&main->time, TIME_COLOR);
	draw_walls(main);
	if (main->player.holding)
	{
		draw_aim(main);
		draw_weapon(main);
		if (main->game.weapon_animation)
		{
			calculate_time(&main->time, TIME_ANIMATION);
			if (main->time.now[TIME_ANIMATION]
				- main->time.last_time[TIME_ANIMATION] >= 0.045)
			{
				main->game.weapon_animation
					= (main->game.weapon_animation + 1) % 28;
				main->time.last_time[TIME_ANIMATION]
					= main->time.now[TIME_ANIMATION];
			}
		}
	}
	if (PUT_CEILING == true)
		draw_2d_view(main);
	calculate_time(&main->time, TIME_FPS);
	display_fps(main);
}

static void	front_back_movement(t_main *main)
{
	if (mlx_is_key_down(main->game.mlx, MLX_KEY_W)
		|| mlx_is_key_down(main->game.mlx, MLX_KEY_UP))
		move_player(main, main->player.dir_x * main->hook.move_step,
			main->player.dir_y * main->hook.move_step);
	if (mlx_is_key_down(main->game.mlx, MLX_KEY_S)
		|| mlx_is_key_down(main->game.mlx, MLX_KEY_DOWN))
		move_player(main, -main->player.dir_x * main->hook.move_step,
			-main->player.dir_y * main->hook.move_step);
	if (mlx_is_key_down(main->game.mlx, MLX_KEY_Q))
		move_player(main, main->player.dir_y * main->hook.move_step,
			-main->player.dir_x * main->hook.move_step);
	if (mlx_is_key_down(main->game.mlx, MLX_KEY_E))
		move_player(main, -main->player.dir_y * main->hook.move_step,
			main->player.dir_x * main->hook.move_step);
	if (mlx_is_key_down(main->game.mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(main->game.mlx, MLX_KEY_A))
		rotate_player(&main->player, -main->hook.rot_step);
	if (mlx_is_key_down(main->game.mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(main->game.mlx, MLX_KEY_D))
		rotate_player(&main->player, main->hook.rot_step);
}

static void	handle_r_and_f(t_main *main)
{
	if (PUT_CEILING == true && mlx_is_key_down(main->game.mlx, MLX_KEY_F))
	{
		if (!main->hook.key_pressed)
		{
			is_player_near_door(main);
			main->hook.key_pressed = 1;
		}
	}
	else
		main->hook.key_pressed = 0;
	if (PUT_CEILING == true && mlx_is_key_down(main->game.mlx, MLX_KEY_R))
	{
		if (!main->hook.key_pressed_hoding)
		{
			main->player.holding = !main->player.holding;
			main->hook.key_pressed_hoding = 1;
		}
	}
	else
		main->hook.key_pressed_hoding = 0;
}

void	handle_keys(void *param)
{
	t_main	*main;

	main = (t_main *)param;
	handle_mouse_rotation(main);
	if (mlx_is_key_down(main->game.mlx, MLX_KEY_ESCAPE)
		&& !main->hook.key_pressed)
	{
		free_all(main);
		exit(EXIT_SUCCESS);
	}
	front_back_movement(main);
	handle_r_and_f(main);
	key_time(main);
	key_move(main);
	display_map_for_hook(main);
}
