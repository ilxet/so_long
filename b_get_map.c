/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_get_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadamik <aadamik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:00:35 by aadamik           #+#    #+#             */
/*   Updated: 2024/05/08 21:18:07 by aadamik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_map_lenght(t_data *data, char *filepath)
{
	int		fd;
	int		y;
	char	*line;

	y = 1;
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\nWrong map name\n");
		exit(1);
	}
	line = get_next_line(fd);
	if (!line)
	{
		ft_printf("Error\nWrong map\n");
		exit(1);
	}
	data->map_len = ft_strlen(line) - 1;
	while (line != NULL && ft_strlen(line) > 2)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		y++;
	}
	data->map_height = y;
	close(fd);
}

char	*get_filename(char *map_name)
{
	char	*fp;

	fp = malloc(sizeof(char) * (ft_strlen(map_name) + 14));
	if (fp == NULL)
		return (NULL);
	ft_strlcpy(fp, "sources/maps/", 14);
	ft_strlcat(fp, map_name, ft_strlen(fp) + ft_strlen(fp) + 1);
	return (fp);
}

int	get_map(char *map_name, t_data *data)
{
	int		fd;
	int		y;
	char	*filepath;

	filepath = get_filename(map_name);
	y = 0;
	get_map_lenght(data, filepath);
	data->map = malloc((data->map_height + 1) * sizeof(char *));
	if (data->map == NULL)
		return (free(filepath), 1);
	fd = open(filepath, O_RDONLY);
	free(filepath);
	if (fd == -1)
		return (print_error_free_map(data), 0);
	y = 0;
	while (y < data->map_height)
	{
		data->map[y] = get_next_line(fd);
		y++;
	}
	data->map[y] = NULL;
	close(fd);
	return (0);
}

int	len_maps_line(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '1' || str[i] == '0' || str[i] == 'P'
			|| str[i] == 'C' || str[i] == 'E')
			counter++;
		i++;
	}
	return (counter);
}

int	ft_strlen_char(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}
