/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:36:23 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/06/17 18:37:17 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_map(t_data *data)
{
	ft_memset(data->img->pixels, 0, data->img->width * data->img->height
		* sizeof(int32_t));
	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, 300, 300);
}
