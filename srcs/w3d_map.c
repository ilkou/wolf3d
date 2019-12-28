/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 21:52:58 by oouklich          #+#    #+#             */
/*   Updated: 2019/12/28 23:17:54 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static int	w3d_free(char ***split, char **line, int **map, int fd)
{
	int		i;
	char	**f_split;

	i = 0;
	f_split = *split;
	while (f_split[i])
	{
		free(f_split[i]);
		f_split[i] = NULL;
		i++;
	}
	if (*line)
		free(*line);
	*line = NULL;
	if (*map)
		free(*map);
	*map = NULL;
	close(fd);
	return (-1);
}

static void	w3d_set_square(t_wolf3d *p, char **split, int j)
{
	int		square;

	square = ft_atoi(split[j]);
	if (square == 0 && p->pos.x == -1.0)
	{
		p->pos.x = j + 0.2;
		p->pos.y = p->h_map + 0.2;
	}
	p->map[p->h_map * p->w_map + j] = square;
}

int			w3d_map(t_wolf3d *p, char *file, int i, int j)
{
	char	**split;
	char	*line;
	int		len;
	int		fd;

	p->map = NULL;
	if ((fd = open(file, O_RDONLY)) == -1 || read(fd, line, 0) < 0)
		return (-1);
	while (get_next_line(fd, &line) > 0 && (j = -1))
	{
		split = ft_strsplit(line, ' ');
		len = ft_twodimlen(split);
		p->w_map = p->h_map == 0 ? len : p->w_map;
		if (p->w_map != len)
			return (w3d_free(&split, &line, &p->map, fd));
		if (!(p->map = (int*)ft_realloc((void*)(&p->map), sizeof(int) * p->h_map
						* p->w_map, sizeof(int) * (p->h_map + 1) * p->w_map)))
			return (w3d_free(&split, &line, &p->map, fd));
		while (++j < len)
			w3d_set_square(p, split, j);
		ft_free_twodim(&split);
		free(line);
		p->h_map++;
	}
	return (close(fd));
}
