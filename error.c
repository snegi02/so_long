/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snegi <snegi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:41:08 by snegi             #+#    #+#             */
/*   Updated: 2024/02/27 15:41:11 by snegi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error(char *str, char *next_line, int fd)
{
	write(1, str, ft_strlen(str));
	while (next_line && fd > -1)
	{
		free(next_line);
		next_line = get_next_line(fd);
	}
	if (fd > -1)
		close(fd);
	exit(1);
}

void	error_notplayable(char *str, char **temp, t_data *data)
{
	int	y;

	y = 0;
	write(1, str, ft_strlen(str));
	while (data->map->map1 && data->map->map1[y])
		free(data->map->map1[y++]);
	free(data->map->map1);
	y = 0;
	while (temp && temp[y])
		free(temp[y++]);
	free(temp);
	exit(1);
}
