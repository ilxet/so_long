/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c1_check_map_flood_fill.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadamik <aadamik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:07:41 by aadamik           #+#    #+#             */
/*   Updated: 2024/05/08 17:18:45 by aadamik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fill(t_data *data, int y, int x)
{
	if (y < 0 || y >= data->map_height || x < 0 || x >= data->map_len
		|| data->map_copy[y][x] == 'E' || data->map_copy[y][x] == '1')
	{
		if (data->map_copy[y][x] != '\0')
			data->map_copy[y][x] = '1';
		return ;
	}
	data->map_copy[y][x] = '1';
	fill(data, y, x - 1);
	fill(data, y, x + 1);
	fill(data, y - 1, x);
	fill(data, y + 1, x);
}

int	check_take_all_coll_exit(t_data *data)
{
	int	i;

	i = 0;
	data->map_copy = ft_calloc(data->map_height + 1, sizeof(char *));
	if (!data->map_copy)
		return (ft_printf("Error\nFailed to allocate memory\n"), 0);
	while (data->map[i])
	{
		data->map_copy[i] = ft_strdup(data->map[i]);
		if (!data->map_copy[i])
		{
			while (--i > 0)
				free(data->map_copy[i]);
			return (free(data->map_copy), 0);
		}
		i++;
	}
	get_cpy_data(data);
	fill(data, data->py_cpy, data->px_cpy);
	get_cpy_data(data);
	if (data->cpy_coll_count != 0 || data->cpy_exit_count != 0)
		return (print_and_free2(data), 0);
	return (free_map(data->map_copy, data), 1);
}

int	check_map(t_data *data)
{
	int	i;
	int	len_of_line;

	i = 0;
	len_of_line = len_maps_line(data->map[0]);
	while (data->map[i] && i < data->map_height)
	{
		if (len_of_line != len_maps_line(data->map[i]))
			return (print_error3(), 0);
		i++;
	}
	if (!check_wrong_chars(data))
		return (ft_printf("Wrong characters in map\n"), 0);
	if (!check_requirements(data))
		return (0);
	if (!check_surrounded(data))
		return (0);
	if (!check_take_all_coll_exit(data))
		return (0);
	if (data->map_height > 31 || data->map_len > 60)
		return (ft_printf("Error\nMap is to big\n"), 0);
	return (1);
}
