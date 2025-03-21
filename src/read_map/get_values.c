/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:47:11 by oissa             #+#    #+#             */
/*   Updated: 2025/03/21 23:50:41 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void get_textures(t_main *main, char **lines)
{
    int i;
    
    i = 0;
    while (lines[i])
    {
        if (ft_strncmp (lines[i], "NO ", 3) == 0)
        {
            if (ft_strlen(&lines[i][3]) == 0)
                exit_and_print("North texture is empty", main, 0);
            main->file.north_texture = ft_strtrim(&lines[i][3], " \t\n");
            if (main->file.north_texture == NULL)
                exit_and_print("Malloc failed", main, 0);
        }
        else if (ft_strncmp (lines[i], "SO ", 3) == 0)
        {
            if (ft_strlen(&lines[i][3]) == 0)
                exit_and_print("South texture is empty", main, 0);
            main->file.south_texture = ft_strtrim(&lines[i][3], " \t\n");
            if (main->file.south_texture == NULL)
                exit_and_print("Malloc failed", main, 0);
        }
        else if (ft_strncmp (lines[i], "WE ", 3) == 0)
        {
            if (ft_strlen(&lines[i][3]) == 0)
                exit_and_print("West texture is empty", main, 0);
            main->file.west_texture = ft_strtrim(&lines[i][3], " \t\n");
            if (main->file.west_texture == NULL)
                exit_and_print("Malloc failed", main, 0);
        }
        else if (ft_strncmp (lines[i], "EA ", 3) == 0)
        {
            if (ft_strlen(&lines[i][3]) == 0)
                exit_and_print("East texture is empty", main, 0);
            main->file.east_texture = ft_strtrim(&lines[i][3], " \t\n");
            if (main->file.east_texture == NULL)
                exit_and_print("Malloc failed", main, 0);
        }
        i++;
    }
    if (main->file.north_texture == NULL || main->file.south_texture == NULL || main->file.west_texture == NULL || main->file.east_texture == NULL)
        exit_and_print("Texture is missing", main, 0);
}

void get_colors(t_main *main, char **lines)
{
    int i;
    char *line_color_floor;
    char *line_color_ceiling;

    i = 0;
    while (lines[i])
    {
        if (ft_strncmp(lines[i], "F ", 2) == 0)
            line_color_floor = lines[i];
        else if (ft_strncmp(lines[i], "C ", 2) == 0)
            line_color_ceiling = lines[i];
        i++;
    }
    if (line_color_floor == NULL || line_color_ceiling == NULL)
        exit_and_print("Color is missing", main, 0);
    char **color_floor = ft_split(&line_color_floor[2], ',');
    char **color_ceiling = ft_split(&line_color_ceiling[2], ',');
    if (color_floor == NULL || color_ceiling == NULL)
        exit_and_print("Malloc failed", main, 0);
    i = -1;
    while (color_floor[++i])
        main->file.floor_color[i] = ft_atoi(color_floor[i]);
    i = -1;
    while (color_ceiling[++i])
        main->file.ceiling_color[i] = ft_atoi(color_ceiling[i]);
    i = -1;
    while (++i < 3)
    {
        if (main->file.floor_color[i] < 0 || main->file.floor_color[i] > 255)
            exit_and_print("Color is not valid", main, 0);
        if (main->file.ceiling_color[i] < 0 || main->file.ceiling_color[i] > 255)
            exit_and_print("Color is not valid", main, 0);
    }
    color_floor = ft_free_split(color_floor);
    color_ceiling = ft_free_split(color_ceiling);
}

void    get_values(t_main *main)
{
    char **lines;

    lines = ft_split(main->result, '\n');
    if (lines == NULL)
        exit_and_print("Malloc failed", main, 0);
    // ? get the values of the textures
    get_textures(main, lines);
    // ? get the values of the colors
    get_colors(main, lines);
    // ? get the values of the map
    // get_map(main);
    // ? print the values
    ft_printf("north_texture: %s\n", main->file.north_texture);
    ft_printf("south_texture: %s\n", main->file.south_texture);
    ft_printf("west_texture: %s\n", main->file.west_texture);
    ft_printf("east_texture: %s\n", main->file.east_texture);
    ft_printf("floor_color: %d, %d, %d\n", main->file.floor_color[0], main->file.floor_color[1], main->file.floor_color[2]);
    ft_printf("ceiling_color: %d, %d, %d\n", main->file.ceiling_color[0], main->file.ceiling_color[1], main->file.ceiling_color[2]);
    lines = ft_free_split(lines);
}
