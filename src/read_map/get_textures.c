/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:55:38 by oissa             #+#    #+#             */
/*   Updated: 2025/04/17 12:43:00 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void function_north(t_main *main, char **lines, int *i)
{
    int skip;
    
    main->helper.count_values_north++;
    if (ft_strlen(&lines[*i][3]) == 0)
        exit_and_print("North texture is empty \"North\"", main, 0);
    if (main->helper.count_values_north > 1)
        exit_and_print("Texture is duplicated \"North\"", main, 0);
    main->helper.skip_space = skip_space(lines[*i], 0);
    main->file.north_texture = ft_strtrim(&lines[*i][main->helper.skip_space + 3], " \t\n");
    if (main->file.north_texture == NULL)
        exit_and_print("Malloc failed", main, 0);
    skip = skip_space(main->file.north_texture, 0);
    if (main->file.north_texture[skip] == '\0')
        exit_and_print("Texture is not valid \"North\"", main, 0);
}

void function_south(t_main *main, char **lines, int *i)
{
    int skip;
    
    main->helper.count_values_south++;
    if (ft_strlen(&lines[*i][3]) == 0)
        exit_and_print("South texture is empty \"South\"", main, 0);
    if (main->helper.count_values_south > 1)
        exit_and_print("Texture is duplicated \"South\"", main, 0);
    main->helper.skip_space = skip_space(lines[*i], 0);
    main->file.south_texture = ft_strtrim(&lines[*i][main->helper.skip_space + 3], " \t\n");
    if (main->file.south_texture == NULL)
        exit_and_print("Malloc failed", main, 0);
    skip = skip_space(main->file.south_texture, 0);
    if (main->file.south_texture[skip] == '\0')
        exit_and_print("Texture is not valid \"South\"", main, 0);
}

void function_west(t_main *main, char **lines, int *i)
{
    int skip;
    
    main->helper.count_values_west++;
    if (ft_strlen(&lines[*i][3]) == 0)
        exit_and_print("West texture is empty \"West\"", main, 0);
    if (main->helper.count_values_west > 1)
        exit_and_print("Texture is duplicated \"West\"", main, 0);
    main->helper.skip_space = skip_space(lines[*i], 0);
    main->file.west_texture = ft_strtrim(&lines[*i][main->helper.skip_space + 3], " \t\n");
    if (main->file.west_texture == NULL)
        exit_and_print("Malloc failed", main, 0);
    skip = skip_space(main->file.west_texture, 0);
    if (main->file.west_texture[skip] == '\0')
        exit_and_print("Texture is not valid \"West\"", main, 0);
}

void function_east(t_main *main, char **lines, int *i)
{
    int skip;
    
    main->helper.count_values_east++;
    if (ft_strlen(&lines[*i][3]) == 0)
        exit_and_print("East texture is empty \"East\"", main, 0);
    if (main->helper.count_values_east > 1)
        exit_and_print("Texture is duplicated \"East\"", main, 0);
    main->helper.skip_space = skip_space(lines[*i], 0);
    main->file.east_texture = ft_strtrim(&lines[*i][main->helper.skip_space + 3], " \t\n");
    if (main->file.east_texture == NULL)
        exit_and_print("Malloc failed", main, 0);
    skip = skip_space(main->file.east_texture, 0);
    if (main->file.east_texture[skip] == '\0')
        exit_and_print("Texture is not valid \"East\"", main, 0);
}

void get_textures(t_main *main, char **lines, int *i)
{
    while (lines[*i])
    {
        main->helper.skip_space = skip_space(lines[*i], 0);
        if (ft_strncmp(lines[*i] + main->helper.skip_space, "NO ", 3) == 0)
            function_north(main, lines, i);
        else if (ft_strncmp(lines[*i] + main->helper.skip_space, "SO ", 3) == 0)
            function_south(main, lines, i);
        else if (ft_strncmp(lines[*i] + main->helper.skip_space, "WE ", 3) == 0)
            function_west(main, lines, i);
        else if (ft_strncmp(lines[*i] + main->helper.skip_space, "EA ", 3) == 0)
            function_east(main, lines, i);
        (*i)++;
    }
    if (main->file.north_texture == NULL
        || main->file.south_texture == NULL
        || main->file.west_texture == NULL
        || main->file.east_texture == NULL)
        exit_and_print("Texture is missing", main, 0);
}
