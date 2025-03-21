/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:57:14 by oissa             #+#    #+#             */
/*   Updated: 2025/03/21 21:57:20 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_game(t_main *main)
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