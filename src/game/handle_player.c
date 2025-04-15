/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:32:12 by oissa             #+#    #+#             */
/*   Updated: 2025/04/15 16:51:43 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void init_player(t_main *main)
{
    if (main->game.player_direction == 'N')
    {
        main->player.dir_x = 0;
        main->player.dir_y = -1;
        main->player.plane_x = 0.66;
        main->player.plane_y = 0;
    }
    else if (main->game.player_direction == 'S')
    {
        main->player.dir_x = 0;
        main->player.dir_y = 1;
        main->player.plane_x = -0.66;
        main->player.plane_y = 0;
    }
    else if (main->game.player_direction == 'E')
    {
        main->player.dir_x = 1;
        main->player.dir_y = 0;
        main->player.plane_x = 0;
        main->player.plane_y = -0.66;
    }
    else if (main->game.player_direction == 'W')
    {
        main->player.dir_x = -1;
        main->player.dir_y = 0;
        main->player.plane_x = 0;
        main->player.plane_y = 0.66;
    }
    main->player.x = main->game.player_x + 0.5;
    main->player.y = main->game.player_y + 0.5;
    main->file.map[main->game.player_y][main->game.player_x] = '0';
}
