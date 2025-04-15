/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_for_uint32.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:21:25 by oissa             #+#    #+#             */
/*   Updated: 2025/04/15 16:58:18 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
    ? save color 32bit int struct
*/
void transformation_32bit(t_main *main)
{
    main->game.color_ceiling = rgb_32bit(main->file.ceiling_color[0],
        main->file.ceiling_color[1], main->file.ceiling_color[2], main);
    main->game.color_floor = rgb_32bit(main->file.floor_color[0], 
        main->file.floor_color[1], main->file.floor_color[2], main);
}

/*
    ! rgb
    * r -> red
    * g -> green
    * b -> blue
    ? shift bit 24 | 16 | 8 | 0xFF
*/
uint32_t rgb_32bit(int red, int green, int blue, t_main *main)
{
    uint32_t color;

    if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
        exit_and_print("Color not valid for 32 bit", main, 0);
    color = (red << 24) | (green << 16) | (blue << 8) | (0xFF);
    return (color);
}