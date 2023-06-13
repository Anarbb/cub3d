/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:39:18 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/06/13 16:54:59 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    raycasting(t_data *data)
{   
    t_engine p;

    p.state = 0;
    float ray_angle = data->pl.pa - (FOV / 2);
    int i = 0;
    // mlx_delete_image(data->mlx, data->line);
	// data->line = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    mlx_delete_image(data->mlx, data->wall);
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
        get_offset(&p, data);
        for (int j = p.wall_top; j < p.wall_bottom; j++)
        {
            p.dist_from_top = j + (p.wall_hight / 2) - (HEIGHT / 2);
            p.offset_y = p.dist_from_top * ((float)p.img->height / p.wall_hight);
            p.color = p.tex[p.img->width * p.offset_y + p.offset_x];
            mlx_put_pixel(data->wall, i, j, p.color);
        }
        mlx_image_to_window(data->mlx, data->wall, 0, 0);
        ray_angle += FOV / NUM_RAYS;
        i++;
    }
    
}
