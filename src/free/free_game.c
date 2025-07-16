/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:57:14 by oissa             #+#    #+#             */
/*   Updated: 2025/05/07 15:20:07 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_and_nullify(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		mlx_delete_texture(*ptr);
		*ptr = NULL;
	}
}

void	free_struct_game(t_main *main)
{
	int	i;

	i = -1;
	if (main->game.image != NULL)
	{
		mlx_delete_image(main->game.mlx, main->game.image);
		main->game.image = NULL;
	}
	free_and_nullify((void **)&main->game.texture_north);
	free_and_nullify((void **)&main->game.texture_south);
	free_and_nullify((void **)&main->game.texture_west);
	free_and_nullify((void **)&main->game.texture_east);
	free_and_nullify((void **)&main->game.texture_floor);
	free_and_nullify((void **)&main->game.texture_door_close);
	free_and_nullify((void **)&main->game.texture_door_open);
	free_and_nullify((void **)&main->game.texture_light_wall);
	free_and_nullify((void **)&main->game.texture_mid_wall);
	while (++i < 28)
		free_and_nullify((void **)&main->game.texture_weapon[i]);
	if (main->game.mlx != NULL)
	{
		mlx_terminate(main->game.mlx);
		main->game.mlx = NULL;
	}
}
