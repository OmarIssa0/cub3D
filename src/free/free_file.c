/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:50:55 by oissa             #+#    #+#             */
/*   Updated: 2025/05/09 01:10:13 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_struct_file(t_main *main)
{
	if (main->file.north_texture != NULL)
	{
		free(main->file.north_texture);
		main->file.north_texture = NULL;
	}
	if (main->file.south_texture != NULL)
	{
		free(main->file.south_texture);
		main->file.south_texture = NULL;
	}
	if (main->file.west_texture != NULL)
	{
		free(main->file.west_texture);
		main->file.west_texture = NULL;
	}
	if (main->file.east_texture != NULL)
	{
		free(main->file.east_texture);
		main->file.east_texture = NULL;
	}
	if (main->file.pos_doors != NULL)
	{
		free(main->file.pos_doors);
		main->file.pos_doors = NULL;
	}
}
