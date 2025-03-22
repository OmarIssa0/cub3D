/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:53:21 by oissa             #+#    #+#             */
/*   Updated: 2025/03/22 22:36:01 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void read_for_file(t_main *main)
{
    char *line;
    char *tmp;

    main->result = ft_strdup("");
    if (main->result == NULL)
    {
        close(main->fd);
        exit_and_print("Malloc failed", main, 1);
    }
    line = get_next_line(main->fd);
    while (line)
    {
        tmp = ft_strjoin(main->result, line);
        if (tmp == NULL)
        {
            free(main->result);
            free(line);
            close(main->fd);
            exit_and_print("Malloc failed", main, 1);
        }
        free(main->result);
        free(line);
        main->result = tmp;
        line = get_next_line(main->fd);
    }
    close(main->fd);
}



void   read_map(t_main *main)
{
    check_file_name(main);
    main->fd = open(main->file_name, O_RDONLY);
    if (main->fd == -1)
    {
        ft_dprintf(2, "Error\n%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    read_for_file(main);
    check_file_empty(main);
    get_values(main);
}
