/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadamik <aadamik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:02:53 by aadamik           #+#    #+#             */
/*   Updated: 2024/04/24 18:34:18 by aadamik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void free_map(char **map)
{
	int	x;

	x = 0;
	while (x++ < MAX_LINES)
		free(map[x]);
	free(map);
}

int on_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

int get_map(char *map_name, t_data *data)
{
	int		fd;
	int		y;
	char	*line;
	char	*filepath;

	filepath = malloc(sizeof(char) * (ft_strlen(map_name) + 6));
	if (filepath == NULL) 
		return (1);
	ft_strlcpy(filepath, "sources/maps/", 14);
	ft_strlcat(filepath, map_name, 14 + ft_strlen(map_name));
	y = 0;
	data->map = malloc(MAX_LINES * sizeof(char *));
	if (data->map == NULL)
		return (free(filepath), 1);
	while (y < MAX_LINES)
	{
		data->map[y] = malloc(MAX_LINE_LENGTH * sizeof(char));
		if (data->map[y] == NULL)
			return (free(filepath), free(data->map), 1);
		y++;
	}
	fd = open(filepath, O_RDONLY);
	free(filepath);
	if (fd == -1)
		return (ft_printf("Can't open the map\n"), free(filepath), free_map(data->map), 0);
	y = 0;
	line = malloc(sizeof(char) * MAX_LINE_LENGTH);
	while((line = get_next_line(fd)) != NULL)
	{
		if(ft_strlen(line) != 0)
			ft_strlcpy(data->map[y++], line, MAX_LINE_LENGTH);
	}
	data->ar_height = y;
	free(line);
	return (0);
}

int len_maps_line(char *str)
{
	int	i;
	int counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '1' || str[i] == '0' || str[i] == 'P' || str[i] == 'C' || str[i] == 'E')
			counter++;
		i++;
	}
	return (counter);
}

int check_wrong_chars(t_data *data)
{
	int	len_of_good_chars;
	int	i;

	len_of_good_chars = len_maps_line(data->map[0]);
	i = 0;
	while (data->map[i] && len_maps_line(data->map[i]) != 0)
		{
			data->map[i][len_of_good_chars] = '\0';
			if (ft_strlen(data->map[i]) != len_maps_line(data->map[i]))
				return (0);
			i++;
		}
	return (1);
}

int check_requirements(t_data *data)
{
	int	exits;
	int	players;
	int y;
	int x;

	y = 0;
	exits = 0;
	players = 0;
	while (data->map[y])
	{
		x = 0;
		while(data->map[y][x])
		{
			if(data->map[y][x] == 'P')
				players++;
			if(data->map[y][x] == 'E')
				exits++;
			x++;
		}
		y++;
	}
	if(players > 1 || exits > 1)
		return (ft_printf("Error\nPlease provide a map with 1 player and 1 exit"), 0);
	return (1);
}

int check_for_ones(t_data *data, int y, int x)
{
	int j;
	int i;

	j = 0;
	while(data->map[0][j] == '1')
		j++;
	i = 0;
	while(data->map[y-1][i] == '1')
		i++;
	if (j != x || i != x)
		return (0);
	j = 0;
	while (data->map[j][0] == '1')
		j++;
	i = 0;
	while (data->map[i][x - 1] == '1')
		i++;
	if (j != y || i != y )
		return (0);
	return (1);
}

int check_surrounded(t_data *data)
{
	int y;
	int x;
	
	y = 0;
	while(data->map[y] && len_maps_line(data->map[y]) >= 3)
	{
		x = 0;
		while(data->map[y][x] && data->map[y][x] != '\n')
			x++;
		y++;
	}
	// data->y = y;
	// data->x = x;
	if(!check_for_ones(data, y, x))
		return (ft_printf("Error\nMap is not surrounded by the walls\n"), 0);
	return (1);
}

int	check_take_all_coll_exit(t_data *data)
{
	char **cpy_map;
	int i = 0;

	cpy_map = malloc(sizeof(char *) * data->ar_height + 1);
	if(!cpy_map)
		return(free_map(data->map), 0);
	while(data->map[i])
	{
		cpy_map[i] = ft_strdup(data->map[i]);
		if(!cpy_map[i])
		{
			while(--i > 0)
				free(cpy_map[i]);
			return(free_map(data->map), 0);
		}
		i++;
	}
	// if ()
	return (free_map(cpy_map), 1);
}

int check_map(t_data *data)
{
	int	i;
	int len_of_line;

	i = 0;
	len_of_line = len_maps_line(data->map[0]);
	data->ar_width = len_of_line;
	while(data->map[i])
	{
		if (len_of_line != len_maps_line(data->map[i]) && len_maps_line(data->map[i]) != 0)
		{ 
			return(ft_printf("Error\nPlease provide a map that will be a rectangle out of correct chars\n"), 0);
		}
		i++;
	}
	if(!check_wrong_chars(data))
		return (ft_printf("Wrong characters in map\n"), 0);
	if(!check_requirements(data))
		return (0);
	if(!check_surrounded(data))
		return (0);
	if(!check_take_all_coll_exit(data))
		return(0);
	return (1);
}

int render_map(t_data *data)
{
	int	y;
	int	x;
	char *path_background = "textures/Background.xpm";
	char *path_player = "textures/Player.xpm";
	char *path_wall = "textures/Wall.xpm";
	char *path_collectible = "textures/Collectible.xpm";
	char *path_exit = "textures/Exit.xpm";
	int height = 64;
	int width = 64;
	y = 0;
	void * img_background = mlx_xpm_file_to_image(data->mlx_ptr, path_background, &width, &height);
	data->coll_count = 0;
	data->e_count = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '0')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img_background, x * 64, y * 64);
			if (data->map[y][x] == 'P')
			{
				void * img_player = mlx_xpm_file_to_image(data->mlx_ptr, path_player, &width, &height);
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img_player, x * 64, y * 64);
				data->py = y;
				data->px = x;
			}
			if (data->map[y][x] == '1')
			{
				void * img_wall = mlx_xpm_file_to_image(data->mlx_ptr, path_wall, &width, &height);
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img_wall, x * 64, y * 64);
			}
			if (data->map[y][x] == 'C')
			{
				data->coll_count++;
				void * img_collectible = mlx_xpm_file_to_image(data->mlx_ptr, path_collectible, &width, &height);
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img_collectible, x * 64, y * 64);
			}
			if (data->map[y][x] == 'E')
			{
				data->e_count++;
				void * img_exit = mlx_xpm_file_to_image(data->mlx_ptr, path_exit, &width, &height);
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img_exit, x * 64, y * 64);
			}
			x++;
		}
		y++;
	}
	printf("Number of moves: %d\n", data->moves);
	return(0);
}

void move_up(t_data *data)
{
	if (data->map[data->py - 1][data->px] != '1' && (data->map[data->py - 1][data->px] != 'E' || data->coll_count == 0))
	{
		data->map[data->py][data->px] = '0';
		data->map[data->py - 1][data->px] = 'P';
		data->moves++;
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
		render_map(data);
	}
}

int	key_press(int keycode, t_data *data)
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

// int exit_game(int keycode, t_data *data)
// {
// 	t_data *temp = data;
// 	free(temp);
// 	printf("%d", keycode);
// 	return(0);
// }
int main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		get_map(argv[1], &data);
		if (check_map(&data))
		{
			data.moves = 0;
			data.mlx_ptr = mlx_init();
			data.win_ptr = mlx_new_window(data.mlx_ptr, data.ar_width * 64, data.ar_height * 64, "game2d");
			
			render_map(&data);
			mlx_hook(data.win_ptr, 17, 1L<<17, on_destroy, &data);
			mlx_hook(data.win_ptr, 2, 1L<<0, key_press, &data);
			// mlx_hook(data.win_ptr, 2, 1L<<17, on_destroy, &data);
			// // Register key release hook
			// mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);
			// // Register destroy hook
			// mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
			mlx_loop(data.mlx_ptr);
		}
		free_map(data.map);

// 	data.mlx_ptr = mlx_init();
// 	if (!data.mlx_ptr)
// 		return (1);
// 	data.win_ptr = mlx_new_window(data.mlx_ptr, 600, 400, "hi :)");
// 	if (!data.win_ptr)
// 		return (free(data.mlx_ptr), 1);
// 	// Register key release hook
	// Register destroy hook
	// Loop over the MLX pointer
// 	mlx_loop(data.mlx_ptr);
	}
	else
		write(1, "Error, no correct path to map", 29);
	return (0);
}