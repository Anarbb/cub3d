/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:33:35 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/06/17 18:33:43 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(t_data *data, int x, int y)
{
	x = (int)(x / 32);
	y = (int)(y / 32);
	if (x < 0 || x >= data->world.map_width || y < 0
		|| y >= data->world.map_height)
		return (0x00000069);
	if (data->world.map[y][x] == '1')
		return (0xFF000069);
	return (0x00000069);
}
