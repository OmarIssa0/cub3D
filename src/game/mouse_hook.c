/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:11:03 by oissa             #+#    #+#             */
/*   Updated: 2025/04/15 17:22:01 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>


void rotate_player(t_player *player, double angle)
{
    double old_dir_x = player->dir_x;
    player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
    player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);
    
    double old_plane_x = player->plane_x;
    player->plane_x = player->plane_x * cos(angle) - player->plane_y * sin(angle);
    player->plane_y = old_plane_x * sin(angle) + player->plane_y * cos(angle);
}

void move_player(t_main *main, double move_x, double move_y)
{
    double new_x = main->player.x + move_x;
    double new_y = main->player.y + move_y;
    if (new_x < 0 || new_x >= main->game.width_map ||
        new_y < 0 || new_y >= main->game.height_map) 
        return;
    // التحقق من الاصطدام مع الجدران
    if (main->file.map[(int)new_y][(int)main->player.x] != '1')
    main->player.y = new_y;
    if (main->file.map[(int)main->player.y][(int)new_x] != '1')
    main->player.x = new_x;
}
void handle_mouse_rotation(t_main *main)
{
    static int last_x = SCREEN_WIDTH / 2;
    int current_x, current_y;

    mlx_get_mouse_pos(main->game.mlx, &current_x, &current_y);

    int delta_x = current_x - last_x;
    last_x = current_x;

    if (delta_x != 0)
    {
        float sensitivity = 0.0005f;
        float angle = delta_x * sensitivity;

        rotate_player(&main->player, angle); // دالة تدور اتجاه اللاعب
    }

    // نعيد ضبط المؤشر للمنتصف كل مرة (لأنه ما يخرجش)
    mlx_set_mouse_pos(main->game.mlx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    last_x = SCREEN_WIDTH / 2;
}

