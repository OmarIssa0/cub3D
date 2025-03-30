/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:47:11 by oissa             #+#    #+#             */
/*   Updated: 2025/03/30 15:53:23 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void get_textures(t_main *main, char **lines, int *i)
{
    while (lines[*i] /*&& (main->file.north_texture == NULL || main->file.south_texture == NULL || main->file.west_texture == NULL || main->file.east_texture == NULL)*/)
    {
        if (ft_strncmp(lines[*i], "NO ", 3) == 0)
        {
            main->helper.count_values_north++;
            if (ft_strlen(&lines[*i][3]) == 0)
                exit_and_print("North texture is empty \"North\"", main, 0);
            if (main->helper.count_values_north > 1)
                exit_and_print("Texture is duplicated \"North\"", main, 0);
            main->file.north_texture = ft_strtrim(&lines[*i][3], " \t\n");
            if (main->file.north_texture == NULL)
                exit_and_print("Malloc failed", main, 0);
            int skip = skip_space(main->file.north_texture, 0);
            if (main->file.north_texture[skip] == '\0')
                exit_and_print("Texture is not valid \"North\"", main, 0);
        }
        else if (ft_strncmp(lines[*i], "SO ", 3) == 0)
        {
            main->helper.count_values_south++;
            if (ft_strlen(&lines[*i][3]) == 0)
                exit_and_print("South texture is empty \"South\"", main, 0);
            if (main->helper.count_values_south > 1)
                exit_and_print("Texture is duplicated \"South\"", main, 0);
            main->file.south_texture = ft_strtrim(&lines[*i][3], " \t\n");
            if (main->file.south_texture == NULL)
                exit_and_print("Malloc failed", main, 0);
            int skip = skip_space(main->file.south_texture, 0);
            if (main->file.south_texture[skip] == '\0')
                exit_and_print("Texture is not valid \"South\"", main, 0);
        }
        else if (ft_strncmp(lines[*i], "WE ", 3) == 0)
        {
            main->helper.count_values_west++;
            if (ft_strlen(&lines[*i][3]) == 0)
                exit_and_print("West texture is empty \"West\"", main, 0);
            if (main->helper.count_values_west > 1)
                exit_and_print("Texture is duplicated \"West\"", main, 0);
            main->file.west_texture = ft_strtrim(&lines[*i][3], " \t\n");
            if (main->file.west_texture == NULL)
                exit_and_print("Malloc failed", main, 0);
            int skip = skip_space(main->file.west_texture, 0);
            if (main->file.west_texture[skip] == '\0')
                exit_and_print("Texture is not valid \"West\"", main, 0);
        }
        else if (ft_strncmp(lines[*i], "EA ", 3) == 0)
        {
            main->helper.count_values_east++;
            if (ft_strlen(&lines[*i][3]) == 0)
                exit_and_print("East texture is empty \"East\"", main, 0);
            if (main->helper.count_values_east > 1)
                exit_and_print("Texture is duplicated \"East\"", main, 0);
            main->file.east_texture = ft_strtrim(&lines[*i][3], " \t\n");
            if (main->file.east_texture == NULL)
                exit_and_print("Malloc failed", main, 0);
            int skip = skip_space(main->file.east_texture, 0);
            if (main->file.east_texture[skip] == '\0')
                exit_and_print("Texture is not valid \"East\"", main, 0);
        }
        (*i)++;
    }
    if (main->file.north_texture == NULL || main->file.south_texture == NULL || main->file.west_texture == NULL || main->file.east_texture == NULL)
        exit_and_print("Texture is missing", main, 0);
}

