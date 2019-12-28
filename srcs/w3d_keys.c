
#include <wolf3d.h>

int		w3d_keys(int key, t_wolf3d *p)
{
	t_vec2d next;
    double moveSpeed = 0.25;
    double rotSpeed = 10.0 * M_PI / 180.0;
	if (key == K_ESC)
		w3d_close(p);
	//move forward if no wall in front of you
	if (key == K_AR_U)
	{
		next.x = p->pos.x + p->dir.x * moveSpeed;
		next.y = p->pos.y + p->dir.y * moveSpeed;
		if(p->map[(int)next.x + (int)p->pos.y * p->w_map] == 0 && next.x > 0.00001 && (int)next.x < p->w_map)
			p->pos.x = next.x;
		if(p->map[(int)p->pos.x + p->w_map * (int)next.y] == 0 && next.y > 0.00001 && (int)next.y < p->h_map)
			p->pos.y = next.y;
	}
	//move backwards if no wall behind you
	if (key == K_AR_D)
	{
		next.x = p->pos.x - p->dir.x * moveSpeed;
		next.y = p->pos.y - p->dir.y * moveSpeed;
		if(p->map[(int)next.x + (int)p->pos.y * p->w_map] == 0 && next.x >= 0.00001 && (int)next.x < p->w_map)
			p->pos.x = next.x;
		if(p->map[(int)p->pos.x + p->w_map * (int)next.y] == 0 && next.y >= 0.00001 && (int)next.y < p->h_map)
			p->pos.y = next.y;
	}
	//rotate to the right
    //rotate to the right
    if (key == K_AR_R)
    {
        //both camera direction and camera plane must be rotated
        double oldDirX = p->dir.x;
        p->dir.x = p->dir.x * cos(-rotSpeed) - p->dir.y * sin(-rotSpeed);
        p->dir.y = oldDirX * sin(-rotSpeed) + p->dir.y * cos(-rotSpeed);
        double oldPlaneX = p->plane.x;
        p->plane.x = p->plane.x * cos(-rotSpeed) - p->plane.y * sin(-rotSpeed);
        p->plane.y = oldPlaneX * sin(-rotSpeed) + p->plane.y * cos(-rotSpeed);
    }
    //rotate to the left
    if (key == K_AR_L)
    {
        //both camera direction and camera plane must be rotated
        double oldDirX = p->dir.x;
        p->dir.x = p->dir.x * cos(rotSpeed) - p->dir.y * sin(rotSpeed);
        p->dir.y = oldDirX * sin(rotSpeed) + p->dir.y * cos(rotSpeed);
        double oldPlaneX = p->plane.x;
        p->plane.x = p->plane.x * cos(rotSpeed) - p->plane.y * sin(rotSpeed);
        p->plane.y = oldPlaneX * sin(rotSpeed) + p->plane.y * cos(rotSpeed);
    }
	if (key == K_AR_U || key == K_AR_D || key == K_AR_R || key == K_AR_L)
	    w3d_draw(p);
	return (1);
}
