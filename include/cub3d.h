/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 06:36:08 by oissa             #+#    #+#             */
/*   Updated: 2025/07/16 20:50:10 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"
# define PURPLE "\033[0;35m"
# define WHITE "\033[0;37m"
# define BLUE "\033[0;34m"
# define YELLOW "\033[0;33m"

# define SCREEN_WIDTH 2000
# define SCREEN_HEIGHT 1000
// # define SCREEN_WIDTH 700
// # define SCREEN_HEIGHT 600
# define TILE_SIZE 10
# define PUT_FLOOR true
# define PUT_CEILING true
# define PATH "assets/image/Super Shotgun/"
# define MOV_SPEED 1.0
# define ROT_SPEED 1.0
# define MAX_FLOAT 3.402823466e+38F

# include "MLX42/MLX42.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <pthread.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

typedef enum e_num
{
	WALL = '1',
	FLOOR = '0',
	SPACE = ' ',
	TIME_FPS = 0,
	TIME_COLOR = 1,
	TIME_ANIMATION = 2,
	CLOSE_FD = 1,
	DONT_CLOSE_FD = 0,
}					t_num;

typedef struct s_hook
{
	double			move_step;
	double			rot_step;
	int				key_pressed;
	int				key_pressed_hoding;
	int				key_pressed_space_equal;
	int				key_pressed_space_minus;
}					t_hook;

typedef struct s_time
{
	struct timespec	current_time[3];
	double			now[3];
	double			last_time[3];
	double			speed;
}					t_time;

typedef struct s_math
{
	float			camera_x;
	float			ray_dir_x;
	float			ray_dir_y;
	int				map_x;
	int				map_y;
	float			delta_dist_x;
	float			delta_dist_y;
	float			side_dist_x;
	float			side_dist_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	float			perp_wall_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
	float			wall_x;
}					t_math;

typedef struct s_player
{
	float			x;
	float			y;
	float			dir_x;
	float			dir_y;
	float			plane_x;
	float			plane_y;
	float			z;
	bool			holding;
}					t_player;

typedef struct s_raycasting
{
	int				*line_height;
	int				draw_start[SCREEN_WIDTH];
	int				draw_end[SCREEN_WIDTH];
	int				side[SCREEN_WIDTH];
	float			wall_x[SCREEN_WIDTH];
	float			ray_dir_x[SCREEN_WIDTH];
	float			ray_dir_y[SCREEN_WIDTH];
	int				is_door[SCREEN_WIDTH];
}					t_raycasting;

typedef struct s_helper
{
	int				index;
	char			*line_color_floor;
	char			*line_color_ceiling;
	char			**color_floor;
	char			**color_ceiling;
	char			*trim;
	char			*trimmed_result;
	char			*path;
	char			*temp;
	char			*itoa;
	int				j;
	int				count_values_ceiling;
	int				count_values_floor;
	int				count_values_north;
	int				count_values_south;
	int				count_values_west;
	int				count_values_east;
	int				skip_space;
	int				surface[2];
	int				x;
	int				y;
	int				new_i;
	int				new_j;
	int				new_x;
	int				new_y;
	int				player;
	pthread_mutex_t	mutex;
}					t_helper;

typedef struct s_game
{
	int				player_x;
	int				player_y;
	int				height_map;
	int				width_map;
	char			player_direction;
	double			time;
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_texture_t	*texture_north;
	mlx_texture_t	*texture_south;
	mlx_texture_t	*texture_west;
	mlx_texture_t	*texture_east;
	mlx_texture_t	*texture_light_wall;
	mlx_texture_t	*texture_mid_wall;
	mlx_texture_t	*texture_floor;
	mlx_texture_t	*texture_door_open;
	mlx_texture_t	*texture_door_close;
	mlx_texture_t	*texture_weapon[28];
	int				weapon_animation;
	uint32_t		night_and_day[25];
	uint32_t		color_ceiling;
	uint32_t		color_floor;
}					t_game;

typedef struct s_point
{
	int				x;
	int				y;
	bool			is_open;
}					t_point;

typedef struct s_file
{
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	int				floor_color[3];
	int				ceiling_color[3];
	char			**map;
	int				nb_door;
	t_point			*pos_doors;
}					t_file;

typedef struct s_splitter
{
	char			**lines;
	int				i;
	int				j;
	int				k;
	int				len;
	int				remander_index;
}					t_splitter;

typedef struct t_line
{
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	uint32_t		color;
	int				thickness;
}					t_line;

typedef struct s_2d
{
	int				map_size;
	int				offsetY;
	int				offsetX;
	int				mapY;
	int				mapX;
	char			tile;
	uint32_t		color;
	int				door_index;
	uint32_t		border;
	int				px;
	int				py;
}					t_2d;

typedef struct s_rays_2d
{
	float			cameraX;
	float			rayDirX;
	float			rayDirY;
	int				mapX;
	int				mapY;
	float			deltaDistX;
	float			deltaDistY;
	int				hit;
	int				side;
	float			perpWallDist;
	float			rayStartX;
	float			rayStartY;
	float			rayEndX;
	float			rayEndY;
	float			minX;
	float			minY;
	float			maxX;
	float			maxY;
	int				map_size;
	int				offsetY;
	int				offsetX;
	float			stepY;
	float			stepX;
	float			sideDistX;
	float			sideDistY;
}					t_rays_2d;

typedef struct s_rectangle
{
	int				x;
	int				y;
	int				width;
	int				height;
	uint32_t		color;
}					t_rectangle;

typedef struct s_mouse
{
	int				delta_x;
	float			sensitivity;
	float			angle;
	int				current_x;
	int				current_y;
	double			new_x;
	double			new_y;
	double			col_x_min;
	double			col_x_max;
	double			col_y_min;
	double			col_y_max;
}					t_mouse;

typedef struct s_draw_weapon
{
	int				posX;
	int				posY;
	uint32_t		x;
	uint32_t		y;
	size_t			offset;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;
	uint32_t		color;
}					t_draw_weapon;

typedef struct s_draw_aim
{
	int				centerX;
	int				centerY;
	int				i;
	int				size;
	int				thickness;
	int				color;
	int				y;
}					t_draw_aim;

typedef struct s_draw_bit
{
	int				x;
	int				y;
	int				texX;
	int				texY;
	float			wallX;
	mlx_texture_t	*texture;
	int				side;
}					t_draw_bit;

typedef struct s_line_thick
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				half_thick;
	int				px;
	int				py;
	int				e2;
}					t_line_thick;

typedef struct s_main
{
	int				fd;
	char			*file_name;
	char			*result;
	t_file			file;
	t_splitter		split;
	t_game			game;
	t_helper		helper;
	t_player		player;
	t_raycasting	raycasting;
	t_math			math;
	t_time			time;
	t_hook			hook;
	t_2d			map_2d;
	t_rectangle		rect;
	t_line			line;
	t_rays_2d		rays_2d;
	t_mouse			mouse;
	t_draw_weapon	draw_weapon;
	t_draw_aim		draw_aim;
	t_draw_bit		draw_bit;
}					t_main;

/*
! ***********************************************************************
? =========                   read map function
! ***********************************************************************
*/
void				read_map(t_main *main);
void				check_file_name(t_main *main);
void				check_file_empty(t_main *main);
int					skip_space(char *str, int i);

