/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:16:54 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/06/14 14:57:37 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	change_angle(t_data *data)
{
	int	mx;
	int	my;

	mx = 0;
	my = 0;
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_get_mouse_pos(data->mlx, &mx, &my);
	data->pl.pa += (mx - 500) / 500.0 * SENSE;
	data->pl.pdx = cos(data->pl.pa) * 5;
	data->pl.pdy = sin(data->pl.pa) * 5;
	mlx_set_mouse_pos(data->mlx, 500, 500);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->pl.pa -= 0.04;
		data->pl.pdx = cos(data->pl.pa) * 5;
		data->pl.pdy = sin(data->pl.pa) * 5;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->pl.pa += 0.04;
		data->pl.pdx = cos(data->pl.pa) * 5;
		data->pl.pdy = sin(data->pl.pa) * 5;
	}
}


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

void init_start_angle(t_var p, t_data *data)
{
	data->pl.px = p.j * 32;
	data->pl.py = p.i * 32;
	if (data->world.map[p.i][p.j] == 'W')
		data->pl.pa = 3 * M_PI / 2;
	else if (data->world.map[p.i][p.j] == 'E')
		data->pl.pa = M_PI / 2;
	else if (data->world.map[p.i][p.j] == 'N')
		data->pl.pa = M_PI;
	else if (data->world.map[p.i][p.j] == 'S')
		data->pl.pa = 0;
	data->pl.pdx = cos(data->pl.pa) * 5;
	data->pl.pdy = sin(data->pl.pa) * 5;
}

void	init_player(t_data *data)
{
	t_var p;

	p.i = 0;
	while (data->world.map[p.i])
	{
		p.j = 0;
		while (data->world.map[p.i][p.j])
		{
			if (data->world.map[p.i][p.j] == 'W' || data->world.map[p.i][p.j] == 'E'
				|| data->world.map[p.i][p.j] == 'N' || data->world.map[p.i][p.j] == 'S')
				init_start_angle(p, data);
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

void check_collision(t_data *data, t_var *p)
{
    p->cell_x = (int)(p->new_px / 32);
    p->cell_y = (int)(p->new_py / 32);
    p->left_cell_x = (int)((p->new_px - PLAYER_SIZE / 2) / 32);
    p->right_cell_x = (int)((p->new_px + PLAYER_SIZE / 2) / 32);
    if (data->world.map[p->cell_y][p->cell_x] == '1')
    {
        p->new_px = data->pl.px;
        p->new_py = data->pl.py;
        return;
    }
    if (p->left_cell_x >= 0 && data->world.map[p->cell_y][p->left_cell_x] == '1')
    {
        p->new_px = data->pl.px;
        p->new_py = data->pl.py;
        return;
    }
    if (p->right_cell_x < WIDTH / 32 && data->world.map[p->cell_y][p->right_cell_x] == '1')
    {
        p->new_px = data->pl.px;
        p->new_py = data->pl.py;
        return;
    }
    data->pl.px = p->new_px;
    data->pl.py = p->new_py;
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
		p.new_px += data->pl.pdx / 2;
		p.new_py += data->pl.pdy / 2;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN) || mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		p.new_px -= data->pl.pdx / 2;
		p.new_py -= data->pl.pdy / 2;
	}
	if (!mlx_is_key_down(data->mlx, MLX_KEY_K))
		change_angle(data);
	else
		mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
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

void	fill_png(unsigned int *list, mlx_texture_t *png)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (png->pixels[i] && j < png->width * png->height)
	{
		list[j] = get_rgba(png->pixels[i], png->pixels[i + 1], png->pixels[i
				+ 2], 255);
		i += 4;
		j++;
	}
}

int	check_texture(t_data *data)
{
	if (!data->NO || !data->SO || !data->WE || !data->EA)
		return (1);
	if (data->NO->height != 64 || data->NO->width != 64)
		return (printf("Error\n🚨: Image error\n"), 1);
	if (data->SO->height != 64 || data->SO->width != 64)
		return (printf("Error\n🚨: Image error\n"), 1);
	if (data->WE->height != 64 || data->WE->width != 64)
		return (printf("Error\n🚨: Image error\n"), 1);
	if (data->EA->height != 64 || data->EA->width != 64)
		return (printf("Error\n🚨: Image error\n"), 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data *data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (0);
	if (ac != 2)
		return (0);
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	init_parse(data, av[1]);
	calculate_map_dimensions(data);
	data->NO = mlx_load_png(data->world.no);
	data->SO = mlx_load_png(data->world.so);
	data->WE = mlx_load_png(data->world.we);
	data->EA = mlx_load_png(data->world.ea);
	if (!data->NO || !data->SO || !data->WE || !data->EA || check_texture(data))
		exit(1);
	data->world.skybox = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	skybox(data);
	fill_png(data->tex_NO, data->NO);
	fill_png(data->tex_EA, data->EA);
	fill_png(data->tex_SO, data->SO);
	fill_png(data->tex_WE, data->WE);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->line = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->wall = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	// draw_map(data);
	init_player(data);
	mlx_image_to_window(data->mlx, data->world.skybox, 0, 0);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_image_to_window(data->mlx, data->line, 0, 0);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	return (0);
}