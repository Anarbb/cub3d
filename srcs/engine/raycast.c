/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:59:18 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/06/10 20:11:32 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_raycast_variables(t_engine *p, float player_angle)
{
	p->ray_angle_step = FOV / NUM_RAYS;
	p->start_angle = player_angle - FOV / 2;
	p->ray_angle = p->start_angle;
	p->i = 0;
	p->hit = 0;
	p->player_angle = player_angle;
}

void	get_tex_dir(t_engine *p, t_data *data)
{
	if (p->stat == 1 && p->ray_x > 0)
	{
		p->img = data->NO;
		p->tex = (unsigned int *)data->tex_NO;
	}
	else if (p->stat == 1 && p->ray_x < 0)
	{
		p->img = data->SO;
		p->tex = (unsigned int *)data->tex_SO;
	}
	else if (p->stat == 2 && p->ray_y > 0)
	{
		p->img = data->WE;
		p->tex = (unsigned int *)data->tex_WE;
	}
	else if (p->stat == 2 && p->ray_y < 0)
	{
		p->img = data->EA;
		p->tex = (unsigned int *)data->tex_EA;
	}
	if (p->stat == 1)
		p->offset_x = (int)p->line_end_y % p->img->width;
	else if (p->stat == 2)
		p->offset_x = (int)p->line_end_x % p->img->width;
}

void	raycast(t_data *data, float player_x, float player_y,
		float player_angle)
{
	t_engine	p;
	int			wall_height;
	int			wall_top;
	int			wall_bottom;
	p.offset_x = 0;
	p.offset_y = 0;
	initialize_raycast_variables(&p, player_angle);
	while (p.i < NUM_RAYS)
	{
		calculate_ray_step(&p, player_x, player_y);
		correct_distortion(&p, player_x, player_y);
		p.hit = 0;
		perform_dda(&p, data);
		p.line_end_x = player_x + p.ray_x * p.perp_dist;
		p.line_end_y = player_y + p.ray_y * p.perp_dist;
		p.player_angle = player_angle;
		calculate_wall_height(&p, &wall_height, &wall_top, &wall_bottom);
		get_tex_dir(&p, data);
		for (int i = wall_top; i < wall_bottom; i++)
		{
			p.dis_from_top = i + (wall_height / 2) - (HEIGHT / 2);
			p.offset_y = p.dis_from_top * (float)p.img->height / wall_height;
			p.color = p.tex[p.img->width * p.offset_y + p.offset_x];
			mlx_put_pixel(data->world.walls, p.i, i, p.color);
		}
		p.ray_angle += p.ray_angle_step;
		if (p.ray_angle >= p.start_angle + VIEW_ANGLE)
			break ;
		p.i++;
	}
}
