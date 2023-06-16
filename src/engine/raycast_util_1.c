/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:51:33 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/06/16 11:58:28 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_intercept(t_data *data, float p, float ray_angle, int state)
{
	if (state == 1)
		return (data->pl.py + (p - data->pl.px) * tan(ray_angle));
	else
		return (data->pl.px + (p - data->pl.py) / tan(ray_angle));
}

void	horz_caluls(t_engine *p, t_data *data, float ray_angle)
{
	p->y_intercept_h = floor(data->pl.py / TILE_SIZE) * TILE_SIZE;
	if (p->is_ray_facing_down)
		p->y_intercept_h += TILE_SIZE;
	p->x_intercept_h = get_intercept(data, p->y_intercept_h, ray_angle, 0);
	p->y_step_h = TILE_SIZE;
	if (p->is_ray_facing_up)
		p->y_step_h *= -1;
	p->x_step_h = TILE_SIZE / tan(ray_angle);
	if (p->is_ray_facing_left && p->x_step_h > 0)
		p->x_step_h *= -1;
	if (p->is_ray_facing_right && p->x_step_h < 0)
		p->x_step_h *= -1;
	p->hit_h_x = p->x_intercept_h;
	p->hit_h_y = p->y_intercept_h;
	if (p->is_ray_facing_up)
		p->hit_h_y -= 0.01;
}

void	get_horz(t_engine *p, t_data *data, float ray_angle)
{
	p->h = 0;
	p->v = 0;
	init_ray_dirs(p, ray_angle);
	horz_caluls(p, data, ray_angle);
	while (1)
	{
		if (has_wall_at(data, p->hit_h_x, p->hit_h_y))
		{
			p->h = 1;
			if (p->is_ray_facing_up)
				p->hit_h_y += 0.01;
			break ;
		}
		else
		{
			p->hit_h_x += p->x_step_h;
			p->hit_h_y += p->y_step_h;
		}
	}
}

void	vert_claculs(t_engine *p, t_data *data, float ray_angle)
{
	p->x_intercept_v = floor(data->pl.px / TILE_SIZE) * TILE_SIZE;
	if (p->is_ray_facing_right)
		p->x_intercept_v += TILE_SIZE;
	p->y_intercept_v = get_intercept(data, p->x_intercept_v, ray_angle, 1);
	p->x_step_v = TILE_SIZE;
	if (p->is_ray_facing_left)
		p->x_step_v *= -1;
	p->y_step_v = TILE_SIZE * tan(ray_angle);
	if (p->is_ray_facing_up && p->y_step_v > 0)
		p->y_step_v *= -1;
	if (p->is_ray_facing_down && p->y_step_v < 0)
		p->y_step_v *= -1;
	p->hit_v_x = p->x_intercept_v;
	p->hit_v_y = p->y_intercept_v;
	if (p->is_ray_facing_left)
		p->hit_v_x -= 0.01;
}

void	get_vert(t_engine *p, t_data *data, float ray_angle)
{
	vert_claculs(p, data, ray_angle);
	while (1)
	{
		if (has_wall_at(data, p->hit_v_x, p->hit_v_y))
		{
			p->v = 1;
			if (p->is_ray_facing_left)
				p->hit_v_x += 0.01;
			break ;
		}
		else
		{
			p->hit_v_x += p->x_step_v;
			p->hit_v_y += p->y_step_v;
		}
	}
}
