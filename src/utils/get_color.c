/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:33:35 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/06/18 11:02:53 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(t_data *data, int x, int y)
{
	x = (int)(x / 64);
	y = (int)(y / 64);
	if (x < 0 || x >= data->world.map_width || y < 0
		|| y >= data->world.map_height)
		return (0x00000069);
	if (data->world.map[y][x] == '1')
		return (0xFF000069);
	return (0x00000069);
}
