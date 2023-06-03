/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:59:18 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/06/03 15:59:57 by aarbaoui         ###   ########.fr       */
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
