/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:18:38 by oissa             #+#    #+#             */
/*   Updated: 2025/05/10 18:42:06 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	flood_fill_map(t_main *main, int i, int j)
{
	if (i < 0 || j < 0 || !main->file.map[i] || !main->file.map[i][j])
		exit_and_print("Map is not closed (out of bounds)", main, 0);
	if (main->file.map[i][j] == ' ')
	{
		print_map_for_error(main, i, j, "Map is not closed (space found)\n");
		// exit_and_print("Map is not closed (space found)", main, 0);
	}
	if (main->file.map[i][j] == '1' || main->file.map[i][j] == '2')
		return ;
	if (main->file.map[i][j] == 'D')
	{
		main->file.pos_doors[main->file.nb_door].x = j;
		main->file.pos_doors[main->file.nb_door].y = i;
		main->file.nb_door++;
	}
	main->file.map[i][j] = '2';
	flood_fill_map(main, i - 1, j); // Up   - 1
	flood_fill_map(main, i + 1, j); // Down  + 1
	flood_fill_map(main, i, j - 1); // Left  - 1
	flood_fill_map(main, i, j + 1); // Right + 1
}
void	fix_map(t_main *main)
{
	int	i;
	int	j;
	int	number_door;

	i = 0;
	j = 0;
	while (main->file.map[i])
	{
		j = 0;
		while (main->file.map[i][j])
		{
			if (main->file.map[i][j] == '2')
				main->file.map[i][j] = '0';
			j++;
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
	main->file.map[main->game.player_y][main->game.player_x] = main->game.player_direction;
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

void	print_map_for_error(t_main *main, int i, int j, char *string)
{
	int	x;
	int	y;
	int	new_i;
	int	new_j;

	ft_printf("%sError:\n%s%s", RED, string, RESET);
	x = i;
	y = j;
	new_i = 0;
	new_j = 0;
	while (main->file.map[new_i])
	{
		new_j = 0;
		while (main->file.map[new_i][new_j])
		{
			if (new_i == x && new_j == y
				&& main->file.map[new_i][new_j] == '\n')
				ft_printf("%s\\n\n%s", RED, RESET);
			if (new_i == x && new_j == y && main->file.map[new_i][new_j] == ' ')
				ft_printf("%s\" \"%s", RED, RESET);
			else if (new_i == x && new_j == y)
				ft_printf("%s%c%s", RED, main->file.map[new_i][new_j], RESET);
			else
				ft_printf("%s%c%s", GREEN, main->file.map[new_i][new_j], RESET);
			new_j++;
		}
		new_i++;
	}
	free_all(main);
	exit(EXIT_FAILURE);
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
				print_map_for_error(main, i, j,
					"Invalid character in the map\n");
			j++;
		}
		i++;
	}
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
				main->game.player_direction = main->file.map[main->helper.x][main->helper.y];
				main->helper.player++;
			}
			main->helper.y++;
		}
		main->helper.x++;
	}
	if (main->helper.player == 0)
		exit_and_print("No player found in the map", main, 0);
}
