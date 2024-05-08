/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_check_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadamik <aadamik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:03:18 by aadamik           #+#    #+#             */
/*   Updated: 2024/05/08 16:59:43 by aadamik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_wrong_chars(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i] && len_maps_line(data->map[i]) != 0)
	{
		if (ft_strlen_char(data->map[i]) != len_maps_line(data->map[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_requirements(t_data *data)
{
	int	exits;
	int	players;
	int	y;
	int	x;

	y = 0;
	exits = 0;
	players = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'P')
				players++;
			if (data->map[y][x] == 'E')
				exits++;
			x++;
		}
		y++;
	}
	if (players > 1 || exits > 1)
		return (ft_printf("Error\nMap has more than 1 player and 1 exit"), 0);
	return (1);
}

int	check_for_ones(t_data *data, int y, int x)
{
	int	j;
	int	i;

	j = 0;
	while (data->map[0][j] == '1')
		j++;
	i = 0;
	while (data->map[data->map_height - 1][i] == '1')
		i++;
	if (j != x || i != x)
		return (printf("HALO1\n"), 0);
	j = 0;
	while (data->map[j] && data->map[j][0] == '1')
		j++;
	i = 0;
	while (data->map[i] && data->map[i][x - 1] == '1')
		i++;
	if (j != y || i != y)
		return (printf("HALO2\n"), 0);
	return (1);
}

int	check_surrounded(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map[y] && len_maps_line(data->map[y]) >= 3)
	{
		x = 0;
		while (data->map[y][x] && data->map[y][x] != '\n')
			x++;
		y++;
	}
	if (!check_for_ones(data, data->map_height, data->map_len))
		return (ft_printf("Error\nMap is not surrounded by the walls\n"), 0);
	return (1);
}

void	get_cpy_data(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	data->cpy_coll_count = 0;
	data->cpy_exit_count = 0;
	while (data->map_copy[y])
	{
		x = 0;
		while (data->map_copy[y][x])
		{
			if (data->map_copy[y][x] == 'C')
				data->cpy_coll_count++;
			if (data->map_copy[y][x] == 'E')
				data->cpy_exit_count++;
			if (data->map_copy[y][x] == 'P')
			{
				data->px_cpy = x;
				data->py_cpy = y;
			}
			x++;
		}
		y++;
	}
}
