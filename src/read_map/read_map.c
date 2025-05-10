/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:53:21 by oissa             #+#    #+#             */
/*   Updated: 2025/05/10 14:40:04 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	trim_EOF(t_main *main)
{
	close(main->fd);
	main->helper.trimmed_result = ft_strtrim(main->result, " \n\t ");
	if (main->helper.trimmed_result == NULL)
		exit_and_print("Malloc failed in trim", main, DONT_CLOSE_FD);
	free(main->result);
	main->result = main->helper.trimmed_result;
}

static void	read_for_file(t_main *main)
{
	string	line;
	string	tmp;

	main->result = ft_strdup("");
	if (main->result == NULL)
		exit_and_print("Malloc failed", main, CLOSE_FD);
	line = get_next_line(main->fd);
	while (line)
	{
		tmp = ft_strjoin(main->result, line);
		if (tmp == NULL)
		{
			free(line);
			exit_and_print("Malloc failed", main, CLOSE_FD);
		}
		free(main->result);
		free(line);
		main->result = tmp;
		line = get_next_line(main->fd);
	}
}

static void	cmp_for_line(t_main *main, char **split, int *i)
{
	if (ft_strncmp(split[*i] + main->helper.skip_space, "NO ", 3) == 0
		|| ft_strncmp(split[*i] + main->helper.skip_space, "SO ", 3) == 0
		|| ft_strncmp(split[*i] + main->helper.skip_space, "WE ", 3) == 0
		|| ft_strncmp(split[*i] + main->helper.skip_space, "EA ", 3) == 0
		|| ft_strncmp(split[*i] + main->helper.skip_space, "F ", 2) == 0
		|| ft_strncmp(split[*i] + main->helper.skip_space, "C ", 2) == 0
		|| ft_strncmp(split[*i] + main->helper.skip_space, "1", 1) == 0
		|| ft_strncmp(split[*i] + main->helper.skip_space, "0", 1) == 0
		|| split[*i][main->helper.skip_space] == '\0')
		(*i)++;
	else
	{
		ft_dprintf(2, RED "Error\nInvalid line: \"%s\"\n" RESET, split[*i]);
		ft_free_split(split);
		free_all(main);
		exit(EXIT_FAILURE);
	}
}

static void	loop_check(t_main *main, char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		main->helper.skip_space = skip_space(split[i], 0);
		cmp_for_line(main, split, &i);
	}
}

void	read_map(t_main *main)
{
	char	**split;

	check_file_name(main);
	main->fd = open(main->file_name, O_RDONLY);
	if (main->fd == -1)
		exit_and_print(strerror(errno), main, DONT_CLOSE_FD);
	read_for_file(main);
	trim_EOF(main);
	check_file_empty(main);
	split = ft_split(main->result, '\n');
	if (split == NULL)
		exit_and_print("Malloc failed", main, DONT_CLOSE_FD);
	loop_check(main, split);
	ft_free_split(split);
}
