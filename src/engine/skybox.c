/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:55:38 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/06/17 10:22:57 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_colors(t_data *data)
{
	char	**fc;
	char	**cc;

	fc = ft_split(data->world.floor_c, ',');
	cc = ft_split(data->world.ceil_c, ',');
	data->world.floor = get_rgba(ft_atoi(fc[0]), ft_atoi(fc[1]), ft_atoi(fc[2]),
			255);
	data->world.ceil = get_rgba(ft_atoi(cc[0]), ft_atoi(cc[1]), ft_atoi(cc[2]),
			255);
	free_all(fc);
	free_all(cc);
}

void	skybox(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	get_colors(data);
	while (++i < WIDTH)
	{
		j = -1;
		while (++j < HEIGHT / 2)
			mlx_put_pixel(data->world.skybox, i, j, data->world.ceil);
	}
	i = -1;
	while (++i < WIDTH)
	{
		j = HEIGHT / 2 - 1;
		while (++j < HEIGHT)
			mlx_put_pixel(data->world.skybox, i, j, data->world.floor);
	}
}
