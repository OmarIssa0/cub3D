/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:55:38 by oissa             #+#    #+#             */
/*   Updated: 2025/05/12 20:20:44 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	exctract_path_direction(t_main *main, char **lines, int *i,
		char **direction)
{
	if (ft_strlen(&lines[*i][3]) == 0)
		exit_and_print(lines[main->helper.skip_space], main, DONT_CLOSE_FD);
	main->helper.skip_space = skip_space(lines[*i], 0);
	*direction = ft_strtrim(&lines[*i][main->helper.skip_space + 3], " \t\n");
	if (*direction == NULL)
		exit_and_print("Malloc failed", main, DONT_CLOSE_FD);
	main->helper.skip_space = skip_space(*direction, 0);
	if (*direction[main->helper.skip_space] == '\0')
		exit_and_print("Texture is not valid", main, DONT_CLOSE_FD);
}

void	get_textures(t_main *main, char **lines, int *i)
{
	int	directions[4];

	ft_bzero(directions, sizeof(directions));
	while (lines[*i])
	{
		main->helper.skip_space = skip_space(lines[*i], 0);
		if (ft_strncmp(lines[*i] + main->helper.skip_space, "NO ", 3) == 0
			&& ++directions[0])
			exctract_path_direction(main, lines, i, &main->file.north_texture);
		else if (ft_strncmp(lines[*i] + main->helper.skip_space, "SO ", 3) == 0
			&& ++directions[1])
			exctract_path_direction(main, lines, i, &main->file.south_texture);
		else if (ft_strncmp(lines[*i] + main->helper.skip_space, "WE ", 3) == 0
			&& ++directions[2])
			exctract_path_direction(main, lines, i, &main->file.west_texture);
		else if (ft_strncmp(lines[*i] + main->helper.skip_space, "EA ", 3) == 0
			&& ++directions[3])
			exctract_path_direction(main, lines, i, &main->file.east_texture);
		(*i)++;
	}
	if (directions[0] != 1 || directions[1] != 1 || directions[2] != 1
		|| directions[3] != 1 || main->file.north_texture == NULL
		|| main->file.south_texture == NULL || main->file.west_texture == NULL
		|| main->file.east_texture == NULL)
		exit_and_print("Texture is Invalid", main, DONT_CLOSE_FD);
}
