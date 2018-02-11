/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:19:35 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/16 16:41:36 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

inline double	rt_interspher(t_env *e, t_obj *tmp, t_v3 r, t_v3 pos)
{
	double disc;

	e->dist = ft_v3sub(pos, tmp->pos);
	e->a = ft_v3dot(r, r);
	e->b = 2 * ft_v3dot(r, e->dist);
	e->c = ft_v3dot(e->dist, e->dist) - (tmp->size * tmp->size);
	disc = e->b * e->b - 4 * e->a * e->c;
	if (disc < 0)
		return (-1);
	e->t0 = (-e->b + sqrtf((float)disc)) / (2 * e->a);
	e->t1 = (-e->b - sqrtf((float)disc)) / (2 * e->a);
	if (e->t0 > e->t1)
		e->t0 = e->t1;
	return (e->t0);
}

inline double	rt_intercyl(t_env *env, t_obj *tmp, t_v3 ray, t_v3 pos)
{
	double disc;

	env->dist = ft_v3sub(pos, tmp->pos);
	tmp->rot = ft_v3nor(tmp->rot);
	env->a = (float)(ft_v3dot(ray, ray) - pow(ft_v3dot(ray, tmp->rot), 2));
	env->b = 2 * (ft_v3dot(ray, env->dist) -
		(ft_v3dot(ray, tmp->rot) * ft_v3dot(env->dist, tmp->rot)));
	env->c = (float)(ft_v3dot(env->dist, env->dist) - pow(ft_v3dot(env->dist,
		tmp->rot), 2) - pow(tmp->size, 2));
	disc = env->b * env->b - 4 * env->a * env->c;
	if (disc < 0)
		return (-1);
	env->t0 = (-env->b + sqrtf((float)disc)) / (2 * env->a);
	env->t1 = (-env->b - sqrtf((float)disc)) / (2 * env->a);
	if (env->t0 > env->t1)
		env->t0 = env->t1;
	return (env->t0);
}

inline double	rt_intercone(t_env *env, t_obj *tmp, t_v3 ray, t_v3 pos)
{
	double	disc;

	env->dist = ft_v3sub(pos, tmp->pos);
	tmp->rot = ft_v3nor(tmp->rot);
	env->a = (float)(ft_v3dot(ray, ray) - (1 + pow(tanf(tmp->size),
		2)) * pow(ft_v3dot(ray, tmp->rot), 2));
	env->b = (float)(2 * (ft_v3dot(ray, env->dist) - (1 + pow(tanf(tmp->size),
		2)) * ft_v3dot(ray, tmp->rot) * ft_v3dot(env->dist, tmp->rot)));
	env->c = (float)(ft_v3dot(env->dist, env->dist) - (1 + pow(tanf(tmp->size),
		2)) * pow(ft_v3dot(env->dist, tmp->rot), 2));
	disc = env->b * env->b - 4 * env->a * env->c;
	if (disc < 0)
		return (-1);
	env->t0 = (-env->b + sqrtf((float)disc)) / (2 * env->a);
	env->t1 = (-env->b - sqrtf((float)disc)) / (2 * env->a);
	if (env->t0 > env->t1)
		env->t0 = env->t1;
	return (env->t0);
}

inline double	rt_interplane(t_env *env, t_obj *tmp, t_v3 ray, t_v3 pos)
{
	float a;

	if ((a = ft_v3dot(tmp->rot, ray)) != 0)
		env->t0 = ((ft_v3dot(tmp->rot, tmp->pos) -
			ft_v3dot(tmp->rot, pos)) / a);
	else
		return (-1);
	if (env->t0 < 0.0001)
		return (-1);
	return (env->t0);
}

inline int		rt_intersect(t_env *env, t_v3 ray, t_v3 pos)
{
	int		hit;
	double	dist;
	t_obj	*obj;
	int		it;

	hit = -1;
	it = -1;
	env->t = 80000.0;
	while (++it < env->nbobj)
	{
		obj = &env->obj[it];
		if (obj->type == SHAPE_CONE)
			dist = rt_intercone(env, obj, ray, pos);
		else if (obj->type == SHAPE_CYLINDER)
			dist = rt_intercyl(env, obj, ray, pos);
		else if (obj->type == SHAPE_PLANE)
			dist = rt_interplane(env, obj, ray, pos);
		else if (obj->type == SHAPE_SPHERE)
			dist = rt_interspher(env, obj, ray, pos);
		else if (obj->type == SHAPE_LIGHT)
			continue;
		if (dist > 0.0001 && dist < env->t && (env->t = (float)dist))
			hit = it;
	}
	return (hit);
}
