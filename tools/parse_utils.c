/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 02:20:22 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/19 16:34:28 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_map(char *line)
{
	return (*line == '1' || *line == '0' || *line == '\t' || *line == ' ');
}