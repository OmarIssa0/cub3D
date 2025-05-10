/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:20:33 by oissa             #+#    #+#             */
/*   Updated: 2025/05/10 16:21:43 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	split_and_check(t_main *main)
{
	if (main->helper.line_color_floor == NULL
		|| main->helper.line_color_ceiling == NULL)
		exit_and_print("Color is missing", main, 0);
	main->helper.color_floor = ft_split(&main->helper.line_color_floor[2], ',');
	main->helper.color_ceiling = ft_split(&main->helper.line_color_ceiling[2],
			',');
	if (main->helper.color_floor == NULL || main->helper.color_ceiling == NULL)
		exit_and_print("Malloc failed", main, 0);
	if (main->helper.color_floor[0] == NULL
		|| main->helper.color_floor[1] == NULL
		|| main->helper.color_floor[2] == NULL)
		exit_and_print("Color is missing", main, 0);
	if (main->helper.color_ceiling[0] == NULL
		|| main->helper.color_ceiling[1] == NULL
		|| main->helper.color_ceiling[2] == NULL)
		exit_and_print("Color is missing", main, 0);
}

void	check_max_min(t_main *main)
{
	main->helper.index = -1;
	while (++main->helper.index < 3)
	{
		if (main->file.floor_color[main->helper.index] < 0
			|| main->file.floor_color[main->helper.index] > 255)
			exit_and_print("Color is not valid Floor", main, 0);
		if (main->file.ceiling_color[main->helper.index] < 0
			|| main->file.ceiling_color[main->helper.index] > 255)
			exit_and_print("Color is not valid Floor", main, 0);
	}
}
