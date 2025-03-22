/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:41:14 by oissa             #+#    #+#             */
/*   Updated: 2025/03/22 22:38:33 by oissa            ###   ########.fr       */
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
    if (main->file.north_texture)
    {
        free(main->file.north_texture);
        main->file.north_texture = NULL;
    }
    if (main->file.south_texture)
    {
        free(main->file.south_texture);
        main->file.south_texture = NULL;
    }
    if (main->file.west_texture)
    {
        free(main->file.west_texture);
        main->file.west_texture = NULL;
    }
    if (main->file.east_texture)
    {
        free(main->file.east_texture);
        main->file.east_texture = NULL;
    }
    if (main->split.lines)
    {
        main->split.lines = ft_free_split(main->split.lines);
        main->split.lines = NULL;
    }
}
