/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:47:11 by oissa             #+#    #+#             */
/*   Updated: 2025/03/22 22:39:03 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void get_textures(t_main *main, char **lines, int *i)
{
    while (lines[*i] && (main->file.north_texture == NULL || main->file.south_texture == NULL || main->file.west_texture == NULL || main->file.east_texture == NULL))
    {
        if (ft_strncmp(lines[*i], "NO ", 3) == 0)
        {
            if (ft_strlen(&lines[*i][3]) == 0)
                exit_and_print("North texture is empty", main, 0);
            main->file.north_texture = ft_strtrim(&lines[*i][3], " \t\n");
            if (main->file.north_texture == NULL)
                exit_and_print("Malloc failed", main, 0);
        }
        else if (ft_strncmp(lines[*i], "SO ", 3) == 0)
        {
            if (ft_strlen(&lines[*i][3]) == 0)
                exit_and_print("South texture is empty", main, 0);
            main->file.south_texture = ft_strtrim(&lines[*i][3], " \t\n");
            if (main->file.south_texture == NULL)
                exit_and_print("Malloc failed", main, 0);
        }
        else if (ft_strncmp(lines[*i], "WE ", 3) == 0)
        {
            if (ft_strlen(&lines[*i][3]) == 0)
                exit_and_print("West texture is empty", main, 0);
            main->file.west_texture = ft_strtrim(&lines[*i][3], " \t\n");
            if (main->file.west_texture == NULL)
                exit_and_print("Malloc failed", main, 0);
        }
        else if (ft_strncmp(lines[*i], "EA ", 3) == 0)
        {
            if (ft_strlen(&lines[*i][3]) == 0)
                exit_and_print("East texture is empty", main, 0);
            main->file.east_texture = ft_strtrim(&lines[*i][3], " \t\n");
            if (main->file.east_texture == NULL)
                exit_and_print("Malloc failed", main, 0);
        }
        (*i)++;
    }
    if (main->file.north_texture == NULL || main->file.south_texture == NULL || main->file.west_texture == NULL || main->file.east_texture == NULL)
        exit_and_print("Texture is missing", main, 0);
}

void get_colors(t_main *main, char **lines, int *i)
{
    int index;
    char *line_color_floor = NULL;
    char *line_color_ceiling = NULL;

    index = 0;
    while (lines[*i] && (line_color_floor == NULL || line_color_ceiling == NULL))
    {
        if (ft_strncmp(lines[*i], "F ", 2) == 0)
            line_color_floor = lines[*i];
        else if (ft_strncmp(lines[*i], "C ", 2) == 0)
            line_color_ceiling = lines[*i];
        (*i)++;
    }
    if (line_color_floor == NULL || line_color_ceiling == NULL)
        exit_and_print("Color is missing", main, 0);
    char **color_floor = ft_split(&line_color_floor[2], ',');
    char **color_ceiling = ft_split(&line_color_ceiling[2], ',');
    if (color_floor == NULL || color_ceiling == NULL)
        exit_and_print("Malloc failed", main, 0);
    index = -1;
    while (color_floor[++index])
        main->file.floor_color[index] = ft_atoi(color_floor[index]);
    index = -1;
    while (color_ceiling[++index])
        main->file.ceiling_color[index] = ft_atoi(color_ceiling[index]);
    index = -1;
    while (++index < 3)
    {
        if (main->file.floor_color[index] < 0 || main->file.floor_color[index] > 255)
            exit_and_print("Color is not valid", main, 0);
        if (main->file.ceiling_color[index] < 0 || main->file.ceiling_color[index] > 255)
            exit_and_print("Color is not valid", main, 0);
    }
    color_floor = ft_free_split(color_floor);
    color_ceiling = ft_free_split(color_ceiling);
}

void get_map(t_main *main, char **lines, int *i)
{
    (void)main;
    while (lines[*i])
    {
        if (lines[*i][0] != '\n')
            break;
        (*i)++;
    }
    main->file.map = lines + *i;
}

void ft_split_file(t_main *main)
{
    main->split.len = ft_strlen(main->result);
    main->split.lines = ft_calloc(main->split.len, sizeof(char *));
    if (main->split.lines == NULL)
        exit_and_print("Malloc failed", main, 0);
    while (main->result[main->split.j])
    {
        if (main->result[main->split.j] == '\n')
        {
            main->split.lines[main->split.i] = ft_substr(main->result, main->split.k, main->split.j - main->split.k + 1);
            if (main->split.lines[main->split.i] == NULL)
                exit_and_print("Malloc failed", main, 0);
            main->split.i++;
            main->split.k = main->split.j + 1;
        }
        main->split.j++;
    }
    if (main->split.k < main->split.j)
    {
        main->split.lines[main->split.i] = ft_substr(main->result, main->split.k, main->split.j - main->split.k);
        if (main->split.lines[main->split.i] == NULL)
            exit_and_print("Malloc failed", main, 0);
        main->split.i++;
    }
    main->split.lines[main->split.i] = NULL;
    if (main->split.lines == NULL)
        exit_and_print("Malloc failed", main, 0);
    main->split.i = 0;
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
    // ? print the values
    // ! print_result(main);
}
