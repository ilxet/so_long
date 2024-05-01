/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadamik <aadamik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:00:44 by aadamik           #+#    #+#             */
/*   Updated: 2024/04/30 23:36:26 by aadamik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef MAX_LINE_LENGTH
#  define MAX_LINE_LENGTH 100
#  define MAX_LINES 100
// #  define WIDTH 2000
// #  define HEIGHT 1000

# include "minilibx-linux/mlx.h"
# include "sources/gnl/get_next_line.h"
# include "sources/ft_printf/ft_printf.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_data
{
	int 	ar_width;
	int 	ar_height;
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	char	**map_copy;
	int		py;
	int		px;
	int		coll_count;
	int		moves;
	int		e_count;
	int		cpy_coll_count;
	int		cpy_exit_count;
	int		px_cpy;
	int		py_cpy;
	void * img_background;
	void * img_player;
	void * img_wall;
	void * img_collectible;
	void * img_exit;
	// int		y;
	// int		x;
} t_data;

# endif
#endif