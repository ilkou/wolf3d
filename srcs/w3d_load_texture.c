#include <wolf3d.h>

int				w3d_load_texture(t_wolf3d *p)
{
	char	*filename;
	int	width[TOTAL_TXT];
	int	height[TOTAL_TXT];
	int	i;

	i = -1;
	while (++i < TOTAL_TXT)
	{
		filename = ft_mystrjoin("xpm/", ft_mystrjoin(ft_itoa(i), ".xpm", 0), 1);
		p->txt.img[i] = mlx_xpm_file_to_image (p->mlx, filename, &width[i], &height[i]);
		free(filename);
	}
	while (--i >= 0)
		if (!p->txt.img[i] || width[i] != 64 || height[i] != 64)
			return (-1);
	i = -1;
	while (++i < TOTAL_TXT)
		p->txt.buf[i] = (int *)mlx_get_data_addr(p->txt.img[i], &p->bpp, &p->size_line, &p->endian);
	return (1);
}
