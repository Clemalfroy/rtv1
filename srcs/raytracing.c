/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:33:55 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/13 15:41:17 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline static void	ft_intersect(t_env *env, int x, int y)
{
	ft_put_pixel(env, x, y, 0x0FFFFFF);
}

inline static void	ft_init_ray(t_env *env, int x, int y)
{
	t_vec3	v;

	env->ray.pos = env->cam.pos;
	v.x = (x + 0.5) / WTH;
	v.y = (y + 0.5) / HGT;
	v.x = (2 * v.x) - 1;
	v.y = 1 - (2 * v.y);
	v.x *= (WTH / (double)HGT) * tan((env->fov / 2) * PI / 180);
	v.y *= tan((env->fov / 2) * PI / 180);
	v.z = 1;
	if (env->cam.mat.ex)
		env->ray.dir = ft_rotate_cam(v, env->cam.mat);
	else
		env->ray.dir = v;
}

static inline void	*scanscreen(t_param *p)
{
	int		x;

	while (++p->begin < p->end)
	{
		x = -1;
		while (++x < WTH)
		{
			p->env->tmin = 1 / EPSILON;
			ft_init_ray(p->env, x, p->begin);
			ft_intersect(p->env, x, p->begin);
		}
	}
	pthread_exit(NULL);
}

inline void			compute(t_env *env)
{
		pthread_t	t[THREADS];
		int			i;
		t_param		o[THREADS];

		i = -1;
		while (++i < THREADS)
		{
			o[i].env = env;
			o[i].begin = (HGT / THREADS) * i;
			o[i].end = (HGT / THREADS) * (i + 1) + 1;
			pthread_create(t + i, NULL, (void *(*)(void *))scanscreen, o + i);
		}
		while (i-- && pthread_join(t[i], NULL) == 0)
			;
}