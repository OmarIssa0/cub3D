/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:02:28 by oissa             #+#    #+#             */
/*   Updated: 2025/04/15 17:04:07 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void draw_walls(t_main *main)
{
    int x;
    int y;
    
    x = 0;
    while (x < SCREEN_WIDTH)
    {
        y = 0;
        while (y < SCREEN_HEIGHT)
        {
            if (y < main->raycasting.drawStart[x])
                mlx_put_pixel(main->game.image, x, y, main->game.color_ceiling);
            else if (y >= main->raycasting.drawStart[x] && y <= main->raycasting.drawEnd[x])
                mlx_put_pixel(main->game.image, x, y, rgb_32bit(143, 98, 28, main));
            else
                mlx_put_pixel(main->game.image, x, y, main->game.color_floor);
            y++;
        }
        x++;
    }
}
