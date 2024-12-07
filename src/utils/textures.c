/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:32:20 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/06/19 11:08:29 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_png(unsigned int *list, mlx_texture_t *png)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!png || !png->pixels || !list)
		return ;
	while (png->pixels[i] && j < png->width * png->height)
	{
		list[j] = get_rgba(png->pixels[i], png->pixels[i + 1], png->pixels[i
				+ 2], 255);
		if (i < (png->height * png->width * 4) - 4)
			i += 4;
		j++;
	}
}

int	check_texture(t_data *data)
{
	if (!data->no || !data->so || !data->we || !data->ea)
		return (1);
	if (data->no->height != 64 || data->no->width != 64)
		return (printf("Error\n🚨: Image error\n"), 1);
	if (data->so->height != 64 || data->so->width != 64)
		return (printf("Error\n🚨: Image error\n"), 1);
	if (data->we->height != 64 || data->we->width != 64)
		return (printf("Error\n🚨: Image error\n"), 1);
	if (data->ea->height != 64 || data->ea->width != 64)
		return (printf("Error\n🚨: Image error\n"), 1);
	return (0);
}

void	fill_textures(t_data *data)
{
	data->no = mlx_load_png(data->world.no);
	data->so = mlx_load_png(data->world.so);
	data->we = mlx_load_png(data->world.we);
	data->ea = mlx_load_png(data->world.ea);
	data->crosshair_tex = mlx_load_png(CROSSHAIR_IMG);
	data->weapon_tex = mlx_load_png(PISTOL_IMG);
	if (!data->no || !data->so || !data->we || !data->ea || check_texture(data)
		|| !data->crosshair_tex || !data->weapon_tex)
		exit(1);
	fill_png(data->tex_no, data->no);
	fill_png(data->tex_ea, data->ea);
	fill_png(data->tex_so, data->so);
	fill_png(data->tex_we, data->we);
}
