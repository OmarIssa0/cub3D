/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:47:11 by oissa             #+#    #+#             */
/*   Updated: 2025/04/15 17:04:42 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void get_map(t_main *main, char **lines, int *i)
{
    *i = 0;
    while (lines[*i])
    {
        int skip = skip_space(lines[*i], 0);
        if (lines[*i][0] != '\n' 
            && ft_strncmp(lines[*i] + skip, "NO ", 3) != 0
            && ft_strncmp(lines[*i] + skip, "SO ", 3) != 0
            && ft_strncmp(lines[*i] + skip, "WE ", 3) != 0
            && ft_strncmp(lines[*i] + skip, "EA ", 3) != 0
            && ft_strncmp(lines[*i] + skip, "F ", 2) != 0
            && ft_strncmp(lines[*i] + skip, "C ", 2) != 0)
            break ;
        (*i)++;
    }
    main->file.map = lines + *i;
}

void print_result(t_main *main)
{
    int i;

    i = 0;
    while (main->file.map[i])
    {
        ft_printf("%s", main->file.map[i]);
        i++;
    }
    ft_printf("\n");
    ft_printf("North texture: %s\n", main->file.north_texture);
    ft_printf("South texture: %s\n", main->file.south_texture);
    ft_printf("West texture: %s\n", main->file.west_texture);
    ft_printf("East texture: %s\n", main->file.east_texture);
    ft_printf("Floor color: %d %d %d\n", main->file.floor_color[0], main->file.floor_color[1], main->file.floor_color[2]);
    ft_printf("Ceiling color: %d %d %d\n", main->file.ceiling_color[0], main->file.ceiling_color[1], main->file.ceiling_color[2]);
}

void get_values(t_main *main)
{
    // ? split the file
    ft_split_file(main);
    // ? get the values of the textures
    get_textures(main, main->split.lines, &main->split.i);
    // ? get the values of the colors
    get_colors(main, main->split.lines, &main->split.i);
    // ? get the values of the map
    get_map(main, main->split.lines, &main->split.i);
    // ? save color int to uint32_t -> 32bit
    transformation_32bit(main);
    // ? print the values
    // print_result(main);
}
