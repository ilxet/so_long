/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_destroy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadamik <aadamik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:58:28 by aadamik           #+#    #+#             */
/*   Updated: 2024/05/07 18:45:09 by aadamik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map, t_data *data)
{
	int	x;

	x = 0;
	while (x < data->map_height)
		free(map[x++]);
	free(map);
}

void	destroy_images_helper(t_data *data)
{
	if (data->img_background)
	{
		mlx_destroy_image(data->mlx_ptr, data->img_background);
		data->img_background = NULL;
	}
}

void	destroy_images(t_data *data)
{
	destroy_images_helper(data);
	if (data->img_player)
	{
		mlx_destroy_image(data->mlx_ptr, data->img_player);
		data->img_player = NULL;
	}
	if (data->img_wall)
	{
		mlx_destroy_image(data->mlx_ptr, data->img_wall);
		data->img_wall = NULL;
	}
	if (data->img_collectible)
	{
		mlx_destroy_image(data->mlx_ptr, data->img_collectible);
		data->img_collectible = NULL;
	}
	if (data->img_exit)
	{
		mlx_destroy_image(data->mlx_ptr, data->img_exit);
		data->img_exit = NULL;
	}
}

int	on_destroy(t_data *data)
{
	destroy_images(data);
	if (data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	exit(0);
}
