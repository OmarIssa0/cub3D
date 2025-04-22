/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:41:14 by oissa             #+#    #+#             */
/*   Updated: 2025/04/19 14:59:27 by oissa            ###   ########.fr       */
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
	if (main->raycasting.lineHeight != NULL)
	{
		free(main->raycasting.lineHeight);
		main->raycasting.lineHeight = NULL;
	}
}

void	free_all(t_main *main)
{
	free_main(main);
	// ? free struct file
	free_struct_file(main);
	// ? free struct helper
	free_struct_helper(main);
	// ? free struct splitter
	free_struct_splitter(main);
	// ? free struct raycasting
	free_struct_raycasting(main);
	// ? free struct game
	free_struct_game(main);
}
