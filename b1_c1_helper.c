/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b1_c1_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadamik <aadamik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:51:42 by aadamik           #+#    #+#             */
/*   Updated: 2024/05/08 17:19:37 by aadamik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_error_free_map(t_data *data)
{
	ft_printf("Error\nWrong map name\n");
	free_map(data->map, data);
}

void	print_and_free2(t_data *data)
{
	ft_printf("Error\nNot all collectibles or exit are reachible.\n");
	free_map(data->map_copy, data);
}

void	print_error3(void)
{
	ft_printf("Error\nMap not a rectangle out of correct chars\n");
}
