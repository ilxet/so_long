/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_load_image_render.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadamik <aadamik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:09:49 by aadamik           #+#    #+#             */
/*   Updated: 2024/05/08 17:23:31 by aadamik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_image(t_data data, char *path, int x, int y)
{
	int		width;
	int		height;
	void	*img;

	width = 64;
	height = 64;
	img = mlx_xpm_file_to_image(data.mlx_ptr, path, &width, &height);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, img, x * 64, y * 64);
	mlx_destroy_image(data.mlx_ptr, img);
}

void	get_paths(t_data *data)
{
	data->path_background = "textures/Background.xpm";
	data->path_player = "textures/Player.xpm";
	data->path_wall = "textures/Wall.xpm";
	data->path_collectible = "textures/Collectible.xpm";
	data->path_exit = "textures/Exit.xpm";
	data->coll_count = 0;
	data->e_count = 0;
}

void	render_map_helper(char *line_of_map, t_data *data, int x, int y)
{
	while (line_of_map[x])
	{
		if (line_of_map[x] == '0')
			load_image(*data, data->path_background, x, y);
		if (line_of_map[x] == 'P')
		{
			data->py = y;
			data->px = x;
			load_image(*data, data->path_player, x, y);
		}
		if (line_of_map[x] == '1')
			load_image(*data, data->path_wall, x, y);
		if (line_of_map[x] == 'C')
		{
			data->coll_count++;
			load_image(*data, data->path_collectible, x, y);
		}
		if (line_of_map[x] == 'E')
		{
			data->e_count++;
			load_image(*data, data->path_exit, x, y);
		}
		x++;
	}
}

int	render_map(t_data *data)
{
	int	y;
	int	x;

	get_paths(data);
	y = 0;
	while (data->map[y])
	{
		x = 0;
		render_map_helper(data->map[y], data, x, y);
		y++;
	}
	ft_printf("Number of moves: %d\n", data->moves);
	return (0);
}
