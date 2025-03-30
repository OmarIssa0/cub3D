/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:39:38 by oissa             #+#    #+#             */
/*   Updated: 2025/03/30 16:35:45 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main (int ac, char **av)
{
    // ? Check if the arguments are valid
    if (ac != 2 && ft_dprintf(2, "Error\nUsage: ./cub3D <map.cub>\n"))
        return (1);
    // ? create the main struct
    t_main main;
    // ? ininitialize the main struct
    ft_bzero(&main, sizeof(t_main));
    main.file_name = ft_strdup(av[1]);
    /*
        ? Read the map 
        * and get the values
    */
    read_map(&main);
    // ? Check if the content
    check_map(&main);
    // ? Initialize the game
    // init_game(&main);
    // ? Initialize the textures
    // ? loop the game
    // mlx_loop(main.game.mlx);
    free_all(&main);
}