void get_colors(t_main *main, char **lines, int *i)
{
    *i = 0;
    while (lines[*i] /*&& (main->helper.line_color_floor == NULL || main->helper.line_color_ceiling == NULL)*/)
    {
        if (ft_strncmp(lines[*i], "F ", 2) == 0)
        {
            main->helper.count_values_floor++;
            main->helper.line_color_floor = lines[*i];
            int cunter = 0;
            int result = 0;
            while (lines[*i][cunter])
            {
                if (lines[*i][cunter] == ',')
                    result++;
                cunter++;
            }
            if (result != 2)
                exit_and_print("Color is not valid Floor", main, 0);
        }
        else if (ft_strncmp(lines[*i], "C ", 2) == 0)
        {
            main->helper.count_values_ceiling++;   
            main->helper.line_color_ceiling = lines[*i];
            int count = 0;
            int result = 0;
            while (lines[*i][count])
            {
                if (lines[*i][count] == ',')
                    result++;
                count++;
            }
            if (result != 2)
                exit_and_print("Color is not valid Ceiling", main, 0);
            count = 0;
            
        }
        (*i)++;
        if (main->helper.count_values_floor > 1 || main->helper.count_values_ceiling > 1)
            exit_and_print("Color is duplicated", main, 0);
    }
    
    if (main->helper.line_color_floor == NULL || main->helper.line_color_ceiling == NULL)
        exit_and_print("Color is missing", main, 0);
   
    main->helper.color_floor = ft_split(&main->helper.line_color_floor[2], ',');
    main->helper.color_ceiling = ft_split(&main->helper.line_color_ceiling[2], ',');
    
    if (main->helper.color_floor == NULL || main->helper.color_ceiling == NULL)
        exit_and_print("Malloc failed", main, 0);
    if (main->helper.color_floor[0] == NULL || main->helper.color_floor[1] == NULL || main->helper.color_floor[2] == NULL)
        exit_and_print("Color is missing", main, 0);
    if (main->helper.color_ceiling[0] == NULL || main->helper.color_ceiling[1] == NULL || main->helper.color_ceiling[2] == NULL)
        exit_and_print("Color is missing", main, 0);
  
    main->helper.index = -1;
    while (main->helper.color_floor[++main->helper.index])
    {
        main->helper.trim = ft_strtrim(main->helper.color_floor[main->helper.index], " \t\n");
        if (main->helper.trim == NULL)
            exit_and_print("Malloc failed", main, 0);
        int skip = skip_space(main->helper.trim, 0);
        if (main->helper.trim[skip] == '\0')
            exit_and_print("Color is not valid Floor", main, 0);
        main->helper.j = 0;
    
        while (main->helper.trim[main->helper.j])
        {
            if (main->helper.trim[0] == '\0' || ft_isdigit(main->helper.trim[main->helper.j]) == 0)
                exit_and_print("Color is not valid Floor", main, 0);
            main->helper.j++;
        }

        free(main->helper.trim);
        main->helper.trim = NULL;
       
        main->file.floor_color[main->helper.index] = ft_atoi(main->helper.color_floor[main->helper.index]);
    }
    if (main->helper.index != 3)
        exit_and_print("Color is not valid Floor", main, 0);
    main->helper.index = -1;
    while (main->helper.color_ceiling[++main->helper.index] != NULL)
    {
        main->helper.trim = ft_strtrim(main->helper.color_ceiling[main->helper.index], " \t\n");
        if (main->helper.trim == NULL)
            exit_and_print("Malloc failed", main, 0);
        int skip = skip_space(main->helper.trim, 0);
        if (main->helper.trim[skip] == '\0')
            exit_and_print("Color is not valid Ceiling", main, 0);
        main->helper.j = 0;
        while (main->helper.trim[main->helper.j])
        {
            if (main->helper.trim[0] == '\0'  || ft_isdigit(main->helper.trim[main->helper.j]) == 0)
                exit_and_print("Color is not valid Ceiling", main, 0);
            main->helper.j++;
        }
        free(main->helper.trim);
        main->helper.trim = NULL;
        main->helper.j++;
        main->file.ceiling_color[main->helper.index] = ft_atoi(main->helper.color_ceiling[main->helper.index]);
    }
    if (main->helper.index != 3)
        exit_and_print("Color is not valid Ceiling", main, 0);
    main->helper.index = -1;
    while (++main->helper.index < 3)
    {
        if (main->file.floor_color[main->helper.index] < 0 || main->file.floor_color[main->helper.index] > 255)
            exit_and_print("Color is not valid Floor", main, 0);
        if (main->file.ceiling_color[main->helper.index] < 0 || main->file.ceiling_color[main->helper.index] > 255)
            exit_and_print("Color is not valid Floor", main, 0);
    }
    main->helper.color_floor = ft_free_split(main->helper.color_floor);
    main->helper.color_ceiling = ft_free_split(main->helper.color_ceiling);
}

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
    // print_result(main);
}
