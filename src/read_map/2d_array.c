/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:23:27 by oissa             #+#    #+#             */
/*   Updated: 2025/05/12 20:19:52 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	loop_and_substr(t_main *main)
{
	while (main->result[main->split.j])
	{
		if (main->result[main->split.j] == '\n')
		{
			main->split.lines[main->split.i]
				= ft_substr(main->result, main->split.k,
					main->split.j - main->split.k + 1);
			if (main->split.lines[main->split.i] == NULL)
				exit_and_print("Malloc failed", main, 0);
			main->split.i++;
			main->split.k = main->split.j + 1;
		}
		main->split.j++;
	}
}

void	ft_split_file(t_main *main)
{
	main->split.len = ft_strlen(main->result);
	main->split.lines = ft_calloc(main->split.len, sizeof(char *));
	if (main->split.lines == NULL)
		exit_and_print("Malloc failed", main, DONT_CLOSE_FD);
	loop_and_substr(main);
	if (main->split.k < main->split.j)
	{
		main->split.lines[main->split.i] = ft_substr(main->result,
				main->split.k, main->split.j - main->split.k);
		if (main->split.lines[main->split.i] == NULL)
			exit_and_print("Malloc failed", main, DONT_CLOSE_FD);
		main->split.i++;
	}
	main->split.lines[main->split.i] = NULL;
	if (main->split.lines == NULL)
		exit_and_print("Malloc failed", main, DONT_CLOSE_FD);
	main->split.i = 0;
}
