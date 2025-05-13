/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:12:44 by oissa             #+#    #+#             */
/*   Updated: 2025/05/13 08:12:47 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_mlx(t_main *main)
{
	main->game.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", true);
	if (main->game.mlx == NULL)
		exit_and_print((char *)mlx_strerror(mlx_errno), main, 0);
	main->raycasting.line_height = ft_calloc(sizeof(int), SCREEN_WIDTH);
	if (main->raycasting.line_height == NULL)
		exit_and_print("malloc error", main, 0);
}

static void	exit_clean(void *param)
{
	t_main	*main;

	main = (t_main *)param;
	free_all(main);
	exit(EXIT_SUCCESS);
}

void	init_game(t_main *main)
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
	mlx_loop_hook(main->game.mlx, &handle_keys, main);
	mlx_close_hook(main->game.mlx, &exit_clean, main);
	mlx_set_cursor_mode(main->game.mlx, MLX_MOUSE_DISABLED);
	mlx_set_mouse_pos(main->game.mlx, SCREEN_WIDTH / 2, SCHAR_MAX / 2);
}
