/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:39:38 by oissa             #+#    #+#             */
/*   Updated: 2025/05/07 21:57:15 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	
*				  N
!                 ^
!				  |
!				  |
!			      |
!				  |
!			      |
* W	<-------------o-------------> E
!				  |
!				  |
!				  |
!				  |
!				  |
!                 v
*				  S
*/

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
    if (main.file_name == NULL)
        exit_and_print("Malloc Failed :(", &main, 0);
    read_map(&main);
    // ? Check if the content
    check_map(&main);
    // ? Initialize the game
    init_game(&main);
    // ? loop the game
    mlx_loop(main.game.mlx);
    free_all(&main);
    return (EXIT_SUCCESS);
}
