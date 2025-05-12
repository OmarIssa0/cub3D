/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:41:14 by oissa             #+#    #+#             */
/*   Updated: 2025/05/12 21:08:57 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_main(t_main *main)
{
	if (main->file_name)
	{
		free(main->file_name);
		main->file_name = NULL;
	}
	if (main->result)
	{
		free(main->result);
		main->result = NULL;
	}
}

void	free_struct_splitter(t_main *main)
{
	if (main->split.lines != NULL)
	{
		main->split.lines = ft_free_split(main->split.lines);
		main->split.lines = NULL;
	}
}

void	free_struct_raycasting(t_main *main)
{
	if (main->raycasting.line_height != NULL)
	{
		free(main->raycasting.line_height);
		main->raycasting.line_height = NULL;
	}
}

void	free_all(t_main *main)
{
	free_main(main);
	free_struct_file(main);
	free_struct_helper(main);
	free_struct_splitter(main);
	free_struct_raycasting(main);
	free_struct_game(main);
}
