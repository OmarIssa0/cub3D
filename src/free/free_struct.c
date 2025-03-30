/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:41:14 by oissa             #+#    #+#             */
/*   Updated: 2025/03/27 16:59:27 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_all(t_main *main)
{
    if (main->file_name)
    {
        free(main->file_name);
        main->file_name = NULL;
    }
    if (main->result)
    {
        free(main->result);
        main->result = NULL;
    }
    // ? free struct file
    if (main->file.north_texture != NULL)
    {
        free(main->file.north_texture);
        main->file.north_texture = NULL;
    }
    if (main->file.south_texture != NULL)
    {
        free(main->file.south_texture);
        main->file.south_texture = NULL;
    }
    if (main->file.west_texture != NULL)
    {
        free(main->file.west_texture);
        main->file.west_texture = NULL;
    }
    if (main->file.east_texture != NULL)
    {
        free(main->file.east_texture);
        main->file.east_texture = NULL;
    }
    // ? free struct helper
    // if (main->helper.line_color_floor != NULL)
    // {
    //     free(main->helper.line_color_floor);
    //     main->helper.line_color_floor = NULL;
    // }
    // if (main->helper.line_color_ceiling != NULL)
    // {
    //     free(main->helper.line_color_ceiling);
    //     main->helper.line_color_ceiling = NULL;
    // }
    if (main->helper.color_floor != NULL)
    {
        main->helper.color_floor = ft_free_split(main->helper.color_floor);
    }
    if (main->helper.color_ceiling != NULL)
    {
        main->helper.color_ceiling = ft_free_split(main->helper.color_ceiling);
    }
    if (main->helper.trim != NULL)
    {
        free(main->helper.trim);
        main->helper.trim = NULL;
    }
    // ? free struct splitter
    if (main->split.lines != NULL)
    {
        main->split.lines = ft_free_split(main->split.lines);
        main->split.lines = NULL;
    }
    // ? free struct game
    if (main->game.mlx != NULL)
    {
        mlx_terminate(main->game.mlx);
        main->game.mlx = NULL;
    }
}
