#ifndef WOLF3D_H
# define WOLF3D_H

# define WIDTH 800
# define HEIGHT 800

# define NBTHREAD 4

#if defined(__APPLE__)
# include <key_macos.h>
#else
# include <key_linux.h>
#endif

#include <mlx.h>
#include <pthread.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libft.h>

typedef struct			s_vec2d
{
	float			x;
	float			y;
}				t_vec2d;

typedef struct			s_wolf3d
{
	t_vec2d			pos;
	t_vec2d			dir;
	t_vec2d			plane;
	char			*map;
	int			w_map;
	int			h_map;
	void			*win;
	void			*img;
	void			*mlx;
	int			*pixels;
	int			bpp;
	int			size_line;
	int			endian;
}				t_wolf3d;

typedef struct			s_thread
{
	t_wolf3d		*w;
	t_vec2d			pos;
	t_vec2d			dir;
	t_vec2d			plane;
	int			x_x;
}				t_thread;

/*
 * to delete
*/

void	print_map(t_wolf3d *p);

/*
 * prototypes
*/

int				w3d_map(t_wolf3d *p, char *file, int i, int j);
int				w3d_putpixel(int *data, int x, int y, int color);
int				w3d_close(t_wolf3d *p);
int				w3d_keys(int k, t_wolf3d *p);
int				w3d_draw(t_wolf3d *p);

void				w3d_thread(t_wolf3d *p);

#endif
