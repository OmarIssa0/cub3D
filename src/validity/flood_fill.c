/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:44:40 by oissa             #+#    #+#             */
/*   Updated: 2025/05/11 21:50:34 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
    * * flood_fill_map
    !    i - 1 --> Up
    !    i + 1 --> Down
    !    j - 1 --> Left
    !    j + 1 --> Right
*/
void	flood_fill_map(t_main *main, int i, int j)
{
	if (i < 0 || j < 0 || !main->file.map[i] || !main->file.map[i][j])
		exit_and_print("Map is not closed (out of bounds)", main, 0);
	if (main->file.map[i][j] == ' ')
		print_map_for_error(main, i, j, "Map is not closed (space found)\n");
	if (main->file.map[i][j] == '1' || main->file.map[i][j] == '2')
		return ;
	if (main->file.map[i][j] == 'D')
	{
		main->file.pos_doors[main->file.nb_door].x = j;
		main->file.pos_doors[main->file.nb_door].y = i;
		main->file.nb_door++;
	}
	main->file.map[i][j] = '2';
	flood_fill_map(main, i - 1, j);
	flood_fill_map(main, i + 1, j);
	flood_fill_map(main, i, j - 1);
	flood_fill_map(main, i, j + 1);
}

void	fix_map(t_main *main)
{
	int	i;
	int	j;
	int	number_door;

	i = 0;
	j = -1;
	while (main->file.map[i])
	{
		j = 0;
		while (main->file.map[i][++j])
		{
			if (main->file.map[i][j] == '2')
				main->file.map[i][j] = '0';
		}
		i++;
	}
	number_door = main->file.nb_door;
	while (number_door > 0)
	{
		main->file.map[main->file.pos_doors[number_door
			- 1].y][main->file.pos_doors[number_door - 1].x] = 'D';
		number_door--;
	}
	main->file.map[main->game.player_y][main->game.player_x]
		= main->game.player_direction;
}

void	check_player_surrounded_by_walls(t_main *main)
{
	main->file.pos_doors = ft_calloc(sizeof(t_point), main->file.nb_door + 1);
	if (main->file.pos_doors == NULL)
		exit_and_print("Malloc Failed :(", main, 0);
	main->file.nb_door = 0;
	flood_fill_map(main, main->game.player_y, main->game.player_x);
	fix_map(main);
}
