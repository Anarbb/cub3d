/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:51:33 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/06/13 16:54:16 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    horz_caluls(t_engine *p, t_data *data, float ray_angle)
{
    p->y_intercept_h = floor(data->pl.py / TILE_SIZE) * TILE_SIZE;
    if (p->is_ray_facing_down)
        p->y_intercept_h += TILE_SIZE;
    p->x_intercept_h = data->pl.px + (p->y_intercept_h - data->pl.py) / tan(ray_angle);
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

    if(p->is_ray_facing_up)
        p->hit_h_y -= 0.01;
}

void    get_horz(t_engine *p, t_data *data, float ray_angle)
{
    p->h = 0;
    p->v = 0;

    init_ray_dirs(p, ray_angle);
    horz_caluls(p, data, ray_angle);
    while (1)
    {
        if (hasWallAt(data, p->hit_h_x, p->hit_h_y))
        {
            p->h = 1;
            break;
        }
        else
        {
            p->hit_h_x += p->x_step_h;
            p->hit_h_y += p->y_step_h;
        }
    }
}

void    vert_claculs(t_engine *p, t_data *data, float ray_angle)
{
    p->x_intercept_v = floor(data->pl.px / TILE_SIZE) * TILE_SIZE;
    if (p->is_ray_facing_right)
        p->x_intercept_v += TILE_SIZE;
    p->y_intercept_v = data->pl.py + (p->x_intercept_v - data->pl.px) * tan(ray_angle);

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

    if(p->is_ray_facing_left)
        p->hit_v_x -= 0.01;
}

void    get_vert(t_engine *p, t_data *data, float ray_angle)
{
    vert_claculs(p, data, ray_angle);
    while (1)
    {
        if (hasWallAt(data, p->hit_v_x, p->hit_v_y))
        {
            p->v = 1;
            break;
        }
        else
        {
            p->hit_v_x += p->x_step_v;
            p->hit_v_y += p->y_step_v;
        }
    }
}

void    do_it(t_data *data, float ray_angle, t_engine *p)
{
    ray_angle = normalizeAngle(ray_angle);
    get_horz(p, data, ray_angle);
    get_vert(p, data, ray_angle);
    if (p->h)
        p->distance_h = get_distance(data->pl.px, data->pl.py, p->hit_h_x, p->hit_h_y);
    else
        p->distance_h = INT_MAX;
    if (p->v)
        p->distance_v = get_distance(data->pl.px, data->pl.py, p->hit_v_x, p->hit_v_y);
    else
        p->distance_v = INT_MAX;
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
    // mlx_draw_line(data->line, data->pl.px, data->pl.py, p->hit_x, p->hit_y, 0xFF000FF);
	// mlx_image_to_window(data->mlx, data->line, 0, 0);
}


