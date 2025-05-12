/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:24:52 by oissa             #+#    #+#             */
/*   Updated: 2025/05/12 20:14:23 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file_name(t_main *main)
{
	int	len;

	len = ft_strlen(main->file_name);
	if (len < 4 || ft_strncmp(&main->file_name[len - 4], ".cub", 4) != 0)
		exit_and_print("File extension is not valid", main, DONT_CLOSE_FD);
}

int	skip_space(char *str, int i)
{
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

void	check_file_empty(t_main *main)
{
	int	tmp;

	tmp = skip_space(main->result, 0);
	if (main->result[tmp] == '\0')
		exit_and_print("Map is empty", main, DONT_CLOSE_FD);
}
