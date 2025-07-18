/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:42:06 by oissa             #+#    #+#             */
/*   Updated: 2025/07/18 20:46:29 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_fps(t_main *main)
{
	static int			frame_count = 0;
	static double		fps = 0.0;
	static mlx_image_t	*image;
	char				*str;
	char				*temp;

	frame_count++;
	if (main->time.now[0] - main->time.last_time[0] >= 1.0)
	{
		fps = frame_count / (main->time.now[0] - main->time.last_time[0]);
		frame_count = 0;
		main->time.last_time[0] = main->time.now[0];
		str = ft_itoa((int)fps);
		if (!str)
			exit_and_print("Malloc Failed :(", main, DONT_CLOSE_FD);
		temp = str;
		str = ft_strjoin("FPS: ", str);
		if (!str)
			exit_and_print("Malloc Failed :(", main, DONT_CLOSE_FD);
		free(temp);
		if (image)
			mlx_delete_image(main->game.mlx, image);
		image = mlx_put_string(main->game.mlx, str, 10, 10);
		free(str);
	}
}
