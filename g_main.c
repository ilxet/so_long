/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadamik <aadamik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:02:53 by aadamik           #+#    #+#             */
/*   Updated: 2024/05/08 17:38:27 by aadamik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		l;
	int		h;

	if (argc == 2)
	{
		if (!argv[1] || ft_strlen(argv[1]) == 0)
			return (ft_printf("Wrong map name\n"), 1);
		init_struct(&data);
		get_map(argv[1], &data);
		if (check_map(&data))
		{
			data.moves = 0;
			data.mlx_ptr = mlx_init();
			h = data.map_height * 64;
			l = data.map_len * 64;
			data.win_ptr = mlx_new_window(data.mlx_ptr, l, h, "game2d");
			render_map(&data);
			mlx_hook(data.win_ptr, 17, 1L << 17, on_destroy, &data);
			mlx_hook(data.win_ptr, 2, 1L << 0, key_press, &data);
			mlx_loop(data.mlx_ptr);
		}
		free_map(data.map, &data);
	}
	return (0);
}
