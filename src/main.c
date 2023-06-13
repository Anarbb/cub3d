/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:16:54 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/06/13 13:21:13 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void mlx_draw_line(mlx_image_t *image, int x1, int y1, int x2, int y2, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	sx = x1 < x2 ? 1 : -1;
	sy = y1 < y2 ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;
	if (x1 == x2 && y1 == y2)
		mlx_put_pixel(image, x1, y1, color);
	// if any is negative, dont draw
	if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0)
		return ;
	while (1)
	{
		mlx_put_pixel(image, x1, y1, color);
		if (x1 == x2 && y1 == y2)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void	draw_mini_square(t_var *p, t_data *data)
{
	p->l = 0;
	while (p->l < 10)
	{
		p->k = 0;
		while (p->k < 10)
		{
			mlx_put_pixel(data->pl.img, p->j + p->k, p->i + p->l, 0xFFF00FF);
			p->k++;
		}
		p->l++;
	}
}

void	draw_square(t_var *p, t_data *data)
{
	p->x = p->j * 32;
	p->y = p->i * 32;
	p->l = 0;
	while (p->l < 31)
	{
		p->k = 0;
		while (p->k < 31)
		{
			mlx_put_pixel(data->img, p->x + p->k, p->y + p->l, 0xFFFFFF);
			p->k++;
		}
		p->l++;
	}
}

void	draw_player(t_data *data)
{
	t_var p;
	static int i;
	p.i = 0;
	while (data->world.map[p.i])
	{
		p.j = 0;
		while (data->world.map[p.i][p.j])
		{
			if (data->world.map[p.i][p.j] == 'W' || data->world.map[p.i][p.j] == 'E'
				|| data->world.map[p.i][p.j] == 'N' || data->world.map[p.i][p.j] == 'S')
				{
					draw_mini_square(&p, data);
					if (i++ == 0)
					{
						data->pl.px = p.j * 32;
						data->pl.py = p.i * 32;
						data->pl.pdx = cos(data->pl.pa) * 5;
						data->pl.pdy = sin(data->pl.pa) * 5;
					}
				}
			p.j++;
		}
		p.i++;
	}
}
void	draw_map(t_data *data)
{
	t_var p;

	p.i = 0;
	while (data->world.map[p.i])
	{
		p.j = 0;
		while (data->world.map[p.i][p.j])
		{
			if (data->world.map[p.i][p.j] == '1')
				draw_square(&p, data);
			p.j++;
		}
		p.i++;
	}
}

void	check_collision(t_data *data, t_var *p)
{
	if (data->world.map[(int)p->new_py / 32][(int)p->new_px / 32] == '1')
	{
		p->new_px = data->pl.px;
		p->new_py = data->pl.py;
	}
	else
	{
		data->pl.px = p->new_px;
		data->pl.py = p->new_py;
	}
}

void	ft_hook(void	*param)
{
	t_data *data;
	t_var p;
	data = (t_data *)param;
	p.new_px = data->pl.px;
	p.new_py = data->pl.py;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(0);
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP) || mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		p.new_px += data->pl.pdx;
		p.new_py += data->pl.pdy;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN) || mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		p.new_px -= data->pl.pdx;
		p.new_py -= data->pl.pdy;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->pl.pa += 0.1;
		data->pl.pdx = cos(data->pl.pa) * 5;
		data->pl.pdy = sin(data->pl.pa) * 5;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->pl.pa -= 0.1;
		data->pl.pdx = cos(data->pl.pa) * 5;
		data->pl.pdy = sin(data->pl.pa) * 5;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		p.new_px += data->pl.pdy;
		p.new_py -= data->pl.pdx;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		p.new_px -= data->pl.pdy;
		p.new_py += data->pl.pdx;
	}
	check_collision(data, &p);
	raycasting(data);
}



int	main(int ac, char **av)
{
	t_data data;

	if (ac != 2)
		return (0);
	data.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	init_parse(&data, av[1]);
	calculate_map_dimensions(&data);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.line = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.wall = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.pl.img = mlx_new_image(data.mlx, 32, 32);
	// draw_map(&data);
	draw_player(&data);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	mlx_image_to_window(data.mlx, data.line, 0, 0);
	// mlx_image_to_window(data.mlx, data.pl.img, data.pl.px, data.pl.py);
	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}