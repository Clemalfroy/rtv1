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

static inline void	mthrd_process(t_thread *thrd)
{
	double 		x;
	double 		y;

	y = -1.0;
	while (++y < HGT)
	{
		x = (WTH * (thrd->i / THREADS)) - 1;
		while (++x < WTH * (thrd->i + 1) / THREADS)
		{
			putpixel(thrd->env, (int)x, (int)y, 0x0FFFFFF);
		}
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
		tab[i].env = env;
		pthread_create(th + i, NULL, (void *(*)(void *))mthrd_process, tab + i);
	}
	while (i--)
		pthread_join(th[i], NULL);
	mlx_put_image_to_window(env->mlx.mlx, env->mlx.win, env->img.img, 0, 0);
	mlx_hud(env);
	return (1);
}