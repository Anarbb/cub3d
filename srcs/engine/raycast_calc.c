/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:34:02 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/06/10 20:11:40 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	perform_dda(t_engine *p, t_data *data)
{
	while (!p->hit)
	{
		if (p->side_dist_x < p->side_dist_y)
		{
			p->stat = 1;
			p->side_dist_x += p->delta_dist_x;
			p->map_x += p->step_x;
			p->perp_dist = p->side_dist_x - p->delta_dist_x;
		}
		else
		{
			p->stat = 2;
			p->side_dist_y += p->delta_dist_y;
			p->map_y += p->step_y;
			p->perp_dist = p->side_dist_y - p->delta_dist_y;
		}
		if (data->world.map[p->map_y / 32][p->map_x / 32] == '1')
			p->hit = 1;
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
