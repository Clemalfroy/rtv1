/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:33:55 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/13 15:41:17 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	average(float *r, float *tab)
{
	r[0] += ft_clamp(tab[0], 0.0, 1.0);
	r[1] += ft_clamp(tab[1], 0.0, 1.0);
	r[2] += ft_clamp(tab[2], 0.0, 1.0);
}

static void	setray(t_env *env, float *tab, double x, double y)
{
	double	u;
	double	v;

	u = (WTH - (double)x * 2.0) / HGT;
	v = (HGT - (double)y * 2.0) / WTH;
	env->k = vec3_sub(&env->cam.dir, &env->cam.pos);
	vec3_norm(&env->k);
	env->i = vec3_cross(&env->k, &(t_vec3){0.0, 1.0, 0.0});
	vec3_norm(&env->i);
	env->j = vec3_cross(&env->i, &env->k);
	env->raydir = (t_vec3){(u * env->i.x + v * env->j.x + FOV *
		env->k.x), (u * env->i.y + v * env->j.y + FOV * env->k.y),
		(u * env->i.z + v * env->j.z + FOV * env->k.z)};
	vec3_norm(&env->raydir);
	ft_fzero(tab, 4);
}

static inline void	raytrace(t_env *env, double x, double y)
{
	float	tab[4];
	float 	r[3];
	double  p;
	int 	nb;

	ft_fzero(r, 3);
	p = 0.0;
	while (y < env->ty + 1 && (x = env->tx) > -1)
	{
		while(x < env->tx + 1 && (p += 1) > 0)
		{
			setray(env, tab, x, y);
			if ((nb = intersect(env, env->raydir, env->cam.pos)) >= 0)
				lambertlight(env, nb, tab);
			average(r, tab);
			x += (1.0 / env->antialias);
		}
		y += (1.0 / env->antialias);
	}
	putpixel(env, env->tx, env->ty, (((int)(r[0] / p * 255) & 0xff) << 16) +
		(((int)(r[1] / p * 255) & 0xff) << 8) + ((int)(r[2] / p * 255) & 0xff));
}

static inline void	mthrd_process(t_thread *thrd)
{
	double 		x;
	double 		y;

	y = 0.0;
	while (y < HGT)
	{
		x = WTH * thrd->i / THREADS;
		while (x < WTH * (thrd->i + 1) / THREADS)
		{
			thrd->env.tx = (int)x;
			thrd->env.ty = (int)y;
			raytrace(&thrd->env, x++, y);
		}
		y++;
	}
	pthread_exit(NULL);
}

inline int 		draw(t_env *env)
{
	pthread_t	th[THREADS];
	t_thread	tab[THREADS];
	int 		i;

	i = -1;
	mlx_destroy_image(env->mlx.mlx, env->img.img);
	mlx_clear_window(env->mlx.mlx, env->mlx.win);
	env->img.img = mlx_new_image(env->mlx.mlx, WTH, HGT);
	while (++i < THREADS)
	{
		tab[i].i = i;
		ft_memcpy(&tab[i].env, env, sizeof(t_env));
		pthread_create(th + i, NULL, (void *(*)(void *))mthrd_process, tab + i);
	}
	while (i--)
		pthread_join(th[i], NULL);
	mlx_put_image_to_window(env->mlx.mlx, env->mlx.win, env->img.img, 0, 0);
	mlx_hud(env);
	return (1);
}