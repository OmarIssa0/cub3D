/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:03:16 by oissa             #+#    #+#             */
/*   Updated: 2025/05/10 16:31:19 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_surface_is_valid(t_main *main, char **color, int (*helper)[3])
{
	main->helper.index = -1;
	while (color[++main->helper.index] != NULL)
	{
		main->helper.trim = ft_strtrim(color[main->helper.index], " \t\n");
		if (main->helper.trim == NULL)
			exit_and_print("Malloc failed", main, DONT_CLOSE_FD);
		main->helper.skip_space = skip_space(main->helper.trim, 0);
		if (main->helper.trim[main->helper.skip_space] == '\0')
			exit_and_print("Color is not valid", main, DONT_CLOSE_FD);
		main->helper.j = 0;
		while (main->helper.trim[main->helper.j])
		{
			if (main->helper.trim[0] == '\0'
				|| ft_isdigit(main->helper.trim[main->helper.j]) == 0)
				exit_and_print("Color is not valid", main, DONT_CLOSE_FD);
			main->helper.j++;
		}
		free(main->helper.trim);
		main->helper.trim = NULL;
		(*helper)[main->helper.index] = ft_atoi(color[main->helper.index]);
	}
	if (main->helper.index != 3)
		exit_and_print("Color is not valid", main, DONT_CLOSE_FD);
}

void	exctract_color_surface(t_main *main, char **lines, int *i, char **color)
{
	int	result;
	int	counter;

	result = 0;
	counter = 0;
	*color = lines[*i] + main->helper.skip_space;
	while (lines[*i][counter])
	{
		if (lines[*i][counter] == ',')
			result++;
		counter++;
	}
	if (result != 2)
		exit_and_print("Color is not valid", main, 0);
}

void	get_colors(t_main *main, char **lines, int *i)
{
	*i = 0;
	while (lines[*i])
	{
		main->helper.skip_space = skip_space(lines[*i], 0);
		if (ft_strncmp(lines[*i] + main->helper.skip_space, "F ", 2) == 0
			&& ++(main->helper.surface[0]))
			exctract_color_surface(main, lines, i,
				&main->helper.line_color_floor);
		else if (ft_strncmp(lines[*i] + main->helper.skip_space, "C ", 2) == 0
			&& ++(main->helper.surface[1]))
			exctract_color_surface(main, lines, i,
				&main->helper.line_color_ceiling);
		(*i)++;
	}
	if (main->helper.surface[0] != 1 || main->helper.surface[1] != 1)
		exit_and_print("Color is duplicated", main, 0);
	split_and_check(main);
	check_surface_is_valid(main, main->helper.color_floor,
		&main->file.floor_color);
	check_surface_is_valid(main, main->helper.color_ceiling,
		&main->file.ceiling_color);
	check_max_min(main);
	main->helper.color_floor = ft_free_split(main->helper.color_floor);
	main->helper.color_ceiling = ft_free_split(main->helper.color_ceiling);
}
