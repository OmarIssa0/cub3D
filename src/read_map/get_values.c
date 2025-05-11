/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:47:11 by oissa             #+#    #+#             */
/*   Updated: 2025/05/10 16:32:27 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void get_map(t_main *main, char **lines, int *i)
{
    *i = 0;
    int skip;

    while (lines[*i])
    {
        skip = skip_space(lines[*i], 0);
        if (lines[*i][0] != '\n' 
            && ft_strncmp(lines[*i] + skip, "NO ", 3) != 0
            && ft_strncmp(lines[*i] + skip, "SO ", 3) != 0
            && ft_strncmp(lines[*i] + skip, "WE ", 3) != 0
            && ft_strncmp(lines[*i] + skip, "EA ", 3) != 0
            && ft_strncmp(lines[*i] + skip, "F ", 2) != 0
            && ft_strncmp(lines[*i] + skip, "C ", 2) != 0
            && lines[*i][skip] != '\0')
            break ;
        (*i)++;
    }
    main->file.map = lines + *i;
}


void get_values(t_main *main)
{
    ft_split_file(main);
    get_textures(main, main->split.lines, &main->split.i);
    get_colors(main, main->split.lines, &main->split.i);
    get_map(main, main->split.lines, &main->split.i);
    transformation_32bit(main);
}
