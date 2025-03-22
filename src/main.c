/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:39:38 by oissa             #+#    #+#             */
/*   Updated: 2025/03/22 22:57:10 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main (int ac, char **av)
{
    if (ac != 2 && ft_dprintf(2, "Error\nUsage: ./cub3D <map.cub>\n"))
        return (1);
    t_main main;
    ft_bzero(&main, sizeof(t_main));
    main.file_name = ft_strdup(av[1]);
    read_map(&main);
    // ? Check if the content
    check_map(&main);
    free_all(&main);
}