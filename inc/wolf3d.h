/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 22:17:02 by oouklich          #+#    #+#             */
/*   Updated: 2019/12/29 01:00:54 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define WIDTH 960
# define HEIGHT 600

# define NBTHREAD 4

# define TOTAL_TXT 8
# define WIDTH_TXT 64
# define HEIGHT_TXT 64

# define NORD 0.5
# define SUD 0.5
# define EST 1.0
# define OUEST 0.25

# if defined(__APPLE__)
#  include <key_macos.h>
# else
#  include <key_linux.h>
# endif

# include <mlx.h>
# include <pthread.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <strings.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <libft.h>

typedef enum		e_txt
{
	TXT_0 = 0, TXT_1, TXT_2, TXT_3, TXT_4, TXT_5, TXT_6, TXT_7
}					t_txt;

typedef struct		s_vec2d
{
	float			x;
	float			y;
}					t_vec2d;

typedef struct		s_ivec2d
{
	int				x;
	int				y;
}					t_ivec2d;

typedef struct		s_texture
{
	void			*img[TOTAL_TXT];
	int				*buf[TOTAL_TXT];
}					t_texture;

typedef struct		s_help
{
	t_ivec2d		curr;
	t_ivec2d		step;
	t_vec2d			ray;
	t_vec2d			delta;
	t_vec2d			next;
	double			x_mapped;
	double			dist;
	double			hit_x;
}					t_help;

typedef struct		s_rcast
{
	t_ivec2d		ext;
	t_ivec2d		txt;
	float			side;
	int				txt_idx;
	int				color;
	int				line;
}					t_rcast;

typedef struct		s_wolf3d
{
	t_vec2d			pos;
	t_vec2d			dir;
	t_vec2d			plane;
	t_texture		txt;
	int				*map;
	int				w_map;
	int				h_map;
	void			*win;
	void			*img;
	void			*mlx;
	int				*pixels;
	void			*m_img;
	int				*m_pixels;
	int				bpp;
	int				size_line;
	int				endian;
}					t_wolf3d;

typedef struct		s_thread
{
	t_wolf3d		*w;
	int				x_x;
}					t_thread;

int					w3d_map(t_wolf3d *p, char *file, int i, int j);
int					w3d_close(t_wolf3d *p);
int					w3d_keys(int k, t_wolf3d *p);
int					w3d_draw(t_wolf3d *p);
int					w3d_load_texture(t_wolf3d *p);
void				w3d_thread(t_wolf3d *p);
t_rcast				w3d_raycaster(t_wolf3d *p, int x);

#endif
