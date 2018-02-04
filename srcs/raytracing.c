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

static void	ft_hit_objects(t_env *env)
{
	double	t;

	t = 1 / EPSILON;
	while (++env->current < env->nbobj)
	{
		if (env->obj[env->current].type == 1)
			ft_hit_sphere(env->obj[env->current], env->ray, &t);
		else if (env->obj[env->current].type == 2)
			ft_hit_cylinder(env->obj[env->current], env->ray, &t);
		else if (env->obj[env->current].type == 3)
			ft_hit_cone(env->obj[env->current], env->ray, &t);
		else if (env->obj[env->current].type == 4)
			ft_hit_plane(env->obj[env->current], env->ray, &t);
		if (env->tmin > t)
		{
			env->hit = 1;
			env->tmin = t;
			env->last = env->current;
		}
	}
}

inline static void	ft_intersect(t_env *env, int x, int y)
{
	env->hit = 0;
	env->current = -1;
	ft_hit_objects(env);
	if (env->hit)
		ft_put_pixel(env, x, y, ft_color(env->obj[env->last].color));
}

inline static void	ft_init_ray(t_env *env, int x, int y)
{
	t_vec3	dir;

	env->ray.pos = env->cam.pos;
	dir.x = (x + 0.5) / WTH;
	dir.y = (y + 0.5) / HGT;
	dir.x = (2 * dir.x) - 1;
	dir.y = 1 - (2 * dir.y);
	dir.x *= (WTH / (double)HGT) * tan((env->fov / 2) * PI / 180);
	dir.y *= tan((env->fov / 2) * PI / 180);
	dir.z = 1;
	if (env->cam.mat.ex)
		env->ray.dir = ft_rotate_cam(dir, env->cam.mat);
	else
		env->ray.dir = dir;
}

static inline void	*scanscreen(t_thread *thrd)
{
	int		x;

	while (++thrd->begin < thrd->end)
	{
		x = -1;
		while (++x < WTH)
		{
			thrd->env.tmin = 1 / EPSILON;
			ft_init_ray(&thrd->env, x, thrd->begin);
			ft_intersect(&thrd->env, x, thrd->begin);
		}
	}
	pthread_exit(NULL);
}

inline void			compute(t_env *env)
{
		pthread_t	t[THREADS];
		int			i;
		t_thread		o[THREADS];

		i = -1;
		while (++i < THREADS)
		{
			ft_memcpy(&o[i].env, env, sizeof(t_env));
			o[i].begin = (HGT / THREADS) * i;
			o[i].end = (HGT / THREADS) * (i + 1) + 1;
			pthread_create(t + i, NULL, (void *(*)(void *))scanscreen, o + i);
		}
		while (i-- && pthread_join(t[i], NULL) == 0)
			;
}