/*
! ***********************************************************************
? =========                   exit and print function
! ***********************************************************************
*/
void				exit_and_print(char *str, t_main *main, int status);
void				print_map_for_error(t_main *main, int i, int j,
						char *string);

/*
! ***********************************************************************
? =========                   free game function
! ***********************************************************************
*/
void				free_and_nullify(void **ptr);
void				free_struct_game(t_main *main);
void				free_all(t_main *main);
void				free_struct_file(t_main *main);
void				free_struct_raycasting(t_main *main);
void				free_struct_splitter(t_main *main);
void				free_struct_helper(t_main *main);
void				free_main(t_main *main);

/*
! ***********************************************************************
? =========                   get values function
! ***********************************************************************
*/
void				get_textures(t_main *main, char **lines, int *i);
void				get_colors(t_main *main, char **lines, int *i);
void				get_values(t_main *main);
// * 1) get value colors
void				split_and_check(t_main *main);
void				check_max_min(t_main *main);
// * 2) utils
void				ft_split_file(t_main *main);
void				loop_and_substr(t_main *main);

/*
! ***********************************************************************
? =========                   valid map function
! ***********************************************************************
*/
void				check_map_content(t_main *main);
void				check_map(t_main *main);
void				check_player(t_main *main);
void				flood_fill_map(t_main *main, int i, int j);
void				fix_map(t_main *main);
void				check_player_surrounded_by_walls(t_main *main);

/*
! ***********************************************************************
? =========                  game function
! ***********************************************************************
*/
void				init_game(t_main *main);
// * 1) 2d game
void				draw_2d_view(t_main *main);
void				draw_map(t_main *main);
void				draw_rays_2d(t_main *main);
void				mlx_draw_line_thick(mlx_image_t *img, t_line line);
void				mlx_draw_rectangle(mlx_image_t *image, t_rectangle *rect);
int					calculate_mapx_mapy(t_main *main, int *x, int y);
void				color_door(t_main *main);
int					onther_draw_map(t_main *main, int *x, int y);
int					give_color(t_main *main, int *x, int y);
void				draw_thik(t_main *main);
void				draw_line_and_rectangle(t_main *main, int x, int y);
void				draw_horizontal_line(t_main *main, int x, int y,
						t_line *line);
void				draw_vertical_line(t_main *main, int x, int y,
						t_line *line);
void				draw_player_rectangle(t_main *main);
void				calculate_camx(t_main *main, int x);
void				cauculate_step_and_side_dist(t_main *main);
void				calculate_hit(t_main *main);
void				calculate_rayendx_rayendy(t_main *main);
void				side(t_main *main);
// * 2) handle color
uint32_t			rgb_32bit(int red, int green, int blue, t_main *main);
void				transformation_32bit(t_main *main);
// * 3) handle player
void				init_player(t_main *main);
// * 4) display bit
void				draw_walls(t_main *main);
// * 5) handle hook & mouse
void				handle_keys(void *param);
void				rotate_player(t_player *player, double angle);
void				move_player(t_main *main, double move_x, double move_y);
void				handle_mouse_rotation(t_main *main);
void				play_sound(t_main *main);
void				is_player_near_door(t_main *main);
void				draw_weapon(t_main *main);
void				draw_aim(t_main *main);
void				display_fps(t_main *main);
void				calculate_time(t_time *time, int number_array);
void				key_move(t_main *main);
void				key_time(t_main *main);

// * 6) rays
void				cast_rays(t_main *main);
void				calulate_delta_dist_and_side_tow(t_main *main);
void				dda_algorithm_tow(t_main *main, int x, int *i, int *found);
// * 7) init texture
void				init_texture(t_main *main);
void				init_door(t_main *main);
void				init_door(t_main *main);
void				init_weapon(t_main *main);

/*
! ***********************************************************************
? =========                  math function
! ***********************************************************************
*/
void				calculate_camx_rays(t_main *main, int x);
void				calulate_delta_dist_and_side(t_main *main);
void				dda_algorithm(t_main *main, int x);
void				calculate_wall(t_main *main);
void				calculate_height_and_down_for_wall(t_main *main, int x);

#endif