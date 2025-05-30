/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:12:44 by oissa             #+#    #+#             */
/*   Updated: 2025/05/15 18:44:28 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void init_mlx(t_main *main)
{
	main->game.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", true);
	if (main->game.mlx == NULL)
		exit_and_print((char *)mlx_strerror(mlx_errno), main, 0);
	main->raycasting.line_height = ft_calloc(sizeof(int), SCREEN_WIDTH);
	if (main->raycasting.line_height == NULL)
		exit_and_print("malloc error", main, 0);
}

static void exit_clean(void *param)
{
	t_main *main;

	main = (t_main *)param;
	free_all(main);
	exit(EXIT_SUCCESS);
}

void play_sound(t_main *main)
{
	pid_t pid = fork();
	if (pid == 0)
	{
		int devnull = open("/dev/null", O_WRONLY);
		dup2(devnull, STDOUT_FILENO);
		dup2(devnull, STDERR_FILENO);
		close(devnull);
		execlp("ffplay", "ffplay", "-nodisp", "-autoexit", "-loglevel", "quiet", "assets/sound/shot.mp3", (char *)NULL);
		exit_and_print("execlp failed", main, DONT_CLOSE_FD);
	}
	else if (pid > 0)
		;
	else
		exit_and_print("fork failed", main, DONT_CLOSE_FD);
}

void keys_hook(struct mlx_key_data keydata, void *param)
{
	static int key_pressed = 0;
	t_main *main;

	main = (t_main *)param;
	// printf("key pressed: %d\n", keydata.key);
	if (key_pressed == 0 && main->player.holding && main->game.weapon_animation == 0 && keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		key_pressed = 1;
		main->game.weapon_animation = 1;
		play_sound(main);
		key_pressed = 0;
	}
	// if (keydata.key == MLX_KEY_RIGHT_CONTROL && keydata.action == MLX_RELEASE &&   keydata.key == MLX_KEY_EQUAL && keydata.action == MLX_PRESS)
	// {
	// 	main->time.speed += 0.5;
	// 	if (main->time.speed > 10.0)
	// 		main->time.speed = 10.0;
	// }
}

void init_game(t_main *main)
{
	init_texture(main);
	init_mlx(main);
	main->game.image = mlx_new_image(main->game.mlx, SCREEN_WIDTH,
									 SCREEN_HEIGHT);
	if (main->game.image == NULL)
		exit_and_print((char *)mlx_strerror(mlx_errno), main, 0);
	init_player(main);
	cast_rays(main);
	draw_walls(main);
	mlx_image_to_window(main->game.mlx, main->game.image, 0, 0);
	signal(SIGCHLD, SIG_IGN);
	main->time.speed = 1.0;
	main->hook.move_step = MOV_SPEED * 0.05;
	main->hook.rot_step = ROT_SPEED * 0.05;
	printf("hook move step: %f\n", main->hook.move_step);
	printf("hook rot step: %f\n", main->hook.rot_step);
	mlx_loop_hook(main->game.mlx, &handle_keys, main);
	mlx_close_hook(main->game.mlx, &exit_clean, main);
	mlx_key_hook(main->game.mlx, &keys_hook, main);
	mlx_set_cursor_mode(main->game.mlx, MLX_MOUSE_DISABLED);
	mlx_set_mouse_pos(main->game.mlx, SCREEN_WIDTH / 2, SCHAR_MAX / 2);
}
