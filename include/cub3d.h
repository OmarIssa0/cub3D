/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:35:38 by oissa             #+#    #+#             */
/*   Updated: 2025/03/27 22:51:16 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"
#define PURPLE "\033[0;35m"
#define WHITE "\033[0;37m"
#define BLUE "\033[0;34m"
#define YELLOW "\033[0;33m"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <MLX42/MLX42.h>
#include <time.h>
#include "libft.h"
#include <stdbool.h>

typedef struct s_helper
{
    int index;
    char *line_color_floor;
    char *line_color_ceiling;
    char **color_floor;
    char **color_ceiling;
    char *trim;
    int j;
    int count_values_ceiling;
    int count_values_floor;
    int count_values_north;
    int count_values_south;
    int count_values_west;
    int count_values_east;
}   t_helper;

typedef struct s_game
{
    int player_x;
    int player_y;
    int height_map;
    int width_map;
    char player_direction;
    mlx_t *mlx;
} t_game;

typedef struct s_file
{
    char *north_texture;
    char *south_texture;
    char *west_texture;
    char *east_texture;
    int floor_color[3];
    int ceiling_color[3];
    char **map;
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
    char *file_name;
    char *result;
    t_file file;
    t_splitter split;
    t_game game;
    t_helper helper;
} t_main;

/*
    ! read map function
*/
void read_map(t_main *main);
void check_file_name(t_main *main);
void check_file_empty(t_main *main);
int skip_space(char *str, int i);

/*
    ! exit and print function
*/
void exit_and_print(char *str, t_main *main, int status);
void print_map_for_error(t_main *main, int i, int j, char *string);

/*
    ! free game function
*/
void free_game(t_main *main);
void free_all(t_main *main);

/*
    ! get values function
*/
void get_textures(t_main *main, char **lines, int *i);
void get_colors(t_main *main, char **lines, int *i);
void get_values(t_main *main);

/*
    ! valid map function
*/
void check_map_content(t_main *main);
void check_map(t_main *main);
void check_player(t_main *main);

/* 
    ! game function
*/
void init_game(t_main *main);


#endif