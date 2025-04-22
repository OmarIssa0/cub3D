/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:52:41 by oissa             #+#    #+#             */
/*   Updated: 2025/04/19 14:59:06 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_struct_helper(t_main *main)
{
	if (main->helper.color_floor != NULL)
	{
		main->helper.color_floor = ft_free_split(main->helper.color_floor);
	}
	if (main->helper.color_ceiling != NULL)
	{
		main->helper.color_ceiling = ft_free_split(main->helper.color_ceiling);
	}
	if (main->helper.trim != NULL)
	{
		free(main->helper.trim);
		main->helper.trim = NULL;
	}
}
