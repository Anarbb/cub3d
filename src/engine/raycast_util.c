/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:51:33 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/06/13 17:15:55 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int hasWallAt(t_data *data, float x, float y)
{
    int map_x;
    int map_y;

    map_x = floor(x / TILE_SIZE);
    map_y = floor(y / TILE_SIZE);
    
    if (map_y < 0 || map_y >= data->world.map_height)
        return (1);
    if (map_x < 0 || map_x >= (int)ft_strlen(data->world.map[map_y]))
        return (1);

    return (data->world.map[map_y][map_x] == '1');
}


float get_distance(float x1, float y1, float x2, float y2)
{
    return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float    normalizeAngle(float angle)
{
    angle = remainder(angle, 2 * M_PI);
    if (angle < 0)
        angle = (2 * M_PI) + angle;
    return (angle);
}

void    init_ray_dirs(t_engine *p, float ray_angle)
{
    p->is_ray_facing_down = ray_angle > 0 && ray_angle < M_PI;
    p->is_ray_facing_up = !p->is_ray_facing_down;
    p->is_ray_facing_right = ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI;
    p->is_ray_facing_left = !p->is_ray_facing_right;
}

void    get_offset(t_engine *p, t_data *data)
{
    if (p->state == 1 && p->is_ray_facing_right)
    {
        p->img = data->SO;
        p->tex = data->tex_SO;
    }
    else if (p->state == 1 && p->is_ray_facing_left)
    {
        p->img = data->NO;
        p->tex = data->tex_NO;
    }
    else if (p->state == 2 && p->is_ray_facing_up)
    {
        p->img = data->WE;
        p->tex = data->tex_WE;
    }
    else if (p->state == 2 && p->is_ray_facing_down)
    {
        p->img = data->EA;
        p->tex = data->tex_EA;
    }
    if (p->state == 1)
        p->offset_x = (int)p->hit_y % p->img->width;
    else if (p->state == 2)
        p->offset_x = (int)p->hit_x % p->img->width;
}