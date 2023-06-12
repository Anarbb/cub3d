/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:39:18 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/06/12 21:00:08 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
int hasWallAt(t_data *data, float x, float y)
{
    if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
        return (1);
    int mapGridIndexX = x / TILE_SIZE;
    int mapGridIndexY = y / TILE_SIZE;
    printf("mapGridIndexX = %d  ", mapGridIndexX);
    printf("mapGridIndexY = %d\n", mapGridIndexY);
    
    return (data->world.map[mapGridIndexY][mapGridIndexX] == '1');
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
void    raycasting(t_data *data)
{
    float ray_angle = data->pl.pa - (FOV / 2);
    ray_angle = normalizeAngle(ray_angle);
    int is_ray_facing_down;
    int is_ray_facing_up;
    int is_ray_facing_right;
    int is_ray_facing_left;
    float distance;
    int h;
    int v;

    float hit_x;
    float hit_y;

    float x_step_h;
    float y_step_h;

    float x_intercept_h;
    float y_intercept_h;


    float hit_h_x;
    float hit_h_y;

    h = 0;
    v = 0;
    int i = 0;
    mlx_delete_image(data->mlx, data->line);
	data->line = mlx_new_image(data->mlx, WIDTH, HEIGHT);

    is_ray_facing_down = ray_angle > 0 && ray_angle < M_PI;
    is_ray_facing_up = !is_ray_facing_down;
    is_ray_facing_right = ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI;
    is_ray_facing_left = !is_ray_facing_right;
    //--------------------------------------- horizontal ---------------------------------------
    //find the y intercept of the first horizontal line
    y_intercept_h = floor(data->pl.py / TILE_SIZE) * TILE_SIZE;
    if (is_ray_facing_down)
        y_intercept_h += TILE_SIZE;
    // find the x intercept of the first horizontal line
    x_intercept_h = data->pl.px + (y_intercept_h - data->pl.py) / tan(ray_angle);
    
    y_step_h = TILE_SIZE;
    y_step_h *= is_ray_facing_up ? -1 : 1;

    x_step_h = TILE_SIZE / tan(ray_angle);
    x_step_h *= (is_ray_facing_left && x_step_h > 0) ? -1 : 1;
    x_step_h *= (is_ray_facing_right && x_step_h < 0) ? -1 : 1;

    hit_h_x = x_intercept_h;
    hit_h_y = y_intercept_h;

    if(is_ray_facing_up)
        hit_h_y--;
    while (hit_h_x >= 0 && hit_h_x <= WIDTH && hit_h_y >= 0 && hit_h_y <= HEIGHT)
    {
        if (hasWallAt(data, hit_h_x, hit_h_y))
        {
            h = 1;
            break;
        }
        else
        {
            hit_h_x += x_step_h;
            hit_h_y += y_step_h;
        }
    }
    //--------------------------------------- vertical ---------------------------------------

    float x_step_v;
    float y_step_v;

    float x_intercept_v;
    float y_intercept_v;

    float hit_v_x;
    float hit_v_y;
    
    // find the y intercept of the first horizontal line
    x_intercept_v = floor(data->pl.px / TILE_SIZE) * TILE_SIZE;
    if (is_ray_facing_right)
        x_intercept_v += TILE_SIZE;
    // find the x intercept of the first horizontal line
    y_intercept_v = data->pl.py + (x_intercept_v - data->pl.px) * tan(ray_angle);
    
    x_step_v = TILE_SIZE;
    x_step_v *= is_ray_facing_left ? -1 : 1;

    y_step_v = TILE_SIZE * tan(ray_angle);
    y_step_v *= (is_ray_facing_up && y_step_v > 0) ? -1 : 1;
    y_step_v *= (is_ray_facing_down && y_step_v < 0) ? -1 : 1;

    hit_v_x = x_intercept_v;
    hit_v_y = y_intercept_v;

    if(is_ray_facing_left)
        hit_v_x--;
    while (hit_v_x >= 0 && hit_v_x <= WIDTH && hit_v_y >= 0 && hit_v_y <= HEIGHT)
    {
        if (hasWallAt(data, hit_v_x, hit_v_y))
        {
            v = 1;
            break;
        }
        else
        {
            hit_v_x += x_step_v;
            hit_v_y += y_step_v;
        }
    }
    float distance_h = h ? get_distance(data->pl.px, data->pl.py, hit_h_x, hit_h_y) : INT_MAX;
    float distance_v = v ? get_distance(data->pl.px, data->pl.py, hit_v_x, hit_v_y) : INT_MAX;
    hit_x = distance_h < distance_v ? hit_h_x : hit_v_x;
    hit_y = distance_h < distance_v ? hit_h_y : hit_v_y;
    distance = distance_h < distance_v ? distance_h : distance_v;

    mlx_draw_line(data->line, data->pl.px, data->pl.py, hit_x, hit_y, 0xFF000FF);
	mlx_image_to_window(data->mlx, data->line, 0, 0);
}
