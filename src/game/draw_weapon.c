/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:46:48 by oissa             #+#    #+#             */
/*   Updated: 2025/07/16 21:06:01 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	loop_give_color(t_main *m)
{
	while (m->draw_weapon.y < m->game.texture_weapon
		[m->game.weapon_animation]->height)
	{
		m->draw_weapon.offset = (m->draw_weapon.y
				* m->game.texture_weapon[m->game.weapon_animation]->width
				+ m->draw_weapon.x) * 4;
		m->draw_weapon.r = m->game.texture_weapon
		[m->game.weapon_animation]->pixels[m->draw_weapon.offset];
		m->draw_weapon.g = m->game.texture_weapon
		[m->game.weapon_animation]->pixels[m->draw_weapon.offset + 1];
		m->draw_weapon.b = m->game.texture_weapon
		[m->game.weapon_animation]->pixels[m->draw_weapon.offset + 2];
		m->draw_weapon.a = m->game.texture_weapon
		[m->game.weapon_animation]->pixels[m->draw_weapon.offset + 3];
		m->draw_weapon.color = (m->draw_weapon.r << 24)
			| (m->draw_weapon.g << 16) | (m->draw_weapon.b << 8)
			| m->draw_weapon.a;
		if (m->draw_weapon.a != 0)
			mlx_put_pixel(m->game.image,
				m->draw_weapon.pos_x + m->draw_weapon.x,
				m->draw_weapon.pos_y + m->draw_weapon.y,
				m->draw_weapon.color);
		m->draw_weapon.y++;
	}
}

void	draw_weapon(t_main *main)
{
	if (main->game.weapon_animation < 0
		|| main->game.weapon_animation >= 28
		|| !main->game.texture_weapon[main->game.weapon_animation])
		return ;
	main->draw_weapon.pos_x = SCREEN_WIDTH / 2
		- main->game.texture_weapon[main->game.weapon_animation]->width / 2
		+ 100;
	main->draw_weapon.pos_y = SCREEN_HEIGHT
		- main->game.texture_weapon[main->game.weapon_animation]->height;
	main->draw_weapon.x = 0;
	while (main->draw_weapon.x
		< main->game.texture_weapon[main->game.weapon_animation]->width)
	{
		main->draw_weapon.y = 0;
		loop_give_color(main);
		main->draw_weapon.x++;
	}
}
