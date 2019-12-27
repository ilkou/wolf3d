
#include <wolf3d.h>

int	w3d_map(t_wolf3d *p, char *file, int i, int j)
{
	char	**split;
	char	*line;
	int	len;
	int	fd;

	if ((fd = open(file, O_RDONLY)) == -1 || read(fd, line, 0) < 0)
		return (-1);
	p->map = NULL;
	while (get_next_line(fd, &line) > 0 && (j = -1))
	{
		split = ft_strsplit(line, ' ');
		len = ft_twodimlen(split);
		p->w_map = p->h_map == 0 ? len : p->w_map;
		if (p->w_map != len)
			return (-1);
		if (!(p->map = (char *)ft_realloc((void*)(&p->map), sizeof(char) * p->h_map * p->w_map, sizeof(char) * ((p->h_map + 1 ) * p->w_map))))
			return (-1);
		while (++j < len)
			p->map[p->h_map * p->w_map + j] = split[j][0];
		ft_free_twodim(&split);
		free(line);
		p->h_map++;
	}
	return (1);
}
