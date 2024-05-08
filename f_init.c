/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadamik <aadamik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:13:54 by aadamik           #+#    #+#             */
/*   Updated: 2024/05/08 17:26:10 by aadamik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_struct_helper(t_data *data)
{
	data->img_background = NULL;
	data->img_player = NULL;
	data->img_wall = NULL;
	data->img_collectible = NULL;
	data->img_exit = NULL;
	data->map_len = 0;
	data->map_height = 0;
	data->path_background = NULL;
	data->path_player = NULL;
	data->path_wall = NULL;
	data->path_collectible = NULL;
	data->path_exit = NULL;
}

void	init_struct(t_data *data)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->map = NULL;
	data->map_copy = NULL;
	data->py = 0;
	data->px = 0;
	data->coll_count = 0;
	data->moves = 0;
	data->e_count = 0;
	data->cpy_coll_count = 0;
	data->cpy_exit_count = 0;
	data->px_cpy = 0;
	data->py_cpy = 0;
	init_struct_helper(data);
}
