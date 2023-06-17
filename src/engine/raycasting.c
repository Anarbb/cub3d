/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:39:18 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/06/17 15:34:00 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_wall_hight(t_engine *p, int i)
{
	p->angle = (FOV / 2) - i * (FOV / NUM_RAYS);
	p->dist = p->distance * cos(p->angle);
	p->wall_hight = TILE_SIZE * WIDTH / p->dist;
	p->wall_top = (HEIGHT / 2) - (p->wall_hight / 2);
	if (p->wall_top < 0)
		p->wall_top = 0;
	p->wall_bottom = (HEIGHT / 2) + (p->wall_hight / 2);
	if (p->wall_bottom > HEIGHT)
		p->wall_bottom = HEIGHT;
}

void	ray_init(t_engine *p, t_data *data, int *i, float *ray_angle)
{
	p->state = 0;
	*ray_angle = data->pl.pa - (FOV / 2);
	ft_memset(data->wall->pixels, 0,
		data->wall->width * data->wall->height * sizeof(int32_t));
	*i = 0;
}

void	shorter(t_engine *p)
{
	if (p->distance_v < p->distance_h)
	{
		p->state = 1;
		p->hit_x = p->hit_v_x;
		p->hit_y = p->hit_v_y;
		p->distance = p->distance_v;
	}
	else
	{
		p->state = 2;
		p->hit_x = p->hit_h_x;
		p->hit_y = p->hit_h_y;
		p->distance = p->distance_h;
	}
}

void	do_it(t_data *data, float ray_angle, t_engine *p)
{
	ray_angle = normalize_angle(ray_angle);
	get_horz(p, data, ray_angle);
	get_vert(p, data, ray_angle);
	if (p->h)
		p->distance_h = get_dis(data->pl.px, data->pl.py,
				p->hit_h_x, p->hit_h_y);
	else
		p->distance_h = INT_MAX;
	if (p->v)
		p->distance_v = get_dis(data->pl.px, data->pl.py,
				p->hit_v_x, p->hit_v_y);
	else
		p->distance_v = INT_MAX;
	shorter(p);
}

void	raycasting(t_data *data)
{
	t_engine	p;
	float		ray_angle;
	int			i;
	int			j;

	ray_init(&p, data, &i, &ray_angle);
	while (i < NUM_RAYS)
	{
		do_it(data, ray_angle, &p);
		get_wall_hight(&p, i);
		get_offset(&p, data);
		j = p.wall_top;
		while (j < p.wall_bottom)
		{
			p.dist_p = j - ((HEIGHT / 2) - (p.wall_hight / 2));
			p.offset_y = p.dist_p * ((float)p.img->height / p.wall_hight);
			p.color = p.tex[p.img->width * p.offset_y + p.offset_x];
			mlx_put_pixel(data->wall, i, j, p.color);
			j++;
		}
		ray_angle += FOV / NUM_RAYS;
		i++;
	}
	data->ray = &p;
}
