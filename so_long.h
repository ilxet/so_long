/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadamik <aadamik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:00:44 by aadamik           #+#    #+#             */
/*   Updated: 2024/05/08 20:29:58 by aadamik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// #  define WIDTH 2000
// #  define HEIGHT 1000

# include "minilibx-linux/mlx.h"
# include "sources/gnl1/get_next_line.h"
# include "sources/printf/ft_printf.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_data
{
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
	void	*img_background;
	void	*img_player;
	void	*img_wall;
	void	*img_collectible;
	void	*img_exit;
	int		map_len;
	int		map_height;
	char	*path_background;
	char	*path_player;
	char	*path_wall;
	char	*path_collectible;
	char	*path_exit;
}	t_data;

void	free_map(char **map, t_data *data);
void	destroy_images_helper(t_data *data);
void	destroy_images(t_data *data);
int		on_destroy(t_data *data);
void	get_map_lenght(t_data *data, char *filepath);
char	*get_filename(char *map_name);
int		get_map(char *map_name, t_data *data);
int		len_maps_line(char *str);
int		ft_strlen_char(char *str);
int		check_wrong_chars(t_data *data);
int		check_requirements(t_data *data);
int		check_for_ones(t_data *data, int y, int x);
int		check_surrounded(t_data *data);
void	get_cpy_data(t_data *data);
void	fill(t_data *data, int y, int x);
int		check_take_all_coll_exit(t_data *data);
int		check_map(t_data *data);
void	load_image(t_data data, char *path, int x, int y);
void	get_paths(t_data *data);
void	render_map_helper(char *line_of_map, t_data *data, int x, int y);
int		render_map(t_data *data);
void	move_up(t_data *data);
void	move_left(t_data *data);
void	move_down(t_data *data);
void	move_right(t_data *data);
int		key_press(int keycode, t_data *data);
void	init_struct_helper(t_data *data);
void	init_struct(t_data *data);
int		main(int argc, char **argv);
void	print_error_free_map(t_data *data);
void	print_and_free2(t_data *data);
void	print_error3(void);

#endif