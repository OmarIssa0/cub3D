/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:39:38 by oissa             #+#    #+#             */
/*   Updated: 2025/05/13 13:12:46 by oissa            ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_main	main;

	if (ac != 2 && ft_dprintf(2, "Error\nUsage: ./cub3D <map.cub>\n"))
		return (1);
	ft_bzero(&main, sizeof(t_main));
	main.file_name = ft_strdup(av[1]);
	if (main.file_name == NULL)
		exit_and_print("Malloc Failed :(", &main, 0);
	read_map(&main);
	check_map(&main);
	init_game(&main);
	mlx_loop(main.game.mlx);
	free_all(&main);
	return (EXIT_SUCCESS);
}
