/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:37:03 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/06/16 12:37:09 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_start_angle(t_var p, t_data *data)
{
	data->pl.px = p.j * 32 + 16;
	data->pl.py = p.i * 32 + 16;
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
	t_var	p;

	p.i = 0;
	while (data->world.map[p.i])
	{
		p.j = 0;
		while (data->world.map[p.i][p.j])
		{
			if (data->world.map[p.i][p.j] == 'W'
				|| data->world.map[p.i][p.j] == 'E'
				|| data->world.map[p.i][p.j] == 'N'
				|| data->world.map[p.i][p.j] == 'S')
				init_start_angle(p, data);
			p.j++;
		}
		p.i++;
	}
}
