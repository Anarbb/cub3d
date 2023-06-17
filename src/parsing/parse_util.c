/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:02:20 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/06/17 12:42:28 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *str)
{
	printf("%s", str);
	exit(0);
}

int	is_empty(char c)
{
	if (c == '\n' || c == ' ' || c == 0)
		return (1);
	return (0);
}

int	is_valid(t_var *p, char **map)
{
	if (!map[p->i + 1] || p->j == 0 || map[p->i + 1][0] == '\n')
		return (1);
	else if (!map[p->i - 1] || p->i == 0 || map[p->i - 1][0] == '\n')
		return (1);
	else if (is_empty(map[p->i][p->j + 1]))
		return (1);
	else if (is_empty(map[p->i][p->j - 1]))
		return (1);
	else if (is_empty(map[p->i + 1][p->j]))
		return (1);
	else if (is_empty(map[p->i - 1][p->j]))
		return (1);
	return (0);
}

int	is_surrounded(char **map)
{
	t_var	p;

	p.i = 0;
	while (map[p.i])
	{
		p.j = 0;
		while (map[p.i][p.j] && map[p.i][p.j] != '\n')
		{
			if (map[p.i][p.j] == '0' || map[p.i][p.j] == 'W'
				|| map[p.i][p.j] == 'E' || map[p.i][p.j] == 'S'
				|| map[p.i][p.j] == 'N')
				if (is_valid(&p, map))
					return (1);
			p.j++;
		}
		p.i++;
	}
	return (0);
}

void	parse_params_2(t_data *data, char *line, int *is)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		data->world.floor_c = ft_strtrim(line + 2, " \t\n");
		if (*data->world.floor_c == '\0')
			ft_error("Error\n");
		(*is)++;
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		data->world.ceil_c = ft_strtrim(line + 2, " \t\n");
		if (*data->world.ceil_c == '\0')
			ft_error("Error\n");
		(*is)++;
	}
}
