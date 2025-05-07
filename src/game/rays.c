/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:13:05 by oissa             #+#    #+#             */
/*   Updated: 2025/05/08 00:30:45 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void calculate_camx_rays(t_main *main, int x)
{
    main->math.camera_x = 2 * x / (float)SCREEN_WIDTH - 1;
    main->math.ray_dir_x = main->player.dir_x + main->player.plane_x * main->math.camera_x;
    main->math.ray_dir_y = main->player.dir_y + main->player.plane_y * main->math.camera_x;
}

void calulate_delta_dist_and_side(t_main *main)
{
    if (main->math.ray_dir_x == 0)
        main->math.delta_dist_x = 1e30;
    else
        main->math.delta_dist_x = fabs(1 / main->math.ray_dir_x);
    if (main->math.ray_dir_y == 0)
        main->math.delta_dist_y = 1e30;
    else
        main->math.delta_dist_y = fabs(1 / main->math.ray_dir_y);
    if (main->math.ray_dir_x < 0)
    {
        main->math.step_x = -1;
        main->math.side_dist_x = (main->player.x - main->math.map_x) * main->math.delta_dist_x;
    }
    else
    {
        main->math.step_x = 1;
        main->math.side_dist_x = (main->math.map_x + 1.0 - main->player.x) * main->math.delta_dist_x;
    }
    if (main->math.ray_dir_y < 0)
    {
        main->math.step_y = -1;
        main->math.side_dist_y = (main->player.y - main->math.map_y) * main->math.delta_dist_y;
    }
    else
    {
        main->math.step_y = 1;
        main->math.side_dist_y = (main->math.map_y + 1.0 - main->player.y) * main->math.delta_dist_y;
    }
}

void DDA_algorithm(t_main *main, int x)
{
    main->math.hit = 0;

    while (main->math.hit == 0)
    {
        if (main->math.side_dist_x < main->math.side_dist_y)
        {
            main->math.side_dist_x += main->math.delta_dist_x;
            main->math.map_x += main->math.step_x;
            main->math.side = 0; // الجدار في الاتجاه الأفقي
        }
        else
        {
            main->math.side_dist_y += main->math.delta_dist_y;
            main->math.map_y += main->math.step_y;
            main->math.side = 1; // الجدار في الاتجاه العمودي
        }

        if (main->file.map[main->math.map_y][main->math.map_x] == '1'
            || main->file.map[main->math.map_y][main->math.map_x] == 'D') // التحقق من الاصطدام بالجدار
            main->math.hit = 1;
    }
    if (main->file.map[main->math.map_y][main->math.map_x] == 'D')
    {
        int i = 0;
    int found = 0;
    while (i < main->file.nb_door)
    {
        if (main->file.pos_doors[i].x == main->math.map_x &&
            main->file.pos_doors[i].y == main->math.map_y)
        {
            found = 1;
            if (main->file.pos_doors[i].is_open == 1)
                main->raycasting.is_door[x] = 1; 
            else
                main->raycasting.is_door[x] = 2; 
            break;
        }
        i++;
    }
    if (!found)
        main->raycasting.is_door[x] = 2;
}
    else
        main->raycasting.is_door[x] = 0;
    main->raycasting.side[x] = main->math.side;
}

void calculate_wall(t_main *main)
{
    if (main->math.side == 0)
        main->math.perp_wall_dist = (main->math.map_x - main->player.x + (1 - main->math.step_x) / 2) / main->math.ray_dir_x;
    else
        main->math.perp_wall_dist = (main->math.map_y - main->player.y + (1 - main->math.step_y) / 2) / main->math.ray_dir_y;
}

void calculate_height_and_down_for_wall(t_main *main, int x)
{
    main->math.drawStart = -main->math.lineHeight / 2 + SCREEN_HEIGHT / 2;
    if (main->math.drawStart < 0)
        main->math.drawStart = 0;
    main->math.drawEnd = main->math.lineHeight / 2 + SCREEN_HEIGHT / 2;
    if (main->math.drawEnd >= SCREEN_HEIGHT)
        main->math.drawEnd = SCREEN_HEIGHT - 1;

    main->raycasting.drawStart[x] = main->math.drawStart;
    main->raycasting.drawEnd[x] = main->math.drawEnd;

    if (main->math.side == 0)
        main->math.wall_x = main->player.y + main->math.perp_wall_dist * main->math.ray_dir_y;
    else
        main->math.wall_x = main->player.x + main->math.perp_wall_dist * main->math.ray_dir_x;
    main->math.wall_x -= floor(main->math.wall_x); // نأخذ الجزء الكسري فقط

    main->raycasting.wall_x[x] = main->math.wall_x;
    main->raycasting.ray_dir_x[x] = main->math.ray_dir_x;
    main->raycasting.ray_dir_y[x] = main->math.ray_dir_y;
}

void cast_rays(t_main *main)
{
    int x;

    x = -1;
    while (++x < SCREEN_WIDTH)
    {
        // ! 1️⃣ حساب اتجاه الشعاع لكل عمود
        calculate_camx_rays(main, x);
        // ! 2️⃣ تحديد موقع اللاعب في الخريطة
        main->math.map_x = (int)main->player.x; 
        main->math.map_y = (int)main->player.y; 
        // ! 3️⃣ حساب خطوات الأشعة والمسافات
        calulate_delta_dist_and_side(main);
        // ! 4️⃣ تنفيذ خوارزمية DDA
        DDA_algorithm(main, x);
        // ! 5️⃣ حساب المسافة إلى الجدار
        calculate_wall(main);
        // ! 6️⃣ حساب ارتفاع الجدار بناءً على المسافة
        main->math.lineHeight = (int)(SCREEN_HEIGHT / main->math.perp_wall_dist);
        main->raycasting.lineHeight[x] = main->math.lineHeight;
        // ! 7️⃣ حساب أعلى وأسفل الجدار على الشاشة لكل عمود
        calculate_height_and_down_for_wall(main, x);
    }
}
