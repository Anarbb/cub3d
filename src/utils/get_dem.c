/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:48:53 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/06/16 12:06:23 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_map_dimensions(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->world.map_width = 0;
	data->world.map_height = 0;
	while (data->world.map[i])
	{
		j = 0;
		while (data->world.map[i][j])
		{
			j++;
			data->world.map_width++;
		}
		i++;
		data->world.map_height++;
	}
}
