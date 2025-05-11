/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 00:11:54 by oissa             #+#    #+#             */
/*   Updated: 2025/05/11 22:00:44 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_and_print(string str, t_main *main, int status)
{
	ft_dprintf(2, RED "Error:\n%s\n" RESET, str);
	if (status == CLOSE_FD)
		close(main->fd);
	free_all(main);
	exit(EXIT_FAILURE);
}

static void	print_error(t_main *main)
{
	if (main->helper.new_i == main->helper.new_x
		&& main->helper.new_j == main->helper.new_y
		&& main->file.map[main->helper.new_i][main->helper.new_j] == '\n')
		ft_printf("%s\\n\n%s", RED, RESET);
	if (main->helper.new_i == main->helper.new_x
		&& main->helper.new_j == main->helper.new_y
		&& main->file.map[main->helper.new_i][main->helper.new_j] == ' ')
		ft_printf("%s\" \"%s", RED, RESET);
	else if (main->helper.new_i == main->helper.new_x
		&& main->helper.new_j == main->helper.new_y)
		ft_printf("%s%c%s", RED,
			main->file.map[main->helper.new_i][main->helper.new_j], RESET);
	else
		ft_printf("%s%c%s", GREEN,
			main->file.map[main->helper.new_i][main->helper.new_j], RESET);
}

void	print_map_for_error(t_main *main, int i, int j, char *string)
{
	ft_printf("%sError:\n%s%s", RED, string, RESET);
	main->helper.new_x = i;
	main->helper.new_y = j;
	while (main->file.map[main->helper.new_i])
	{
		main->helper.new_j = 0;
		while (main->file.map[main->helper.new_i][main->helper.new_j])
		{
			print_error(main);
			main->helper.new_j++;
		}
		main->helper.new_i++;
	}
	free_all(main);
	exit(EXIT_FAILURE);
}
