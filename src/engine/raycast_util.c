/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:51:33 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/06/17 10:33:51 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	has_wall_at(t_data *data, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if (map_y < 0 || map_y >= data->world.map_height)
		return (1);
	if (map_x < 0 || map_x >= (int)ft_strlen(data->world.map[map_y]))
		return (1);
	return (data->world.map[map_y][map_x] == '1');
}

float	get_dis(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float	normalize_angle(float angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

void	init_ray_dirs(t_engine *p, float ray_angle)
{
	if (ray_angle > 0 && ray_angle < M_PI)
		p->is_ray_facing_down = 1;
	else
		p->is_ray_facing_down = 0;
	if (!p->is_ray_facing_down)
		p->is_ray_facing_up = 1;
	else
		p->is_ray_facing_up = 0;
	if (ray_angle < M_PI / 2 || ray_angle > (3 * M_PI) / 2)
		p->is_ray_facing_right = 1;
	else
		p->is_ray_facing_right = 0;
	if (!p->is_ray_facing_right)
		p->is_ray_facing_left = 1;
	else
		p->is_ray_facing_left = 0;
}

void	get_offset(t_engine *p, t_data *data)
{
	if (p->state == 1 && p->is_ray_facing_right)
	{
		p->img = data->so;
		p->tex = data->tex_so;
	}
	else if (p->state == 1 && p->is_ray_facing_left)
	{
		p->img = data->no;
		p->tex = data->tex_no;
	}
	else if (p->state == 2 && p->is_ray_facing_up)
	{
		p->img = data->we;
		p->tex = data->tex_we;
	}
	else if (p->state == 2 && p->is_ray_facing_down)
	{
		p->img = data->ea;
		p->tex = data->tex_ea;
	}
	if (p->state == 1)
		p->offset_x = (int)p->hit_y % p->img->width;
	else if (p->state == 2)
		p->offset_x = (int)p->hit_x % p->img->width;
}
