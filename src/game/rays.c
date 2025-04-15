/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:13:05 by oissa             #+#    #+#             */
/*   Updated: 2025/04/15 17:13:59 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>


void cast_rays(t_main *main)
{
    for (int x = 0; x < SCREEN_WIDTH; x++) // لكل عمود في الشاشة
    {
        // 1️⃣ حساب اتجاه الشعاع لكل عمود
        float cameraX = 2 * x / (float)SCREEN_WIDTH - 1;
        float rayDirX = main->player.dir_x + main->player.plane_x * cameraX;
        float rayDirY = main->player.dir_y + main->player.plane_y * cameraX;

        // 2️⃣ تحديد موقع اللاعب في الخريطة
        int mapX = (int)main->player.x; // كان main->game.player_x
        int mapY = (int)main->player.y; // كان main->game.player_y

        // 3️⃣ حساب خطوات الأشعة والمسافات
        float deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        float deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        float sideDistX, sideDistY;
        int stepX, stepY;

        // تحديد اتجاه الأشعة
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (main->player.x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - main->player.x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (main->player.y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - main->player.y) * deltaDistY;
        }

        // 4️⃣ تنفيذ خوارزمية DDA
        int hit = 0, side;
        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0; // الجدار في الاتجاه الأفقي
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1; // الجدار في الاتجاه العمودي
            }

            if (main->file.map[mapY][mapX] == '1') // التحقق من الاصطدام بالجدار
                hit = 1;
        }

        // 5️⃣ حساب المسافة إلى الجدار
        float perpWallDist;
        if (side == 0)
            perpWallDist = (mapX - main->player.x + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - main->player.y + (1 - stepY) / 2) / rayDirY;

        // 6️⃣ حساب ارتفاع الجدار بناءً على المسافة
        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
        main->raycasting.lineHeight[x] = lineHeight;

        // 7️⃣ حساب أعلى وأسفل الجدار على الشاشة لكل عمود
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT)
            drawEnd = SCREEN_HEIGHT - 1;

        main->raycasting.drawStart[x] = drawStart;
        main->raycasting.drawEnd[x] = drawEnd;
    }
}
