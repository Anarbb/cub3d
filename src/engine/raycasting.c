/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:39:18 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/06/13 13:19:54 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int hasWallAt(t_data *data, float x, float y)
{
    int map_x;
    int map_y;

    map_x = floor(x / TILE_SIZE);
    map_y = floor(y / TILE_SIZE);
    if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
        return (1);
    
    if (map_y < 0 || map_y >= data->world.map_height)
        return (1);
    if (map_x < 0 || map_x >= ft_strlen(data->world.map[map_y]))
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
        p->hit_x = p->hit_v_x;
        p->hit_y = p->hit_v_y;
        p->distance = p->distance_v;
    }
    else
    {
        p->hit_x = p->hit_h_x;
        p->hit_y = p->hit_h_y;
        p->distance = p->distance_h;
    }
    // mlx_draw_line(data->line, data->pl.px, data->pl.py, p->hit_x, p->hit_y, 0xFF000FF);
	// mlx_image_to_window(data->mlx, data->line, 0, 0);
}

void    raycasting(t_data *data)
{   
    t_engine p;
    float ray_angle = data->pl.pa - (FOV / 2);
    int i = 0;
    mlx_delete_image(data->mlx, data->wall);
    // mlx_delete_image(data->mlx, data->line);
	// data->line = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->wall = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    while (i < NUM_RAYS)
    {
        do_it(data, ray_angle, &p);
        p.angle = (FOV / 2) - i * (FOV / NUM_RAYS);
        p.dist = p.distance * cos(p.angle);
        p.wall_hight = TILE_SIZE * WIDTH / p.dist;
        p.wall_top = (HEIGHT / 2) - (p.wall_hight / 2);
        p.wall_top = p.wall_top < 0 ? 0 : p.wall_top;
        p.wall_bottom = (HEIGHT / 2) + (p.wall_hight / 2);
        p.wall_bottom = p.wall_bottom > HEIGHT ? HEIGHT : p.wall_bottom;
        for (int j = p.wall_top; j < p.wall_bottom; j++)
            mlx_put_pixel(data->wall, i, j, 0xFFFFFFFF);
        mlx_image_to_window(data->mlx, data->wall, 0, 0);
        ray_angle += FOV / NUM_RAYS;
        i++;
    }
    
}
