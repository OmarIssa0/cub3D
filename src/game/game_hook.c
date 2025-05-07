/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:07:21 by oissa             #+#    #+#             */
/*   Updated: 2025/05/07 18:52:25 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void map_cir(t_main *main)
{
	int radius;
	int mapX;
	int mapY;
	int centerX;
	int centerY;
	int padding;

	radius = SCREEN_WIDTH / 25;
	centerX = SCREEN_WIDTH - radius - SCREEN_WIDTH / 15;
	// Positioned on the right side
	centerY = SCREEN_HEIGHT - radius - SCREEN_WIDTH / 15;
	// Positioned 10 pixels above the bottom
	padding = 100;
	// Padding around the map
	for (int y = -radius; y <= radius; y++)
	{
		for (int x = -radius; x <= radius; x++)
		{
			if (x * x + y * y <= radius * radius)
			{
				mapX = (int)(main->player.x + (double)x * main->game.width_map / (2 * radius));
				mapY = (int)(main->player.y + (double)y * main->game.height_map / (2 * radius));
				if (mapX >= -padding && mapX < main->game.width_map + padding && mapY >= -padding && mapY < main->game.height_map + padding)
				{
					int squareSize = 2; // Size of the square for each map cell
					for (int sy = 0; sy < squareSize; sy++)
					{
						for (int sx = 0; sx < squareSize; sx++)
						{
							if (mapX < 0 || mapX >= main->game.width_map - 1 || mapY < 0 || mapY >= main->game.height_map)
								mlx_put_pixel(main->game.image, centerX + x * squareSize + sx, centerY + y * squareSize + sy, 0x00000000); // Padding color
							else if (main->file.map[mapY][mapX] == '1')
								mlx_put_pixel(main->game.image, centerX + x * squareSize + sx, centerY + y * squareSize + sy, 0xFF0000FF); // Wall color
							else if ((int)main->player.x == mapX && (int)main->player.y == mapY)
								mlx_put_pixel(main->game.image, centerX + x * squareSize + sx, centerY + y * squareSize + sy, 0x00FF00FF); // Player color
							else
								mlx_put_pixel(main->game.image, centerX + x * squareSize + sx, centerY + y * squareSize + sy, 0xFFFFFFFF); // Floor color
						}
					}
				}
			}
		}
	}
}
void calculate_time(t_time *time, int number_array)
{
	clock_gettime(CLOCK_MONOTONIC, &time->current_time[number_array]);
	time->now[number_array] = time->current_time[number_array].tv_sec + (time->current_time[number_array].tv_nsec / 1e9);
	if (time->last_time[number_array] == 0.0)
		time->last_time[number_array] = time->now[number_array];
}

void display_fps(t_main *main)
{
	static int frame_count = 0;
	static double fps = 0.0;
	static mlx_image_t *image = NULL;
	string str;

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

void draw_aim(t_main *main)
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
				continue;
			mlx_put_pixel(main->game.image, centerX + i, centerY, color);
			mlx_put_pixel(main->game.image, centerX - i, centerY, color);
			mlx_put_pixel(main->game.image, centerX, centerY + i, color);
			mlx_put_pixel(main->game.image, centerX, centerY - i, color);
			y++;
		}
		i++;
	}
}

void draw_weapon(t_main *main)
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
	if (main->game.weapon_animation < 0 || main->game.weapon_animation >= 28 || !main->game.texture_weapon[main->game.weapon_animation])
		return; // Ensure valid animation index and texture
	posX = SCREEN_WIDTH / 2 - main->game.texture_weapon[main->game.weapon_animation]->width / 2 + 100;
	posY = SCREEN_HEIGHT - main->game.texture_weapon[main->game.weapon_animation]->height;
	x = 0;
	while (x < main->game.texture_weapon[main->game.weapon_animation]->width)
	{
		y = 0;
		while (y < main->game.texture_weapon[main->game.weapon_animation]->height)
		{
			offset = (y * main->game.texture_weapon[main->game.weapon_animation]->width + x) * 4;
			r = main->game.texture_weapon[main->game.weapon_animation]->pixels[offset];
			g = main->game.texture_weapon[main->game.weapon_animation]->pixels[offset + 1];
			b = main->game.texture_weapon[main->game.weapon_animation]->pixels[offset + 2];
			a = main->game.texture_weapon[main->game.weapon_animation]->pixels[offset + 3];
			color = (r << 24) | (g << 16) | (b << 8) | a;
			if (a != 0)
				mlx_put_pixel(main->game.image, posX + x, posY + y, color);
			y++;
		}
		x++;
	}
}

void handle_keys(void *param)
{
	t_main *main;
	double move_step;
	double rot_step;

	main = (t_main *)param;
	move_step = MOV_SPEED * 0.05;
	rot_step = ROT_SPEED * 0.05;
	handle_mouse_rotation(main);
	if (mlx_is_key_down(main->game.mlx, MLX_KEY_ESCAPE))
	{
		free_all(main);
		exit(EXIT_SUCCESS);
	}
	// ? Front & Back
	if (mlx_is_key_down(main->game.mlx, MLX_KEY_W) || mlx_is_key_down(main->game.mlx, MLX_KEY_UP))
		move_player(main, main->player.dir_x * move_step, main->player.dir_y * move_step);
	if (mlx_is_key_down(main->game.mlx, MLX_KEY_S) || mlx_is_key_down(main->game.mlx, MLX_KEY_DOWN))
		move_player(main, -main->player.dir_x * move_step, -main->player.dir_y * move_step);
	// ? Side
	if (mlx_is_key_down(main->game.mlx, MLX_KEY_Q))
		move_player(main, main->player.dir_y * move_step, -main->player.dir_x * move_step);
	if (mlx_is_key_down(main->game.mlx, MLX_KEY_E))
		move_player(main, -main->player.dir_y * move_step, main->player.dir_x * move_step);
	// ? Cam
	if (mlx_is_key_down(main->game.mlx, MLX_KEY_LEFT) || mlx_is_key_down(main->game.mlx, MLX_KEY_A))
		rotate_player(&main->player, rot_step);
	if (mlx_is_key_down(main->game.mlx, MLX_KEY_RIGHT) || mlx_is_key_down(main->game.mlx, MLX_KEY_D))
		rotate_player(&main->player, -rot_step);
	if (mlx_is_key_down(main->game.mlx, MLX_KEY_SPACE) || mlx_is_mouse_down(main->game.mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		main->game.weapon_animation = 1;
	}
	// ? Display map
	cast_rays(main);
	calculate_time(&main->time, TIME_COLOR);
	draw_walls(main);
	// ? Display circler map
	// map_cir(main);
	draw_aim(main);
	draw_weapon(main);
	if (main->game.weapon_animation)
	{
		calculate_time(&main->time, TIME_ANIMATION);
		if (main->time.now[TIME_ANIMATION] - main->time.last_time[TIME_ANIMATION] >= 0.05)
		{
			main->game.weapon_animation = (main->game.weapon_animation + 1) % 28;
			main->time.last_time[TIME_ANIMATION] = main->time.now[TIME_ANIMATION];
		}
	}
	draw_2D_view(main);
	calculate_time(&main->time, TIME_FPS);
	display_fps(main);
}
