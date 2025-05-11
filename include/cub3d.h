/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/03/20 23:35:38 by oissa             #+#    #+#             */
/*   Updated: 2025/05/07 19:13:26 by oissa            ###   ########.fr       */
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

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
// #define SCREEN_WIDTH 2560
// #define SCREEN_HEIGHT 1080
// #define SCREEN_WIDTH 1000
// #define TILE_SIZE 45
# define TILE_SIZE 10
# define PUT_FLOOR true
# define PUT_CEILING true

# define MOV_SPEED 1.0
# define ROT_SPEED 1.0

# define MAX_FLOAT 3.402823466e+38F

# include "MLX42/MLX42.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
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
} t_num;

typedef char *string;

typedef struct s_time
{
	struct timespec current_time[3];
	double now[3];
	double last_time[3];
} t_time;

typedef struct s_math
{
	float camera_x;
	float ray_dir_x;
	float ray_dir_y;
	int map_x;
	int map_y;
	float delta_dist_x;
	float delta_dist_y;
	float side_dist_x;
	float side_dist_y;
	int step_x;
	int step_y;
	int hit;
	int side;
	float perp_wall_dist;
	int lineHeight;
	int drawStart;
	int drawEnd;
	float wall_x;
} t_math;

typedef struct s_player
{
	float x;
	float y;
	float dir_x;
	float dir_y;
	float plane_x;
	float plane_y;
	float z;
	bool holding;
} t_player;

typedef struct s_raycasting
{
	int *lineHeight;
	int drawStart[SCREEN_WIDTH];
	int drawEnd[SCREEN_WIDTH];
	int side[SCREEN_WIDTH];
	float wall_x[SCREEN_WIDTH];
	float ray_dir_x[SCREEN_WIDTH];
	float ray_dir_y[SCREEN_WIDTH];
	int is_door[SCREEN_WIDTH];
} t_raycasting;

typedef struct s_helper
{
	int index;
	string line_color_floor;
	string line_color_ceiling;
	char **color_floor;
	char **color_ceiling;
	string trim;
	string trimmed_result;
	int j;
	int count_values_ceiling;
	int count_values_floor;
	int count_values_north;
	int count_values_south;
	int count_values_west;
	int count_values_east;
	int skip_space;
	int	surface[2];
	int x;
	int y;
	int player;
} t_helper;

typedef struct s_game
{
	int player_x;
	int player_y;
	int height_map;
	int width_map;
	char player_direction;
	double time;
	mlx_t *mlx;
	mlx_image_t *image;
	mlx_texture_t *texture_north;
	mlx_texture_t *texture_south;
	mlx_texture_t *texture_west;
	mlx_texture_t *texture_east;
	mlx_texture_t *texture_light_wall;
	mlx_texture_t *texture_mid_wall;
	mlx_texture_t *texture_floor;
	mlx_texture_t *texture_door_open;
	mlx_texture_t *texture_door_close;
	// mlx_texture_t	*texture_weapon[13];
	mlx_texture_t *texture_weapon[28];
	int weapon_animation;
	uint32_t night_and_day[25];
	uint32_t color_ceiling;
	uint32_t color_floor;
} t_game;

typedef struct s_point
{
	int x;
	int y;
	bool is_open;
} t_point;

typedef struct s_file
{
	string north_texture;
	string south_texture;
	string west_texture;
	string east_texture;
	int floor_color[3];
	int ceiling_color[3];
	char **map;
	int nb_door;
	t_point *pos_doors;
} t_file;

typedef struct s_splitter
{
	char **lines;
	int i;
	int j;
	int k;
	int len;
	int remander_index;
} t_splitter;

typedef struct s_main
{
	int fd;
	string file_name;
	string result;
	t_file file;
	t_splitter split;
	t_game game;
	t_helper helper;
	t_player player;
	t_raycasting raycasting;
	t_math math;
	t_time time;
} t_main;

/*
! ***********************************************************************
? =========                   read map function
! ***********************************************************************
*/
void	read_map(t_main *main);
void	check_file_name(t_main *main);
void	check_file_empty(t_main *main);
int	skip_space(string str, int i);

/*
! ***********************************************************************
? =========                   exit and print function
! ***********************************************************************
*/
void	exit_and_print(string str, t_main *main, int status);
void	print_map_for_error(t_main *main, int i, int j, char *string);

/*
! ***********************************************************************
? =========                   free game function
! ***********************************************************************
*/
void	free_and_nullify(void **ptr);
void	free_struct_game(t_main *main);
void	free_all(t_main *main);
void	free_struct_file(t_main *main);
void	free_struct_raycasting(t_main *main);
void	free_struct_splitter(t_main *main);
void	free_struct_helper(t_main *main);
void	free_main(t_main *main);

/*
! ***********************************************************************
? =========                   get values function
! ***********************************************************************
*/
void	get_textures(t_main *main, char **lines, int *i);
void	get_colors(t_main *main, char **lines, int *i);
void	get_values(t_main *main);
// * 1) get value colors
void	function_floor(t_main *main, char **lines, int *i);
void	function_ceiling(t_main *main, char **lines, int *i);
void	split_and_check(t_main *main);
void	check_floor_is_valid(t_main *main);
void	check_ceiling_is_valid(t_main *main);
void	check_max_min(t_main *main);
// * 2) utils
void	ft_split_file(t_main *main);
void	loop_and_substr(t_main *main);

/*
! ***********************************************************************
? =========                   valid map function
! ***********************************************************************
*/
void	check_map_content(t_main *main);
void	check_map(t_main *main);
void	check_player(t_main *main);

/*
! ***********************************************************************
? =========                  game function
! ***********************************************************************
*/
void	init_game(t_main *main);
// * 1) 2d game
void	draw_2D_view(t_main *main);
void	draw_map(t_main *main);
void	draw_rays_2D(t_main *main);
void	mlx_draw_line_thick(mlx_image_t *img, int x0, int y0, int x1, int y1,
		uint32_t color, int thickness);
void	mlx_draw_rectangle(mlx_image_t *image, int x, int y, int width,
		int height, uint32_t color);
// * 2) handle color
uint32_t	rgb_32bit(int red, int green, int blue, t_main *main);
void	transformation_32bit(t_main *main);
// * 3) handle player
void	init_player(t_main *main);
// * 4) display bit
void	draw_walls(t_main *main);
// * 5) handle hook & mouse
void	handle_keys(void *param);
void	rotate_player(t_player *player, double angle);
void	move_player(t_main *main, double move_x, double move_y);
void	handle_mouse_rotation(t_main *main);
// * 6) rays
void	cast_rays(t_main *main);

/*
! ***********************************************************************
? =========                  math function
! ***********************************************************************
*/
void	calculate_camx_rays(t_main *main, int x);
void	calulate_delta_dist_and_side(t_main *main);
void	DDA_algorithm(t_main *main, int x);
void	calculate_wall(t_main *main);
void	calculate_height_and_down_for_wall(t_main *main, int x);

#endif