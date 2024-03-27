/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snegi <snegi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:39:01 by snegi             #+#    #+#             */
/*   Updated: 2024/02/06 14:39:03 by snegi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_strcmp(char *str)
{
	int		i;
	char	*cmp;

	cmp = ".ber";
	i = 0;
	while (str[i]) 
	{
		if (str[i] != cmp[i])
			error("Error\n :please enter.ber file only\n", NULL, -1);
		i++;
	}
}

void	check_recterror(char *next, t_mapdata *mapdata, int fd)
{
	int	i;

	i = 0;
	while (next[i] != '\n' && next[i] != '\0')
	{
		if ((mapdata->num_nextline == 0 && next[i] != '1') || next[0] != '1')
			error("Error\n :map should be properly walled\n", next, fd);
		if (next[i] == 'E')
			mapdata->e++;
		if (next[i] == 'P')
			mapdata->p++;
		if (next[i] == 'C')
			mapdata->c++;
		if (next[i] != '1' && next[i] != '0' && next[i] != 'E'
			&& next[i] != 'P' && next[i] != 'C')
			mapdata->o++;
		i++;
	}
	if (next[i - 1] != '1')
		error("Error\n :map should be properly walled\n", next, fd);
	if (mapdata->count == 0) 
		mapdata->count = i;
	if (mapdata->count != i)
		error("Error\n :map is not rectangle\n", next, fd);
}

void	check_rectangle(int fd, char *next_line, t_mapdata *mapdata)
{
	char	*temp;
	int		i;

	while (next_line)
	{
		check_recterror(next_line, mapdata, fd);
		temp = get_next_line(fd);
		i = 0;
		while (!temp && next_line[i] != '\n' && next_line[i] != '\0')
		{
			if (next_line[i] != '1')
				error("Error\n :map should be properly walled\n", next_line, fd);
			i++;
		}
		free(next_line);
		next_line = temp;
		mapdata->num_nextline++;
	}
	if (mapdata->e != 1 || mapdata->p != 1 || mapdata->c < 1 || mapdata->o > 0)
		error("Error\n : map(1-E,1-P,C>1,1,0 no other char) )\n", next_line, fd);
}

void	find_error(t_mapdata *mapdata, char **ar, t_data *data)
{
	char	*next_line;
	int		fd;

	fd = open(ar[1], O_RDONLY);
	if (fd < 0)
		error("Error\n : no such map\n", NULL, -1);
	ft_strcmp(ar[1] + (ft_strlen(ar[1]) - 4));
	mapdata->count = 0;
	mapdata->num_nextline = 0;
	mapdata->e = 0;
	mapdata->p = 0;
	mapdata->c = 0;
	mapdata->o = 0;
	next_line = get_next_line(fd);
	if (!next_line)
		error("Error\n : No map\n", next_line, -1);
	check_rectangle(fd, next_line, mapdata);
	close(fd);
	data->map = mapdata;
	if (mapdata->count * WIDTH >= 1920 || mapdata->num_nextline * HEIGHT >= 1080)
		error("Error\n : Map size is big\n", NULL, -1);
	makemap(ar, mapdata, data);
	check_path(data);
}

int	main(int ac, char **ar)
{
	t_mapdata	mapdata;
	t_data		data;
	t_image		image;

	if (ac != 2)
		return (0);
	find_error(&mapdata, ar, &data);
	data.size_x = mapdata.count * WIDTH;
	data.size_y = mapdata.num_nextline * HEIGHT;
	data.counter = 0;
	data.collected = 0;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.size_x, data.size_y, "./So_long");
	store_image(&mapdata, &data, &image);
	put_background(&data);
	create_map(&data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_hook(data.win, 17, 0, on_destroy, &data);
	mlx_loop(data.mlx);
	return (0);
}
