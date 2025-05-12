/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/05/09 00:57:26 by oissa             #+#    #+#             */
/*   Updated: 2025/05/09 00:57:26 by oissa            ###   ########.fr       */
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

void	display_fps(t_main *main)
{
	static int frame_count = 0;
	static double fps = 0.0;
	static mlx_image_t *image = NULL;
	char * str;

	frame_count++;
	if (main->time.now[0] - main->time.last_time[0] >= 1.0)
	{
		fps = frame_count / (main->time.now[0] - main->time.last_time[0]);
		frame_count = 0;
		main->time.last_time[0] = main->time.now[0];
		str = ft_itoa((int)fps);
		char *temp = str;
		str = ft_strjoin("FPS: ", str);
		free(temp);
		if (image)
			mlx_delete_image(main->game.mlx, image);
		image = mlx_put_string(main->game.mlx, str, 10, 10);
		free(str);
	}
}

void	draw_aim(t_main *main)
{
	int centerX;
	int centerY;
	int i;
	int size;
	int thickness;
	int color;
	int y;

	centerX = SCREEN_WIDTH / 2;
	centerY = SCREEN_HEIGHT / 2;
	size = 5;
	thickness = 10;
	color = 0xFF0000FF;
	i = 0;
	while (i < size)
	{
		y = 0;
		while (y < thickness)
		{
			if (i == SCREEN_WIDTH / 2 || y == SCREEN_HEIGHT / 2)
				continue ;
			mlx_put_pixel(main->game.image, centerX + i, centerY, color);
			mlx_put_pixel(main->game.image, centerX - i, centerY, color);
			mlx_put_pixel(main->game.image, centerX, centerY + i, color);
			mlx_put_pixel(main->game.image, centerX, centerY - i, color);
			y++;
		}
		i++;
	}
}

void	draw_weapon(t_main *main)
{
	int posX;
	int posY;
	uint32_t x;
	uint32_t y;
	size_t offset;
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
	uint32_t color;

	// Center the weapon
	if (main->game.weapon_animation < 0 || main->game.weapon_animation >= 28
		|| !main->game.texture_weapon[main->game.weapon_animation])
		return ; // Ensure valid animation index and texture
	posX = SCREEN_WIDTH / 2
		- main->game.texture_weapon[main->game.weapon_animation]->width / 2
		+ 100;
	posY = SCREEN_HEIGHT
		- main->game.texture_weapon[main->game.weapon_animation]->height;
	x = 0;
	while (x < main->game.texture_weapon[main->game.weapon_animation]->width)
	{
		y = 0;
		while (y < main->game.texture_weapon[main->game.weapon_animation]->height)
		{
			offset = (y
					* main->game.texture_weapon[main->game.weapon_animation]->width
					+ x) * 4;
			r = main->game.texture_weapon[main->game.weapon_animation]->pixels[offset];
			g = main->game.texture_weapon[main->game.weapon_animation]->pixels[offset
				+ 1];
			b = main->game.texture_weapon[main->game.weapon_animation]->pixels[offset
				+ 2];
			a = main->game.texture_weapon[main->game.weapon_animation]->pixels[offset
				+ 3];
			color = (r << 24) | (g << 16) | (b << 8) | a;
			if (a != 0)
				mlx_put_pixel(main->game.image, posX + x, posY + y, color);
			y++;
		}
		x++;
	}
}

void	is_player_near_door(t_main *main)
{
	int i;
	int j;
	int z;
	int cornerX;
	int cornerY;
	i = (int)main->player.x;
	j = (int)main->player.y;
	cornerX = i - 1;
	cornerY = j - 1;
	z = 0;
	while (cornerX <= i + 1)
	{
		cornerY = j - 1;
		while (cornerY <= j + 1)
		{
			if (main->file.map[cornerY][cornerX] == 'D')
			{
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
			cornerY++;
		}
		cornerX++;
	}
}

void	handle_keys(void *param)
{
	t_main *main;
	double move_step;
	double rot_step;
	static int key_pressed = 0;
	static int key_pressed_too = 0;
	main = (t_main *)param;
	move_step = MOV_SPEED * 0.05;
	rot_step = ROT_SPEED * 0.05;
	handle_mouse_rotation(main);
	if (mlx_is_key_down(main->game.mlx, MLX_KEY_ESCAPE) && !key_pressed)
	{
		free_all(main);
		exit(EXIT_SUCCESS);
	}
	// ? Front & Back
	if (mlx_is_key_down(main->game.mlx, MLX_KEY_W)
		|| mlx_is_key_down(main->game.mlx, MLX_KEY_UP))
		move_player(main, main->player.dir_x * move_step, main->player.dir_y
			* move_step);
	if (mlx_is_key_down(main->game.mlx, MLX_KEY_S)
		|| mlx_is_key_down(main->game.mlx, MLX_KEY_DOWN))
		move_player(main, -main->player.dir_x * move_step, -main->player.dir_y
			* move_step);
	// ? Side
	if (mlx_is_key_down(main->game.mlx, MLX_KEY_Q))
		move_player(main, main->player.dir_y * move_step, -main->player.dir_x
			* move_step);
	if (mlx_is_key_down(main->game.mlx, MLX_KEY_E))
		move_player(main, -main->player.dir_y * move_step, main->player.dir_x
			* move_step);
	// ? Cam
	if (mlx_is_key_down(main->game.mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(main->game.mlx, MLX_KEY_A))
		rotate_player(&main->player, rot_step);
	if (mlx_is_key_down(main->game.mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(main->game.mlx, MLX_KEY_D))
		rotate_player(&main->player, -rot_step);
	if (main->player.holding && (mlx_is_key_down(main->game.mlx, MLX_KEY_SPACE)
			|| mlx_is_mouse_down(main->game.mlx, MLX_MOUSE_BUTTON_LEFT)))
		main->game.weapon_animation = 1;

	if (PUT_CEILING == true && mlx_is_key_down(main->game.mlx, MLX_KEY_F))
	{
		if (!key_pressed)
		{
			is_player_near_door(main);
			key_pressed = 1;
		}
	}
	else
	{
		key_pressed = 0;
	}
	if (PUT_CEILING == true && mlx_is_key_down(main->game.mlx, MLX_KEY_R))
	{
		if (!key_pressed_too)
		{
			main->player.holding = !main->player.holding;
			key_pressed_too = 1;
		}
	}
	else
	{
		key_pressed_too = 0;
	}
	// ? Display map
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
				- main->time.last_time[TIME_ANIMATION] >= 0.05)
			{
				main->game.weapon_animation = (main->game.weapon_animation + 1)
					% 28;
				main->time.last_time[TIME_ANIMATION] = main->time.now[TIME_ANIMATION];
			}
		}
	}
	if (PUT_CEILING == true)
		draw_2D_view(main);
	calculate_time(&main->time, TIME_FPS);
	display_fps(main);
}
