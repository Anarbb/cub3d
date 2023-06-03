/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:34:02 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/06/03 15:57:12 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_raycast_variables(t_engine *p, float player_angle)
{
	p->ray_angle_step = FOV / NUM_RAYS;
	p->start_angle = player_angle - FOV / 2;
	p->ray_angle = p->start_angle;
	p->i = 0;
	p->hit = 0;
	p->player_angle = player_angle;
}

void	calculate_ray_step(t_engine *p, float player_x, float player_y)
{
	p->ray_x = cos(p->ray_angle);
	p->ray_y = sin(p->ray_angle);
	p->delta_dist_x = fabs(1 / p->ray_x);
	p->delta_dist_y = fabs(1 / p->ray_y);
	p->map_x = (int)player_x;
	p->map_y = (int)player_y;
	p->step_x = get_step(p->ray_x);
	p->step_y = get_step(p->ray_y);
}

void	perform_dda(t_engine *p, t_data *data, float player_x, float player_y)
{
	while (!p->hit)
	{
		if (p->side_dist_x < p->side_dist_y)
		{
			p->side_dist_x += p->delta_dist_x;
			p->map_x += p->step_x;
			p->hit = data->world.map[p->map_y / 32][p->map_x / 32] == '1';
			p->perp_dist = (p->map_x - player_x + (1 - p->step_x) / 2)
				/ p->ray_x;
		}
		else
		{
			p->side_dist_y += p->delta_dist_y;
			p->map_y += p->step_y;
			p->hit = data->world.map[p->map_y / 32][p->map_x / 32] == '1';
			p->perp_dist = (p->map_y - player_y + (1 - p->step_y) / 2)
				/ p->ray_y;
		}
	}
}

void	draw_wall_segment(t_engine *p, t_data *data, int wall_top,
		int wall_bottom)
{
	int	i;

	i = wall_top;
	while (i < wall_bottom)
	{
		mlx_put_pixel(data->world.walls, p->i, i, 0xFFFFFFFF);
		i++;
	}
}

void	correct_distortion(t_engine *p, float player_x, float player_y)
{
	p->side_dist_x = 0;
	p->side_dist_y = 0;
	if (p->ray_x < 0)
		p->side_dist_x = (player_x - p->map_x) * p->delta_dist_x;
	else if (p->ray_x > 0)
		p->side_dist_x = (p->map_x + 1 - player_x) * p->delta_dist_x;
	if (p->ray_y < 0)
		p->side_dist_y = (player_y - p->map_y) * p->delta_dist_y;
	else if (p->ray_y > 0)
		p->side_dist_y = (p->map_y + 1 - player_y) * p->delta_dist_y;
}

void	calculate_wall_height(t_engine *p, int *wall_height, int *wall_top,
		int *wall_bottom)
{
	*wall_height = HEIGHT / (p->perp_dist * cos(p->ray_angle - p->player_angle))
		* WALL_SCALE;
	*wall_top = HEIGHT / 2 - *wall_height / 2;
	if (*wall_top < 0)
		*wall_top = 0;
	*wall_bottom = HEIGHT / 2 + *wall_height / 2;
	if (*wall_bottom > HEIGHT)
		*wall_bottom = HEIGHT;
}

void	raycast(t_data *data, float player_x, float player_y,
		float player_angle)
{
	t_engine	p;
	int			wall_height;
	int			wall_top;
	int			wall_bottom;

	initialize_raycast_variables(&p, player_angle);
	while (p.i < NUM_RAYS)
	{
		calculate_ray_step(&p, player_x, player_y);
		correct_distortion(&p, player_x, player_y);
		p.hit = 0;
		perform_dda(&p, data, player_x, player_y);
		p.line_end_x = player_x + p.ray_x * p.perp_dist;
		p.line_end_y = player_y + p.ray_y * p.perp_dist;
		p.player_angle = player_angle;
		calculate_wall_height(&p, &wall_height, &wall_top, &wall_bottom);
		draw_wall_segment(&p, data, wall_top, wall_bottom);
		p.ray_angle += p.ray_angle_step;
		if (p.ray_angle >= p.start_angle + VIEW_ANGLE)
			break ;
		p.i++;
	}
}
