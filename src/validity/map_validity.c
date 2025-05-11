/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:18:38 by oissa             #+#    #+#             */
/*   Updated: 2025/05/11 22:05:28 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_height_width(t_main *main)
{
	int	i;
	int	max;
	int	current_len;

	i = 0;
	max = 0;
	while (main->file.map[i])
	{
		current_len = ft_strlen(main->file.map[i]);
		if (current_len > max)
			max = current_len;
		i++;
	}
	main->game.height_map = i;
	main->game.width_map = max;
}

void	check_map(t_main *main)
{
	get_values(main);
	check_map_content(main);
	check_player(main);
	calculate_height_width(main);
	check_player_surrounded_by_walls(main);
}

void	check_player(t_main *main)
{
	while (main->file.map[main->helper.x])
	{
		main->helper.y = 0;
		while (main->file.map[main->helper.x][main->helper.y])
		{
			if (main->helper.player > 1)
				print_map_for_error(main, main->helper.x, main->helper.y - 1,
					"More than one player in the map\n");
			if (main->file.map[main->helper.x][main->helper.y] == 'N'
				|| main->file.map[main->helper.x][main->helper.y] == 'S'
				|| main->file.map[main->helper.x][main->helper.y] == 'W'
				|| main->file.map[main->helper.x][main->helper.y] == 'E')
			{
				main->game.player_x = main->helper.y;
				main->game.player_y = main->helper.x;
				main->game.player_direction
					= main->file.map[main->helper.x][main->helper.y];
				main->helper.player++;
			}
			main->helper.y++;
		}
		main->helper.x++;
	}
	if (main->helper.player == 0)
		exit_and_print("No player found in the map", main, 0);
}
