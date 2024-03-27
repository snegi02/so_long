/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snegi <snegi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:26:09 by snegi             #+#    #+#             */
/*   Updated: 2024/02/26 15:26:11 by snegi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	path_exist(int y, int x, char **temp, t_data *data)
{
	if (x < 0 || y < 0 || x >= data->map->count || y >= data->map->num_nextline
		|| temp[y][x] == '1')
		return ;
	temp[y][x] = '1';
	path_exist(y - 1, x, temp, data);
	path_exist(y, x - 1, temp, data);
	path_exist(y + 1, x, temp, data);
	path_exist(y, x + 1, temp, data);
}

char	**create_copymap(t_data *data)
{
	char	**temp;
	int		i;
	int		index;

	index = 0;
	temp = malloc((data->map->num_nextline + 1) * sizeof(char *));
	temp[data->map->num_nextline] = NULL;
	while (index < data->map->num_nextline)
	{
		i = 0;
		temp[index] = malloc((data->map->count + 1) * sizeof(char));
		while (i < data->map->count)
		{
			temp[index][i] = data->map->map1[index][i];
			i++;
		}
		temp[index][i] = '\0';
		index++;
	}
	return (temp);
}

void	check_path(t_data *data)
{
	int		x;
	int		y;
	char	**temp;

	y = 0;
	temp = create_copymap(data);
	path_exist(data->p_y, data->p_x, temp, data);
	while (y < data->map->num_nextline)
	{
		x = 0;
		while (x < data->map->count)
		{
			if (temp[y][x] != '0' && temp [y][x] != '1')
				error_notplayable("Error\n : Not Playable!!!\n", temp, data);
			x++;
		}
		y++;
	}
	y = 0;
	while (temp && temp[y])
		free(temp[y++]);
	free(temp);
}

void	player_index(int y, int x, t_data *data, char *temp)
{
	data->map->map1[y][x] = temp[x];
	if (data->map->map1[y][x] == 'P')
	{
		data->p_x = x;
		data->p_y = y;
	}
}

void	makemap(char **ar, t_mapdata *mapdata, t_data *data)
{
	char	*temp;
	int		i;
	int		index;
	int		fd;

	fd = open(ar[1], O_RDONLY);
	index = 0;
	mapdata->map1 = malloc((mapdata->num_nextline + 1) * sizeof(char *));
	mapdata->map1[mapdata->num_nextline] = NULL;
	temp = get_next_line(fd);
	while (temp)
	{
		i = 0;
		mapdata->map1[index] = malloc((mapdata->count + 1) * sizeof(char));
		while (temp[i] != '\n' && temp[i] != '\0')
		{
			player_index(index, i, data, temp);
			i++;
		}
		mapdata->map1[index][i] = '\0';
		free(temp);
		temp = get_next_line(fd);
		index++;
	}
	close(fd);
}
