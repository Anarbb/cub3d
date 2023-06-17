/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:08:22 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/06/17 15:14:02 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(mlx_image_t *img, int x, int y, int color)
{
	int	i;
	int	j;
	int	size;

	size = 8;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *data)
{
	t_var	p;

	p.i = 0;
	while (data->world.map[p.i])
	{
		p.j = 0;
		while (data->world.map[p.i][p.j])
		{
			if (data->world.map[p.i][p.j] == '1')
				draw_square(data->img, p.j * 8, p.i * 8, 0x00FF00);
			else if (data->world.map[p.i][p.j] == '2')
				draw_square(data->img, p.j * 8, p.i * 8, 0x0000FF);
			else if (data->world.map[p.i][p.j] == '0')
				draw_square(data->img, p.j * 8, p.i * 8, 0x000000);
			p.j++;
		}
		p.i++;
	}
}

int	get_color(t_data *data, int x, int y)
{
	x = (int)(x / 32);
	y = (int)(y / 32);
	if (x < 0 || x >= data->world.map_width || y < 0
		|| y >= data->world.map_height)
		return (0x00000069);
	if (data->world.map[y][x] == '1')
		return (0xFF000069);
	return (0x00000069);
}

void	draw_outline(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < 300)
	{
		x = 0;
		while (x < 300)
		{
			if (x == 0 || y == 0 || x == 299 || y == 299)
				mlx_put_pixel(data->img, x, y, 0x00FF00FF);
			x++;
		}
		y++;
	}
}

void	draw_ray(t_data *data)
{
	t_line	p;
	float	ray_end_x;
	float	ray_end_y;
	float	ray_start_x;
	float	ray_start_y;

	ray_start_x = 150 + 4;
	ray_start_y = 150 + 4;
	ray_end_x = ray_start_x + cos(data->pl.pa) * 25;
	ray_end_y = ray_start_y + sin(data->pl.pa) * 25;
	p.x0 = ray_start_x;
	p.y0 = ray_start_y;
	p.x1 = ray_end_x;
	p.y1 = ray_end_y;
	mlx_draw_line(data->img, p, 0xFFFFFFFF);
}

void	minimap(t_data *data)
{
	int	x;
	int	y;
	int	x_grid;
	int	y_grid;

	x = 0;
	y = 0;
	x_grid = 0;
	y_grid = 0;
	ft_memset(data->img->pixels, 0, data->img->width * data->img->height
		* sizeof(int32_t));
	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, 300, 300);
	while (y < 300)
	{
		x = 0;
		while (x < 300)
		{
			x_grid = data->pl.px - 150 + x;
			y_grid = data->pl.py - 150 + y;
			mlx_put_pixel(data->img, x, y, get_color(data, x_grid, y_grid));
			x++;
		}
		y++;
	}
	draw_square(data->img, 150, 150, 0x00FF0069);
	draw_outline(data);
	draw_ray(data);
}
