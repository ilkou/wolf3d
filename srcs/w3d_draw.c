
#include <wolf3d.h>

int		w3d_putpixel(int *pixels, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixels[y * WIDTH + x] = color;
		return (1);
	}
	return (-1);
}

int		w3d_darker(int color, float ratio)
{
	int	r;
	int	g;
	int	b;

	r = (int)((color >> 16 & 0xFF) * ratio);
	g = (int)((color >> 8 & 0xFF) * ratio);
	b = (int)((color & 0xFF) * ratio);
	return (r << 16 | g << 8 | b);
}

void		*w3d_raycaster(t_thread *p)
{
	int	x;

	x = (p->x_x * WIDTH / NBTHREAD) - 1;
	while (++x < (p->x_x + 1) * WIDTH / NBTHREAD)
	{
		double cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = p->dir.x + p->plane.x * cameraX;
		double rayDirY = p->dir.y + p->plane.y * cameraX;
		//which box of the map we're in
		int mapX = (int)p->pos.x;
		int mapY = (int)p->pos.y;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (p->pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - p->pos.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (p->pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - p->pos.y) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = p->pos.x < (double)mapX ? OUEST : EST;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = p->pos.y < (double)mapY ? NORD : SUD;
			}
			//Check if ray has hit a wall
			if (p->w->map[mapX + p->w->w_map * mapY] != '0') hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == OUEST || side == EST) perpWallDist = (mapX - p->pos.x + (1 - stepX) / 2) / rayDirX;
		else           perpWallDist = (mapY - p->pos.y + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(HEIGHT / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		drawStart = (drawStart < 0) ? 0 : drawStart;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		drawEnd = (drawEnd >= HEIGHT) ? HEIGHT - 1 : drawEnd;

		//choose wall color
		int color;
		switch(p->w->map[mapX + p->w->w_map * mapY])
		{
			case '1':  color = 0xFF0000; break; //red
			case '2':  color = 0x00FF00; break; //green
			case '3':  color = 0x0000FF; break; //blue
			case '4':  color = 0xFFFFFF; break; //white
			default: color = 0xFFFF00; break; //yellow
		}

		//give x and y sides different brightness
		if (side == NORD)
			color = w3d_darker(color, 0.75);
		else if (side == SUD)
			color = w3d_darker(color, 0.75);
		else if (side == OUEST)
			color = w3d_darker(color, 0.5);

		//draw the pixels of the stripe as a vertical line
		int sky;
		if (drawStart > 0) {
			sky = rand() % drawStart;
			w3d_putpixel(p->w->pixels, x, sky, 0xFFFFFF);
		}
		for (int y = drawStart; y < drawEnd; y++) {
			w3d_putpixel(p->w->pixels, x, y, color);
		}
		if (drawEnd < HEIGHT)
			for (int y = drawEnd; y < HEIGHT; y++) {
				w3d_putpixel(p->w->pixels, x, y, 0x123456);
			}
	}
	pthread_exit(NULL);
}

void		w3d_thread(t_wolf3d *w)
{
	t_thread	t[NBTHREAD];
	pthread_t	p[NBTHREAD];
	int		i;

	i = -1;
	while (++i < NBTHREAD)
	{
		t[i].x_x = i;
		t[i].w = w;
		t[i].pos = w->pos;
		t[i].dir = w->dir;
		t[i].plane = w->plane;
		pthread_create(&p[i], NULL, (void*)w3d_raycaster, &t[i]);
	}
	while (--i >= 0)
		pthread_join(p[i], NULL);
}

int		w3d_draw(t_wolf3d *p)
{
	bzero(p->pixels, WIDTH * HEIGHT * 4);
	w3d_thread(p);
	mlx_clear_window (p->mlx, p->win);
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
	return (1);
}
