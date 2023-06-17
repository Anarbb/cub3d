/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:16:54 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/06/17 18:47:17 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	imgs_init(t_data *data)
{
	data->world.skybox = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->wall = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img = mlx_new_image(data->mlx, 300, 300);
	data->crosshair = mlx_texture_to_image(data->mlx, data->crosshair_tex);
	data->weapon = mlx_texture_to_image(data->mlx, data->weapon_tex);
	mlx_resize_image(data->crosshair, 16, 16);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data || ac != 2)
		return (1);
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!data->mlx)
		return (1);
	init_parse(data, av[1]);
	calculate_map_dimensions(data);
	fill_textures(data);
	imgs_init(data);
	skybox(data);
	init_player(data);
	mlx_image_to_window(data->mlx, data->world.skybox, 0, 0);
	mlx_image_to_window(data->mlx, data->wall, 0, 0);
	mlx_image_to_window(data->mlx, data->crosshair,
		WIDTH / 2 - 16 / 2, HEIGHT / 2 - 16 / 2);
	mlx_image_to_window(data->mlx, data->weapon,
		(WIDTH / 2) - (data->weapon->width / 2),
		(HEIGHT) - data->weapon->height);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	return (0);
}
