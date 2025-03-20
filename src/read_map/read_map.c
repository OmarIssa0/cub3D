/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:53:21 by oissa             #+#    #+#             */
/*   Updated: 2025/03/21 01:13:10 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void check_map(t_main *main)
{
    int len;

    len = ft_strlen(main->file_name);
    if (len < 4 || ft_strncmp(&main->file_name[len - 4], ".cub", 4) != 0)
        exit_and_print("File extension is not valid", main, 0);
}

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

int skip_space(char *str, int i)
{
    while (ft_isspace(str[i]))
        i++;
    return (i);
}

static void check_map_empty(t_main *main)
{
    int tmp;

    tmp = skip_space(main->result, 0);
    if (main->result[tmp] == '\0')
    {
        free(main->result);
        exit_and_print("Map is empty", main, 0);
    }
}

void   read_map(t_main *main)
{
    check_map(main);
    main->fd = open(main->file_name, O_RDONLY);
    if (main->fd == -1)
    {
        ft_dprintf(2, "Error\n%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    read_for_file(main);
    check_map_empty(main);
}
