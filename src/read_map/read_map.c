/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:53:21 by oissa             #+#    #+#             */
/*   Updated: 2025/03/29 21:28:02 by oissa            ###   ########.fr       */
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
            free(line);
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
    // ? Check if the file name is valid .cub 
    check_file_name(main);
    // ? open the file
    main->fd = open(main->file_name, O_RDONLY);
    if (main->fd == -1)
    {
        exit_and_print(strerror(errno), main, 0);
        exit(EXIT_FAILURE);
    }
    // ? read the file
    read_for_file(main);
    // ? Check if the file is empty
    check_file_empty(main);
    // ? check if the file is valid
    char **split = ft_split(main->result, '\n');
    if (split == NULL)
        exit_and_print("Malloc failed", main, 0);
    int i = 0;
    while (split[i])
    {
        if (split[i][0] == '\0')
        {
            i++;
            continue;
        }
        int skip = skip_space(split[i], 0);
        if (split[i][0] == '\0')
        {
            i++;
            continue;
        }
        if (ft_strncmp(split[i] + skip, "NO ", 3) == 0
        || ft_strncmp(split[i] + skip, "SO ", 3) == 0
        || ft_strncmp(split[i] + skip, "WE ", 3) == 0
        || ft_strncmp(split[i] + skip, "EA ", 3) == 0 
        || ft_strncmp(split[i] + skip, "F ", 2) == 0
        || ft_strncmp(split[i] + skip, "C ", 2) == 0
        || ft_strncmp(split[i] + skip, "1", 1) == 0)
            i++;
        else
        {
            ft_dprintf(2,RED "Error\nInvalid line: \"%s\"\n" RESET, split[i]);
            ft_free_split(split);
            free_all(main);
            exit(EXIT_FAILURE);
        }
    }
    ft_free_split(split);
    // ? get the structure values
    get_values(main);
}
