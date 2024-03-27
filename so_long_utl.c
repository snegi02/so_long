/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snegi <snegi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:29:53 by snegi             #+#    #+#             */
/*   Updated: 2024/02/26 15:29:59 by snegi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_image(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img->player_right);
	mlx_destroy_image(data->mlx, data->img->player_left);
	mlx_destroy_image(data->mlx, data->img->player_up);
	mlx_destroy_image(data->mlx, data->img->player_down);
	mlx_destroy_image(data->mlx, data->img->door);
	mlx_destroy_image(data->mlx, data->img->wall);
	mlx_destroy_image(data->mlx, data->img->background);
	mlx_destroy_image(data->mlx, data->img->heart);
	free(data->img);
}

int	on_destroy(t_data *data)
{
	int	index;

	index = 0;
	while (data->map->map1 && data->map->map1[index])
		free(data->map->map1[index++]);
	free(data->map->map1);
	free_image(data);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}

void	player_direction(t_data *data, int x, int y, char direction)
{
	if (data->map->map1[data->p_y][data->p_x] == 'P')
		data->map->map1[data->p_y][data->p_x] = '0';
	mlx_put_image_to_window(data->mlx, data->win, data->img->background,
		data->p_x * WIDTH, data->p_y * HEIGHT);
	if (direction == 'R')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img->player_right, x * WIDTH, y * HEIGHT);
	else if (direction == 'L')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img->player_left, x * WIDTH, y * HEIGHT);
	else if (direction == 'D')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img->player_down, x * WIDTH, y * HEIGHT);
	else if (direction == 'U')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img->player_up, x * WIDTH, y * HEIGHT);
}

int	game_move(t_data *data, int x, int y, char direction)
{
	data->counter = data->counter + 1;
	ft_printf("this is your %d move.\n", data->counter);
	if (data->map->map1[y][x] == '1')
		return (0);
	else if (data->map->map1[y][x] == '0')
		player_direction(data, x, y, direction);
	else if (data->map->map1[y][x] == 'C')
	{
		player_direction(data, x, y, direction);
		data->map->map1[y][x] = '0';
		data->collected = data->collected + 1;
	}
	else if (data->map->map1[y][x] == 'E' && data->map->c == data->collected)
		on_destroy(data);
	else
		return (0);
	data->p_x = x;
	data->p_y = y;
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		on_destroy(data);
	else if (keycode == 119 || keycode == 65362)
		game_move(data, data->p_x, data->p_y - 1, 'U');
	else if (keycode == 97 || keycode == 65361)
		game_move(data, data->p_x - 1, data->p_y, 'L');
	else if (keycode == 115 || keycode == 65364)
		game_move(data, data->p_x, data->p_y + 1, 'D');
	else if (keycode == 100 || keycode == 65363)
		game_move(data, data->p_x + 1, data->p_y, 'R');
	return (0);
}
