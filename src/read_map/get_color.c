/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:03:16 by oissa             #+#    #+#             */
/*   Updated: 2025/03/30 16:19:31 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void function_floor(t_main *main, char **lines, int *i)
{
    int result;
    int counter;

    result = 0;
    counter = 0;
    main->helper.count_values_floor++;
    main->helper.line_color_floor = lines[*i];
    while (lines[*i][counter])
    {
        if (lines[*i][counter] == ',')
            result++;
        counter++;
    }
    if (result != 2)
        exit_and_print("Color is not valid Floor", main, 0);
}

void function_ceiling(t_main *main, char **lines, int *i)
{
    int result;
    int counter;

    result = 0;
    counter = 0;
    main->helper.count_values_ceiling++;
    main->helper.line_color_ceiling = lines[*i];
    while (lines[*i][counter])
    {
        if (lines[*i][counter] == ',')
            result++;
        counter++;
    }
    if (result != 2)
        exit_and_print("Color is not valid Ceiling", main, 0);
}


void check_floor_is_valid(t_main *main)
{
    while (main->helper.color_floor[++main->helper.index])
    {
        main->helper.trim = 
            ft_strtrim(main->helper.color_floor[main->helper.index], " \t\n");
        if (main->helper.trim == NULL)
            exit_and_print("Malloc failed", main, 0);
        main->helper.skip_space = skip_space(main->helper.trim, 0);
        if (main->helper.trim[main->helper.skip_space] == '\0')
            exit_and_print("Color is not valid Floor", main, 0);
        main->helper.j = 0;
        while (main->helper.trim[main->helper.j])
        {
            if (main->helper.trim[0] == '\0'
                || ft_isdigit(main->helper.trim[main->helper.j]) == 0)
                exit_and_print("Color is not valid Floor", main, 0);
            main->helper.j++;
        }
        free(main->helper.trim);
        main->helper.trim = NULL;
        main->file.floor_color[main->helper.index]
            = ft_atoi(main->helper.color_floor[main->helper.index]);
    }
    if (main->helper.index != 3)
        exit_and_print("Color is not valid Floor", main, 0);
}
void check_ceiling_is_valid(t_main *main)
{
    while (main->helper.color_ceiling[++main->helper.index] != NULL)
    {
        main->helper.trim 
            = ft_strtrim(main->helper.color_ceiling[main->helper.index], " \t\n");
        if (main->helper.trim == NULL)
            exit_and_print("Malloc failed", main, 0);
        main->helper.skip_space = skip_space(main->helper.trim, 0);
        if (main->helper.trim[main->helper.skip_space] == '\0')
            exit_and_print("Color is not valid Ceiling", main, 0);
        main->helper.j = 0;
        while (main->helper.trim[main->helper.j])
        {
            if (main->helper.trim[0] == '\0'
                || ft_isdigit(main->helper.trim[main->helper.j]) == 0)
                exit_and_print("Color is not valid Ceiling", main, 0);
            main->helper.j++;
        }
        free(main->helper.trim);
        main->helper.trim = NULL;
        main->file.ceiling_color[main->helper.index]
            = ft_atoi(main->helper.color_ceiling[main->helper.index]);
    }
    if (main->helper.index != 3)
        exit_and_print("Color is not valid Ceiling", main, 0);
}


void get_colors(t_main *main, char **lines, int *i)
{
    *i = 0;
    while (lines[*i])
    {
        if (ft_strncmp(lines[*i], "F ", 2) == 0)
            function_floor(main, lines, i);
        else if (ft_strncmp(lines[*i], "C ", 2) == 0)
            function_ceiling(main, lines, i);
        (*i)++;
        if (main->helper.count_values_floor > 1
            || main->helper.count_values_ceiling > 1)
            exit_and_print("Color is duplicated", main, 0);
    }
    split_and_check(main);
    main->helper.index = -1;
    check_floor_is_valid(main);
    main->helper.index = -1;
    check_ceiling_is_valid(main);
    check_max_min(main);
    main->helper.color_floor
        = ft_free_split(main->helper.color_floor);
    main->helper.color_ceiling
        = ft_free_split(main->helper.color_ceiling);
}
