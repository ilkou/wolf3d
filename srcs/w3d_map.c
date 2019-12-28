
#include <wolf3d.h>

static int	w3d_free(char ***split, char **line, int **map, int fd)
{
    int i;
    char **f_split;

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

int		w3d_map(t_wolf3d *p, char *file, int i, int j)
{
    char	**split;
    char	*line;
    int	len;
    int	fd;

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
	if (!(p->map = (int *)ft_realloc((void*)(&p->map), sizeof(int) * p->h_map * p->w_map,
			sizeof(int) * ((p->h_map + 1 ) * p->w_map))))
	    return (w3d_free(&split, &line, &p->map, fd));
	while (++j < len)
	    p->map[p->h_map * p->w_map + j] = ft_atoi(split[j]);
	ft_free_twodim(&split);
	free(line);
	p->h_map++;
    }
    close(fd);
    return (1);
}
