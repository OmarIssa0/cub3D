/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:35:38 by oissa             #+#    #+#             */
/*   Updated: 2025/03/21 23:50:55 by oissa            ###   ########.fr       */
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

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <MLX42/MLX42.h>
# include <time.h>
# include "libft.h"

typedef struct s_file
{
    char *north_texture;
    char *south_texture;
    char *west_texture;
    char *east_texture;
    int  floor_color[3];
    int  ceiling_color[3];
    char **map;
}         t_file;


typedef struct s_main
{
    int fd;
    char *file_name;
    char *result;
    t_file file;
}            t_main;


/*
    ! read map function
*/
void   read_map(t_main *main);
void check_map(t_main *main);
void check_map_empty(t_main *main);
int skip_space(char *str, int i);

/*
    ! exit and print function
*/
void    exit_and_print(char *str, t_main *main, int status);


/*
    ! free game function
*/
void free_game(t_main *main);
void free_all(t_main *main);

/*
    ! get values function
*/
void get_textures(t_main *main, char **lines);
void get_colors(t_main *main, char **lines);
void get_values(t_main *main);

#endif