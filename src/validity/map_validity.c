/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:18:38 by oissa             #+#    #+#             */
/*   Updated: 2025/03/23 00:11:28 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_map(t_main *main)
{
    // ? Check if the content
    check_map_content(main);
    
}

void print_map_for_error(t_main *main, int i, int j, char *string)
{
    ft_printf("%sError:\n%s%s", RED, string, RESET);
    int x = i;
    int y = j;
    int new_i = 0;
    int new_j = 0;
    while (main->file.map[new_i])
    {
        new_j = 0;
        while (main->file.map[new_i][new_j])
        {
            if (new_i == x && new_j == y && main->file.map[new_i][new_j] == '\n')
                ft_printf("%s\\n\n%s", RED, RESET);
            else if (new_i == x && new_j == y)
                ft_printf("%s%c%s", RED, main->file.map[new_i][new_j], RESET);
            else
                ft_printf("%s%c%s", GREEN, main->file.map[new_i][new_j], RESET);
            new_j++;
        }
        new_i++;
    }
    free_all(main);
    exit(EXIT_FAILURE);
}

void check_map_content(t_main *main)
{
    int i = 0;
    int j = 0;
    if (!main->file.map)
        exit_and_print("Map is not initialized", main, 0);
    while (main->file.map[i])
    {
        j = 0;
        while (main->file.map[i][j])
        {
            if (main->file.map[i][j] == '\n' && j == 0)
                print_map_for_error(main, i, j, "new line at the beginning of the line\n");
            if (main->file.map[i][j] != ' ' && main->file.map[i][j] != '1'
                && main->file.map[i][j] != '0' && main->file.map[i][j] != '\n'
                && main->file.map[i][j] != 'N' && main->file.map[i][j] != 'S'
                && main->file.map[i][j] != 'W' && main->file.map[i][j] != 'E')
                    print_map_for_error(main, i, j, "Invalid character in the map\n");
            j++;
        }
        i++;
    }   
}
