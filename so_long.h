/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snegi <snegi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:37:37 by snegi             #+#    #+#             */
/*   Updated: 2024/01/31 12:37:40 by snegi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include "nextline/get_next_line.h"
# include "print/ft_printf.h"

# include <unistd.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define HEIGHT	32
# define WIDTH	32

typedef struct s_image
{
	void	*player_right;
	void	*player_left;
	void	*player_up;
	void	*player_down;
	void	*door;
	void	*wall;
	void	*background;
	void	*heart;
}	t_image;

typedef struct s_mapdata
{
	int		count;
	int		e;
	int		p;
	int		c;
	int		o;
	int		num_nextline;
	char	**map1;
}	t_mapdata;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			size_x;
	int			size_y;
	int			p_x;
	int			p_y;
	int			counter;
	int			collected;
	t_mapdata	*map;
	t_image		*img;
}		t_data;

void	makemap(char **ar, t_mapdata *mapdata, t_data *data);
void	error(char *str, char *next_line, int fd);
void	store_image(t_mapdata *mapdata, t_data *data, t_image *image);
void	create_map(t_data *data);
void	put_background(t_data *data);
int		on_destroy(t_data *data);
int		key_hook(int keycode, t_data *data);
void	check_path(t_data *data);
void	error_notplayable(char *str, char **temp, t_data *data);

#endif
