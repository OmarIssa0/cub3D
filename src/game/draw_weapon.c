/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:46:48 by oissa             #+#    #+#             */
/*   Updated: 2025/07/19 03:03:44 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_weapon_pixel(t_main *m, uint32_t tex_x, uint32_t tex_y)
{
	m->draw_weapon.offset = (tex_y
			* m->game.texture_weapon[m->game.weapon_animation]->width
			+ tex_x) * 4;
	m->draw_weapon.r = m->game.texture_weapon[m->game.weapon_animation]
		->pixels[m->draw_weapon.offset];
	m->draw_weapon.g = m->game.texture_weapon[m->game.weapon_animation]
		->pixels[m->draw_weapon.offset + 1];
	m->draw_weapon.b = m->game.texture_weapon[m->game.weapon_animation]
		->pixels[m->draw_weapon.offset + 2];
	m->draw_weapon.a = m->game.texture_weapon[m->game.weapon_animation]
		->pixels[m->draw_weapon.offset + 3];
	m->draw_weapon.color = (m->draw_weapon.r << 24)
		| (m->draw_weapon.g << 16) | (m->draw_weapon.b << 8)
		| m->draw_weapon.a;
	if (m->draw_weapon.a != 0)
		mlx_put_pixel(m->game.image, m->draw_weapon.pos_x
			+ m->draw_weapon.x, m->draw_weapon.pos_y + m->draw_weapon.y,
			m->draw_weapon.color);
}

static void	loop_give_color(t_main *m)
{
	uint32_t	tex_x;
	uint32_t	tex_y;

	while (m->draw_weapon.y < m->draw_weapon.weapon_height)
	{
		tex_x = (m->draw_weapon.x
				* m->game.texture_weapon[m->game.weapon_animation]->width)
			/ m->draw_weapon.weapon_width;
		tex_y = (m->draw_weapon.y
				* m->game.texture_weapon[m->game.weapon_animation]->height)
			/ m->draw_weapon.weapon_height;
		draw_weapon_pixel(m, tex_x, tex_y);
		m->draw_weapon.y++;
	}
}

void	draw_weapon(t_main *main)
{
	if (main->game.weapon_animation < 0 || main->game.weapon_animation >= 28
		|| !main->game.texture_weapon[main->game.weapon_animation])
		return ;
	main->draw_weapon.weapon_width = SCREEN_WIDTH * 0.4;
	main->draw_weapon.weapon_height = SCREEN_HEIGHT * 0.3;
	main->draw_weapon.pos_x = (SCREEN_WIDTH - main->draw_weapon.weapon_width)
		/ 2;
	main->draw_weapon.pos_y = SCREEN_HEIGHT - main->draw_weapon.weapon_height;
	main->draw_weapon.x = 0;
	while (main->draw_weapon.x < main->draw_weapon.weapon_width)
	{
		main->draw_weapon.y = 0;
		loop_give_color(main);
		main->draw_weapon.x++;
	}
}
