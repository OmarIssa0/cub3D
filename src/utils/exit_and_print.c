/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 00:11:54 by oissa             #+#    #+#             */
/*   Updated: 2025/03/21 00:16:17 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    exit_and_print(char *str, t_main *main, int status)
{
    ft_dprintf(2, RED"Error:\n%s\n"RESET, str);
    if (status == 1)
        close(main->fd);
    exit(EXIT_FAILURE);
}