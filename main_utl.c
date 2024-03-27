/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snegi <snegi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:36:05 by snegi             #+#    #+#             */
/*   Updated: 2024/02/07 15:36:07 by snegi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	store_image1(t_image *image, t_data *data)
{
	char	*r_path;
	int		img_width;
	int		img_height;

	r_path = "textures/wall.xpm";
	image->wall = mlx_xpm_file_to_image(data->mlx,
			r_path, &img_width, &img_height);
	r_path = "textures/background.xpm";
	image->background = mlx_xpm_file_to_image(data->mlx,
			r_path, &img_width, &img_height);
	r_path = "textures/heart.xpm";
	image->heart = mlx_xpm_file_to_image(data->mlx,
			r_path, &img_width, &img_height);
}

void	store_image(t_mapdata *mapdata, t_data *data, t_image *image)
{
	char	*r_path;
	int		img_width;
	int		img_height;

	image = malloc(sizeof(t_image));
	data->img = image;
	r_path = "textures/player-right.xpm";
	image->player_right = mlx_xpm_file_to_image(data->mlx, 
			r_path, &img_width, &img_height);
	r_path = "textures/player-left.xpm";
	image->player_left = mlx_xpm_file_to_image(data->mlx,
			r_path, &img_width, &img_height);
	r_path = "textures/player-up.xpm";
	image->player_up = mlx_xpm_file_to_image(data->mlx,
			r_path, &img_width, &img_height);
	r_path = "textures/player-down.xpm";
	image->player_down = mlx_xpm_file_to_image(data->mlx,
			r_path, &img_width, &img_height);
	r_path = "textures/exit.xpm";
	image->door = mlx_xpm_file_to_image(data->mlx,
			r_path, &img_width, &img_height);
	store_image1(image, data);
}

void	put_background(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->size_y)
	{
		x = 0;
		while (x < data->size_x)
		{
			mlx_put_image_to_window(data->mlx,
				data->win, data->img->background, x, y);
			x = x + WIDTH;
		}
		y = y + HEIGHT;
	}
}

void	map_data(t_data *data, int x, int y)
{
	if (data->map->map1[y][x] == '1')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img->wall, x * WIDTH, y * HEIGHT);
	else if (data->map->map1[y][x] == 'P')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img->player_right, x * WIDTH, y * HEIGHT);
	else if (data->map->map1[y][x] == 'E')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img->door, x * WIDTH, y * HEIGHT);
	else if (data->map->map1[y][x] == 'C')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img->heart, x * WIDTH, y * HEIGHT);
}

void	create_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->size_y / HEIGHT)
	{
		x = 0;
		while (x < data->size_x / WIDTH)
		{
			map_data(data, x, y);
			x++;
		}
		y++;
	}
}
