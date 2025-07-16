/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:09:47 by oissa             #+#    #+#             */
/*   Updated: 2025/05/12 21:09:47 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_walls(t_main *main)
{
	static int	i = 0;

	main->draw_bit.x = 0;
	while (main->draw_bit.x < SCREEN_WIDTH)
	{
		main->draw_bit.wall_x = main->raycasting.wall_x[main->draw_bit.x];
		main->draw_bit.side = main->raycasting.side[main->draw_bit.x];
		initialize_wall_texture(main);
		calculate_tex_x(main);
		update_day_night_cycle(main, &i);
		draw_column_pixels(main, i);
		main->draw_bit.x++;
	}
}
