/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:18:38 by oissa             #+#    #+#             */
/*   Updated: 2025/03/30 16:36:51 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void flood_fill_map(t_main *main, int i, int j)
{
    if (i < 0 || j < 0 || !main->file.map[i] || !main->file.map[i][j])
        exit_and_print("Map is not closed (out of bounds)", main, 0);
    if (main->file.map[i][j] == ' ')
    {
        print_map_for_error(main, i, j, "Map is not closed (space found)\n");
        // exit_and_print("Map is not closed (space found)", main, 0);
    }

    if (main->file.map[i][j] == '1' || main->file.map[i][j] == '2')
        return;

    main->file.map[i][j] = '2';


    flood_fill_map(main, i - 1, j); // Up   - 1
    flood_fill_map(main, i + 1, j); // Down  + 1
    flood_fill_map(main, i, j - 1); // Left  - 1
    flood_fill_map(main, i, j + 1); // Right + 1
}
void   fix_map(t_main *main)
{
    int i = 0;
    int j = 0;
    while (main->file.map[i])
    {
        j = 0;
        while (main->file.map[i][j])
        {
            if (main->file.map[i][j] == '2')
                main->file.map[i][j] = '0';
            j++;
        }
        i++;
    }
    main->file.map[main->game.player_y][main->game.player_x] = main->game.player_direction;
}

// Function to validate if the map is closed
void check_map_surrounded_by_walls(t_main *main)
{
    // int i = 0;
    // int j = 0;

    // while (main->file.map[i])
    // {
    //     j = 0;
    //     while (main->file.map[i][j])
    //     {
    //         if (main->file.map[i][j] == 'E' || main->file.map[i][j] == 'N' ||
    //             main->file.map[i][j] == 'S' || main->file.map[i][j] == 'W' )
    //         {
    //             flood_fill_map(main, i, j);
    //             return;
    //         }
    //         j++;
    //     }
    //     i++;
    // }
    flood_fill_map(main, main->game.player_y, main->game.player_x);
    fix_map(main);
    // int i = 0;
    // while (main->file.map[i])
    // {
    //     ft_printf("%s%s%s", GREEN, main->file.map[i], RESET);
    //     i++;
    // }

    
    // flood_fill_map(main, main->game.player_y, main->game.player_x);
    // exit_and_print("No starting point found in the map", main, 0);
}

void calculate_height_width(t_main *main) {
    int i = 0;
    int max = 0;
    
    while (main->file.map[i]) {
        int current_len = ft_strlen(main->file.map[i]);
        if (current_len > max) max = current_len;
        i++;
    }
    
    main->game.height_map = i;
    main->game.width_map = max;
}
void check_map(t_main *main)
{
    // ? Check if the content
    check_map_content(main);
    // ? Check if only one player is in the map
    check_player(main);
    // ? Calculate the height and width of the map
    calculate_height_width(main);
    // ? Check if the map is surrounded by walls
    check_map_surrounded_by_walls(main);
    // ft_printf("Height: %d\n", main->game.height_map);
    // ft_printf("Width: %d\n", main->game.width_map);
    // ft_printf("Player x: %d\n", main->game.player_x);
    // ft_printf("Player y: %d\n", main->game.player_y);
    // ft_printf("South: %s\n" , main->file.south_texture);
    // ft_printf("West: %s\n" , main->file.west_texture);
    // ft_printf("East: %s\n" , main->file.east_texture);
    // ft_printf("North: %s\n" , main->file.north_texture);
    // ft_printf("Floor:  %d %d %d\n", main->file.floor_color[0], main->file.floor_color[1], main->file.floor_color[2]);
    // ft_printf("Ceiling:  %d %d %d\n", main->file.ceiling_color[0], main->file.ceiling_color[1], main->file.ceiling_color[2]);
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
            if (new_i == x && new_j == y && main->file.map[new_i][new_j] == ' ')
                ft_printf("%s\" \"%s", RED, RESET);
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

void check_player(t_main *main)
{
    int i = 0;
    int j = 0;
    int player = 0;
    while (main->file.map[i])
    {
        j = 0;
        while (main->file.map[i][j])
        {
            if (player > 1)
            {
                ft_printf("%sError:\nMore than one player in the map: [%c]\n%s", RED, main->file.map[i][j - 1] ,RESET);
                int x = i;
                int y = j - 1;
                int new_i = 0;
                int new_j = 0;
                while (main->file.map[new_i])
                {
                    new_j = 0;
                    while (main->file.map[new_i][new_j])
                    {
                        if (new_i == x && new_j == y)
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
            if (main->file.map[i][j] == 'N' || main->file.map[i][j] == 'S'
                || main->file.map[i][j] == 'W' || main->file.map[i][j] == 'E')
            {
                main->game.player_x = j;
                main->game.player_y = i;
                main->game.player_direction = main->file.map[i][j];
                player++;
            }
            j++;
        }
        i++;
    }
    if (player == 0)
        exit_and_print("No player found in the map", main, 0);
}
