/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_tow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:30:09 by oissa             #+#    #+#             */
/*   Updated: 2025/07/14 20:40:45 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	key_time_add(t_main *main)
{
	if (PUT_CEILING == true && mlx_is_key_down(main->game.mlx, MLX_KEY_EQUAL)
		&& mlx_is_key_down(main->game.mlx, MLX_KEY_RIGHT_CONTROL))
	{
		if (!main->hook.key_pressed_space_equal)
		{
			main->time.speed += 0.5;
			if (main->time.speed > 10.0)
				main->time.speed = 10.0;
			main->hook.key_pressed_space_equal = 1;
		}
	}
	else
		main->hook.key_pressed_space_equal = 0;
}

void	key_time(t_main *main)
{
	key_time_add(main);
	if (PUT_CEILING == true && mlx_is_key_down(main->game.mlx, MLX_KEY_MINUS)
		&& mlx_is_key_down(main->game.mlx, MLX_KEY_RIGHT_CONTROL))
	{
		if (!main->hook.key_pressed_space_minus)
		{
			main->time.speed -= 0.5;
			if (main->time.speed < 0.1)
				main->time.speed = 0.1;
			main->hook.key_pressed_space_minus = 1;
		}
	}
	else
		main->hook.key_pressed_space_minus = 0;
}

static void	key_move_add(t_main *main)
{
	if (PUT_CEILING == true && mlx_is_key_down(main->game.mlx, MLX_KEY_MINUS)
		&& mlx_is_key_down(main->game.mlx, MLX_KEY_LEFT_CONTROL))
	{
		if (!main->hook.key_pressed_space_minus)
		{
			main->hook.move_step -= 0.05;
			if (main->hook.move_step < 0.05)
				main->hook.move_step = 0.05;
			main->hook.key_pressed_space_minus = 1;
		}
	}
	else
		main->hook.key_pressed_space_minus = 0;
}

void	key_move(t_main *main)
{
	key_move_add(main);
	if (PUT_CEILING == true && mlx_is_key_down(main->game.mlx, MLX_KEY_EQUAL)
		&& mlx_is_key_down(main->game.mlx, MLX_KEY_LEFT_CONTROL))
	{
		if (!main->hook.key_pressed_space_equal)
		{
			main->hook.move_step += 0.025;
			if (main->hook.move_step > 0.25)
				main->hook.move_step = 0.25;
			main->hook.key_pressed_space_equal = 1;
		}
	}
	else
		main->hook.key_pressed_space_equal = 0;
}
