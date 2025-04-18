/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:35:38 by oissa             #+#    #+#             */
/*   Updated: 2025/04/15 19:13:16 by oissa            ###   ########.fr       */
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

// # define SCREEN_WIDTH 1920
#define SCREEN_WIDTH 2560
# define SCREEN_HEIGHT 1080
# define DEGUGGING 0
// #define TILE_SIZE 45
# define TILE_SIZE 25

# define MOV_SPEED 1.0
# define ROT_SPEED 1.0

# include "MLX42/MLX42.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>

typedef char		*string;

typedef struct s_mlx_draw
{
    mlx_image_t     *image;
    int             x;
    int             y;
    int             width;
    int             heigth;
    uint32_t        color;
    int             x0;
    int             y0;
    int             y1;
    int             x1;
    int             thickness;
}                   t_mlx_draw;


typedef struct s_player
{
	float			x;
	float			y;
	float			dir_x;
	float			dir_y;
	float			plane_x;
	float			plane_y;
}					t_player;

typedef struct s_raycasting
{
	int				*lineHeight;
	int				drawStart[SCREEN_WIDTH];
	int				drawEnd[SCREEN_WIDTH];
	int				side[SCREEN_WIDTH];
	float			wall_x[SCREEN_WIDTH];
	float			ray_dir_x[SCREEN_WIDTH];
	float			ray_dir_y[SCREEN_WIDTH];
}					t_raycasting;

typedef struct s_helper
{
	int				index;
	string			line_color_floor;
	string			line_color_ceiling;
	char			**color_floor;
	char			**color_ceiling;
	string			trim;
	string			trimmed_result;
	int				j;
	int				count_values_ceiling;
	int				count_values_floor;
	int				count_values_north;
	int				count_values_south;
	int				count_values_west;
	int				count_values_east;
	int				skip_space;
}					t_helper;

typedef struct s_game
{
	int				player_x;
	int				player_y;
	int				height_map;
	int				width_map;
	char			player_direction;
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_texture_t	*texture_north;
	mlx_texture_t	*texture_south;
	mlx_texture_t	*texture_west;
	mlx_texture_t	*texture_east;
	uint32_t		color_ceiling;
	uint32_t		color_floor;
}					t_game;

typedef struct s_file
{
	string			north_texture;
	string			south_texture;
	string			west_texture;
	string			east_texture;
	int				floor_color[3];
	int				ceiling_color[3];
	char			**map;
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

typedef struct s_main
{
	int				fd;
	string			file_name;
	string			result;
	t_file			file;
	t_splitter		split;
	t_game			game;
	t_helper		helper;
	t_player		player;
	t_raycasting	raycasting;
    t_mlx_draw      mlx_draw;
}					t_main;

/*
! ***********************************************************************
? =========                   read map function               
! ***********************************************************************
*/
void				read_map(t_main *main);
void				check_file_name(t_main *main);
void				check_file_empty(t_main *main);
int					skip_space(string str, int i);

/*
! ***********************************************************************
? =========                   exit and print function               
! ***********************************************************************
*/
void				exit_and_print(string str, t_main *main, int status);
void				print_map_for_error(t_main *main, int i, int j,
						char *string);

/*
! ***********************************************************************
? =========                   free game function               
! ***********************************************************************
*/
void				free_game(t_main *main);
void				free_all(t_main *main);

/*
! ***********************************************************************
? =========                   get values function               
! ***********************************************************************
*/
void				get_textures(t_main *main, char **lines, int *i);
void				get_colors(t_main *main, char **lines, int *i);
void				get_values(t_main *main);
// * 1) get value textures
void				function_north(t_main *main, char **lines, int *i);
void				function_south(t_main *main, char **lines, int *i);
void				function_west(t_main *main, char **lines, int *i);
void				function_east(t_main *main, char **lines, int *i);
// * 2) get value colors
void				function_floor(t_main *main, char **lines, int *i);
void				function_ceiling(t_main *main, char **lines, int *i);
void				split_and_check(t_main *main);
void				check_floor_is_valid(t_main *main);
void				check_ceiling_is_valid(t_main *main);
void				check_max_min(t_main *main);
// * 3) utils
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

/*
! ***********************************************************************
? =========                  game function               
! ***********************************************************************
*/
void				init_game(t_main *main);
// * 1) 2d game
void				draw_2D_view(t_main *main);
void				draw_map(t_main *main);
void				draw_rays_2D(t_main *main);
void				mlx_draw_line_thick(mlx_image_t *img, int x0, int y0,
						int x1, int y1, uint32_t color, int thickness);
void				mlx_draw_rectangle(mlx_image_t *image, int x, int y,
						int width, int height, uint32_t color);
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
// * 6) rays
void				cast_rays(t_main *main);

#endif