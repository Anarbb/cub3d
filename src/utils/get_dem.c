/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:48:53 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/06/19 10:38:04 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_map_dimensions(t_data *data)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	max = 0;
	data->world.map_width = 0;
	data->world.map_height = 0;
	while (data->world.map[i])
	{
		if (j > max)
			max = j;
		j = 0;
		while (data->world.map[i][j] && data->world.map[i][j] != '\n')
			j++;
		i++;
	}
	data->world.map_width = max;
	data->world.map_height = i;
}
