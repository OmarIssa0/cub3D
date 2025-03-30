/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:49:26 by oissa             #+#    #+#             */
/*   Updated: 2025/03/27 16:54:53 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_game(t_main *main)
{
    main->game.mlx = mlx_init(main->game.width_map * 32, main->game.height_map * 32, "Cub3D", true);
    if (main->game.mlx == NULL)
    {
        free_all(main);
        exit_and_print((char *)mlx_strerror(mlx_errno), main, 0);
    }
}