/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_move.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadamik <aadamik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:11:25 by aadamik           #+#    #+#             */
/*   Updated: 2024/05/08 17:25:21 by aadamik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_up(t_data *data)
{
	if (data->map[data->py - 1][data->px] != '1'
		&& (data->map[data->py - 1][data->px] != 'E' || data->coll_count == 0))
	{
		data->map[data->py][data->px] = '0';
		data->map[data->py - 1][data->px] = 'P';
		data->moves++;
		destroy_images(data);
		render_map(data);
	}
}

void	move_left(t_data *data)
{
	if (data->map[data->py][data->px - 1] != '1'
		&& (data->map[data->py][data->px - 1] != 'E' || data->coll_count == 0))
	{
		data->map[data->py][data->px] = '0';
		data->map[data->py][data->px - 1] = 'P';
		data->moves++;
		destroy_images(data);
		render_map(data);
	}
}

void	move_down(t_data *data)
{
	if (data->map[data->py + 1][data->px] != '1'
		&& (data->map[data->py + 1][data->px] != 'E' || data->coll_count == 0))
	{
		data->map[data->py][data->px] = '0';
		data->map[data->py + 1][data->px] = 'P';
		data->moves++;
		destroy_images(data);
		render_map(data);
	}
}

void	move_right(t_data *data)
{
	if (data->map[data->py][data->px + 1] != '1'
		&& (data->map[data->py][data->px + 1] != 'E' || data->coll_count == 0))
	{
		data->map[data->py][data->px] = '0';
		data->map[data->py][data->px + 1] = 'P';
		data->moves++;
		destroy_images(data);
		render_map(data);
	}
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		on_destroy(data);
	if (keycode == 119)
		move_up(data);
	if (keycode == 97)
		move_left(data);
	if (keycode == 115)
		move_down(data);
	if (keycode == 100)
		move_right(data);
	if (data->e_count != 1)
		on_destroy(data);
	return (0);
}
