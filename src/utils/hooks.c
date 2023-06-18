/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:34:05 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/06/18 11:00:08 by ybenlafk         ###   ########.fr       */
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

void	init_cells(t_var *p)
{
	p->cell_x = (int)(p->new_px / 64);
	p->cell_y = (int)(p->new_py / 64);
	p->left_cell_x = (int)((p->new_px - PLAYER_SIZE / 2) / 64);
	p->right_cell_x = (int)((p->new_px + PLAYER_SIZE / 2) / 64);
}

void	check_collision(t_data *data, t_var *p)
{
	init_cells(p);
	if (data->world.map[p->cell_y][p->cell_x] == '1')
	{
		p->new_px = data->pl.px;
		p->new_py = data->pl.py;
		return ;
	}
	if (p->left_cell_x >= 0
		&& data->world.map[p->cell_y][p->left_cell_x] == '1')
	{
		p->new_px = data->pl.px;
		p->new_py = data->pl.py;
		return ;
	}
	if (p->right_cell_x < WIDTH / 64
		&& data->world.map[p->cell_y][p->right_cell_x] == '1')
	{
		p->new_px = data->pl.px;
		p->new_py = data->pl.py;
		return ;
	}
	data->pl.px = p->new_px;
	data->pl.py = p->new_py;
}

void	hook_norm(t_data *data, t_var *p)
{
	if (!mlx_is_key_down(data->mlx, MLX_KEY_K))
		change_angle(data);
	else
		mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		p->new_px += data->pl.pdy;
		p->new_py -= data->pl.pdx;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		p->new_px -= data->pl.pdy;
		p->new_py += data->pl.pdx;
	}
}

void	ft_hook(void *param)
{
	t_data	*data;
	t_var	p;

	data = (t_data *)param;
	p.new_px = data->pl.px;
	p.new_py = data->pl.py;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(0);
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP)
		|| mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		p.new_px += data->pl.pdx;
		p.new_py += data->pl.pdy;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		p.new_px -= data->pl.pdx;
		p.new_py -= data->pl.pdy;
	}
	hook_norm(data, &p);
	check_collision(data, &p);
	minimap(data);
	raycasting(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}
