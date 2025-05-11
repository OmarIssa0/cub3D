/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 22:01:53 by oissa             #+#    #+#             */
/*   Updated: 2025/05/11 22:04:19 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_if_statment(t_main *main, int i, int j)
{
	if (main->file.map[i][j] == 'D')
		main->file.nb_door++;
	if (main->file.map[i][j] == '\n' && j == 0)
		print_map_for_error(main, i, j,
			"new line at the beginning of the line\n");
	if (main->file.map[i][j] != ' ' && main->file.map[i][j] != '1'
		&& main->file.map[i][j] != '0' && main->file.map[i][j] != '\n'
		&& main->file.map[i][j] != 'N' && main->file.map[i][j] != 'S'
		&& main->file.map[i][j] != 'W' && main->file.map[i][j] != 'E'
		&& main->file.map[i][j] != 'D')
		print_map_for_error(main, i, j, "Invalid character in the map\n");
}

void	check_map_content(t_main *main)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!main->file.map)
		exit_and_print("Map is not initialized", main, 0);
	while (main->file.map[i])
	{
		j = 0;
		while (main->file.map[i][j])
		{
			check_if_statment(main, i, j);
			j++;
		}
		i++;
	}
}
