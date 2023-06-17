/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:55:38 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/06/17 17:39:03 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_string_int(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	parse_colors(char **fc, char **cc)
{
	int	count;

	count = 0;
	if (fc == NULL || cc == NULL)
		return (0);
	while (fc[count])
	{
		if (!is_string_int(ft_strtrim(fc[count], " ")))
			return (0);
		count++;
	}
	count = 0;
	while (cc[count])
	{
		if (!is_string_int(ft_strtrim(cc[count], " ")))
			return (0);
		count++;
	}
	return (1);
}

void	get_colors(t_data *data)
{
	char	**fc;
	char	**cc;

	fc = ft_split(data->world.floor_c, ',');
	cc = ft_split(data->world.ceil_c, ',');
	if (!parse_colors(fc, cc))
		ft_error("Error\nInvalid colors\n");
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
