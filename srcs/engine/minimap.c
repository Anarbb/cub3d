/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:49:29 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/06/03 16:54:43 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(mlx_image_t *image, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_put_pixel(image, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

// get player position
// draw space around player position from the double array data->world.map
// draw player position
void	minimap(t_data *data)
{
	int		px;
	int		py;
	char	**map;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	int		x;
	int		y;
	int		minimap_size;
	int		minimap_width;
	int		minimap_height;

	px = data->pl.px / 32;
	py = data->pl.py / 32;
	map = data->world.map;
	minimap_size = 5;
	minimap_width = 40;
	minimap_height = 40;
	start_x = px - (minimap_width / 2);
	start_y = py - (minimap_height / 2);
	end_x = start_x + minimap_width;
	end_y = start_y + minimap_height;
	int i, j;
	x = 0;
	y = 0;
	for (i = start_y; i < end_y; i++)
	{
		for (j = start_x; j < end_x; j++)
		{
			if (i >= 0 && j >= 0 && i < data->world.map_height
				&& j < data->world.map_width)
			{
				if (map[i][j] == '1')
					draw_square(data->world.minim, x * minimap_size, y
							* minimap_size, minimap_size, 0xFFFFFFFF);
				else if (map[i][j] == 'N')
					draw_square(data->world.minim, x * minimap_size, y
							* minimap_size, minimap_size, 0xFFF00FFF);
				else
					draw_square(data->world.minim, x * minimap_size, y
							* minimap_size, minimap_size, 0x00000000);
			}
			x++;
		}
		x = 0;
		y++;
	}
}
