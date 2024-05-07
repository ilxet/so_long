/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadamik <aadamik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:02:53 by aadamik           #+#    #+#             */
/*   Updated: 2024/05/05 18:05:39 by aadamik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void free_map(char **map, t_data *data)
{
	int x;
 
	x = 0;
	while (x < data->map_height)
		free(map[x++]);
	free(map);
}

void destroy_images(t_data *data)
{
	if (data->img_background)
	{
		mlx_destroy_image(data->mlx_ptr, data->img_background);
		data->img_background = NULL;
	}
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

int on_destroy(t_data *data)
{
	destroy_images(data);
	if (data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	exit(0);
}

void get_map_lenght(t_data *data, char *filepath)
{
	int fd;
	int y;
	char *line;
	
	y = 1;
	fd = open(filepath, O_RDONLY);
	if (fd == -1 )
	{
		ft_printf("Error\nWrong map name\n");
		exit(1);
	}
	line = get_next_line(fd);
	data->map_len = ft_strlen(line) - 1;
	while (line != NULL && ft_strlen(line) > 2)
	{
		free(line);
		line = get_next_line(fd);
		if(!line)
			break;
		y++;
	}
	// printf("%i\n", data->map_len);
	data->map_height = y;
	close(fd);
	return;
}

int get_map(char *map_name, t_data *data)
{
	int fd;
	int y;
	// char *line;
	char *filepath;

	filepath = malloc(sizeof(char) * (ft_strlen(map_name) + 14));
	if (filepath == NULL)
		return (1);
	ft_strlcpy(filepath, "sources/maps/", 14);
	// filepath = ft_strdup("sources/maps/");
	ft_strlcat(filepath, map_name, ft_strlen(filepath) + ft_strlen(map_name) + 1);
	y = 0;
	get_map_lenght(data, filepath);
	data->map = malloc((data->map_height + 1) * sizeof(char *));
	if (data->map == NULL)
		return (free(filepath), 1);
	// while (y < data->map_height)
	// {
	// 	data->map[y] = malloc((data->map_len + 1) * sizeof(char));
	// 	if (data->map[y] == NULL)
	// 	{
	// 		// while(y-- > 0)
	// 		// 	free(data->map[y]);
	// 		return (free(filepath), free(data->map), 1);
	// 	}
	// 	y++;
	// }
	fd = open(filepath, O_RDONLY);
	free(filepath);
	if (fd == -1)
		return (ft_printf("Error\nWrong map name\n"), free_map(data->map, data), 0);
	y = 0;
	while (y < data->map_height)
	{
		data->map[y] = get_next_line(fd);
		y++;
	}
	// while ((line = get_next_line(fd)) != NULL)
	// {
	// 	if (ft_strlen(line) != 0) {
	// 		ft_strlcpy(data->map[y], line, data->map_len + 1);
	// 		y++;
	// 		free(line);
	// 	}
	// }
	data->map[y] = NULL;
	close(fd);
	data->ar_height = y;
	// free(line);
	return (0);
}

int len_maps_line(char *str)
{
	int i;
	int counter;

	i = 0;
	counter = 0;
	if(!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '1' || str[i] == '0' || str[i] == 'P' || str[i] == 'C' || str[i] == 'E')
			counter++;
		i++;
	}
	return (counter);
}

int ft_strlen_char(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

int check_wrong_chars(t_data *data)
{
	// int len_of_good_chars;
	int i;
	// len_of_good_chars = len_maps_line(data->map[0]);
	i = 0;
	while (data->map[i] && len_maps_line(data->map[i]) != 0)
	{
		printf("check 2\n");
		// data->map[i][len_of_good_chars] = '\0';
		if (ft_strlen_char(data->map[i]) != len_maps_line(data->map[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int check_requirements(t_data *data)
{
	int exits;
	int players;
	int y;
	int x;

	y = 0;
	exits = 0;
	players = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'P')
				players++;
			if (data->map[y][x] == 'E')
				exits++;
			x++;
		}
		y++;
	}
	if (players > 1 || exits > 1)
		return (ft_printf("Error\nPlease provide a map with 1 player and 1 exit"), 0);
	return (1);
}

int check_for_ones(t_data *data, int y, int x)
{
	int j;
	int i;

	j = 0;
	while (data->map[0][j] == '1')
		j++;
	i = 0;
	while (data->map[data->map_height - 1][i] == '1')
		i++;
	if (j != x || i != x)
		return (printf("HALO1\n"), 0);
	j = 0;
	while (data->map[j] && data->map[j][0] == '1')
		j++;
	i = 0;
	while (data->map[i] && data->map[i][x - 1] == '1')
		i++;
	if (j != y || i != y)
		return (printf("HALO2\n"), 0);
	return (1);
}

int check_surrounded(t_data *data)
{
	int y;
	int x;

	y = 0;
	while (data->map[y] && len_maps_line(data->map[y]) >= 3)
	{
		x = 0;
		while (data->map[y][x] && data->map[y][x] != '\n')
			x++;
		y++;
	}
	// data->y = y;
	// data->x = x;
	if (!check_for_ones(data, data->map_height, data->map_len))
		return (ft_printf("Error\nMap is not surrounded by the walls\n"), 0);
	return (1);
}

void get_cpy_data(t_data *data)
{
	int y;
	int x;

	y = 0;
	data->cpy_coll_count = 0;
	data->cpy_exit_count = 0;
	while (data->map_copy[y])
	{
		x = 0;
		while (data->map_copy[y][x])
		{
			if (data->map_copy[y][x] == 'C')
				data->cpy_coll_count++;
			if (data->map_copy[y][x] == 'E')
				data->cpy_exit_count++;
			if (data->map_copy[y][x] == 'P')
			{
				data->px_cpy = x;
				data->py_cpy = y;
			}
			x++;
		}
		y++;
	}
}

void fill(t_data *data, int y, int x)
{
	if (y < 0 || y >= data->ar_height || x < 0 || x >= data->map_len || data->map_copy[y][x] == 'E' || data->map_copy[y][x] == '1')
	{
		if (data->map_copy[y][x] != '\0')
			data->map_copy[y][x] = '1';
		return;
	}
	data->map_copy[y][x] = '1';
	fill(data, y, x - 1);
	fill(data, y, x + 1);
	fill(data, y - 1, x);
	fill(data, y + 1, x);
}

int check_take_all_coll_exit(t_data *data)
{
	int i = 0;
//	data->map_copy = malloc(sizeof(char *) * data->ar_height + 1);
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
	// usunac po sprawdzeniu
	// int y = 0;
	// int x;
	// while (data->map_copy[y])
	// {
	// 	x = 0;
	// 	while (data->map_copy[y][x])
	// 	{
	// 		printf("%c", data->map_copy[y][x]);
	// 		x++;
	// 	}
	// 	printf("\n");
	// 	y++;
	// }
	//
	get_cpy_data(data);
	if (data->cpy_coll_count != 0 || data->cpy_exit_count != 0)
	{
		free_map(data->map_copy, data);
		return (ft_printf("Error\nNot all collectibles or exit are reachible.\n"), 0);
	}
	return (free_map(data->map_copy, data), 1);
	// return (1);
}

int check_map(t_data *data)
{
	int i;
	int len_of_line;

	i = 0;
	len_of_line = len_maps_line(data->map[0]);
	data->ar_width = len_of_line;
	while (data->map[i] && i < data->map_height)
	{
		// printf("len_of_line: %d\n", len_of_line);
		// printf("len_maps_line: %d\n", len_maps_line(data->map[i]));
		// printf("ft_strlen: %d\n", ft_strlen(data->map[i]));
		// printf("i: %d\n", i);
		if (len_of_line != len_maps_line(data->map[i]))
		{
			return (ft_printf("Error\nPlease provide a map that will be a rectangle out of correct chars\n"), 0);
		}
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

void load_image(t_data data, char *path, int x, int y){
	int width;
	int height;
	
	void *img = mlx_xpm_file_to_image(data.mlx_ptr, path, &width, &height);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, img, x * 64, y * 64);
	mlx_destroy_image(data.mlx_ptr, img);
}

int render_map(t_data *data)
{
	int y;
	int x;
	char *path_background = "textures/Background.xpm";
	char *path_player = "textures/Player.xpm";
	char *path_wall = "textures/Wall.xpm";
	char *path_collectible = "textures/Collectible.xpm";
	char *path_exit = "textures/Exit.xpm";
	int height = 64;
	int width = 64;
	y = 0;
	data->img_background = mlx_xpm_file_to_image(data->mlx_ptr, path_background, &width, &height);
	data->coll_count = 0;
	data->e_count = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '0')
			{

				load_image(*data, path_background, x,y);
				// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_background, x * 64, y * 64);
				// mlx_destroy_image(data->mlx_ptr, data->img_background);
			}	
			if (data->map[y][x] == 'P')
			{
				data->py = y;
				data->px = x;
				load_image(*data, path_player, x,y);
				// data->img_player = mlx_xpm_file_to_image(data->mlx_ptr, path_player, &width, &height);
				// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_player, x * 64, y * 64);
				// mlx_destroy_image(data->mlx_ptr, data->img_player);
			}
			if (data->map[y][x] == '1')
			{
				load_image(*data, path_wall, x,y);
				// data->img_wall = mlx_xpm_file_to_image(data->mlx_ptr, path_wall, &width, &height);
				// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_wall, x * 64, y * 64);
				// mlx_destroy_image(data->mlx_ptr, data->img_wall);
			}
			if (data->map[y][x] == 'C')
			{
				data->coll_count++;
				load_image(*data, path_collectible, x,y);
				// data->img_collectible = mlx_xpm_file_to_image(data->mlx_ptr, path_collectible, &width, &height);
				// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_collectible, x * 64, y * 64);
				// mlx_destroy_image(data->mlx_ptr, data->img_collectible);
			}
			if (data->map[y][x] == 'E')
			{
				data->e_count++;
				load_image(*data, path_exit, x,y);

				// data->img_exit = mlx_xpm_file_to_image(data->mlx_ptr, path_exit, &width, &height);
				// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_exit, x * 64, y * 64);
				// mlx_destroy_image(data->mlx_ptr, data->img_exit);
			}
			x++;
		}
		y++;
	}
	printf("Number of moves: %d\n", data->moves);
	return (0);
}

void move_up(t_data *data)
{
	if (data->map[data->py - 1][data->px] != '1' && (data->map[data->py - 1][data->px] != 'E' || data->coll_count == 0))
	{
		data->map[data->py][data->px] = '0';
		data->map[data->py - 1][data->px] = 'P';
		data->moves++;
		destroy_images(data);
		render_map(data);
	}
}

void move_left(t_data *data)
{
	if (data->map[data->py][data->px - 1] != '1' && (data->map[data->py][data->px - 1] != 'E' || data->coll_count == 0))
	{
		data->map[data->py][data->px] = '0';
		data->map[data->py][data->px - 1] = 'P';
		data->moves++;
		destroy_images(data);
		render_map(data);
	}
}

void move_down(t_data *data)
{
	if (data->map[data->py + 1][data->px] != '1' && (data->map[data->py + 1][data->px] != 'E' || data->coll_count == 0))
	{
		data->map[data->py][data->px] = '0';
		data->map[data->py + 1][data->px] = 'P';
		data->moves++;
		destroy_images(data);
		render_map(data);
	}
}

void move_right(t_data *data)
{
	if (data->map[data->py][data->px + 1] != '1' && (data->map[data->py][data->px + 1] != 'E' || data->coll_count == 0))
	{
		data->map[data->py][data->px] = '0';
		data->map[data->py][data->px + 1] = 'P';
		data->moves++;
		destroy_images(data);
		render_map(data);
	}
}

int key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		on_destroy(data);
		// mlx_destroy_display(data->mlx_ptr);
	}
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

void init_struct(t_data *data)
{
	data->ar_width = 0;
	data->ar_height = 0;
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
	data->img_background = NULL;
	data->img_player = NULL;
	data->img_wall = NULL;
	data->img_collectible = NULL;
	data->img_exit = NULL;
	data->map_len = 0;
	data->map_height = 0;
}

int main(int argc, char **argv)
{
	t_data data;
	
	if (argc == 2)
	{
		if(!argv[1] || ft_strlen(argv[1]) == 0)
			return (ft_printf("Wrong map name\n"), 1);
		init_struct(&data);
		get_map(argv[1], &data);
		if (check_map(&data))
		{
			data.moves = 0;
			data.mlx_ptr = mlx_init();
			data.win_ptr = mlx_new_window(data.mlx_ptr, data.map_len * 64, data.map_height * 64, "game2d");

			render_map(&data);
			mlx_hook(data.win_ptr, 17, 1L << 17, on_destroy, &data);
			mlx_hook(data.win_ptr, 2, 1L << 0, key_press, &data);
			mlx_loop(data.mlx_ptr);
		}
		free_map(data.map, &data);
	}
	else
		write(1, "Error, no correct path to map", 29);
	return (0);
}
