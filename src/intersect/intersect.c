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

inline double	intersphere(t_env *e, t_obj *tmp, t_vec3 r, t_vec3 pos)
{
	double disc;

	e->dist = vec3_sub(&pos, &tmp->pos);
	e->a = vec3_dot(&r, &r);
	e->b = 2 * vec3_dot(&r, &e->dist);
	e->c = vec3_dot(&e->dist, &e->dist) - (tmp->size * tmp->size);
	disc = e->b * e->b - 4 * e->a * e->c;
	if (disc < 0)
		return (-1);
	e->t0 = (-e->b + sqrtf(disc)) / (2 * e->a);
	e->t1 = (-e->b - sqrtf(disc)) / (2 * e->a);
	if (e->t0 > e->t1)
		e->t0 = e->t1;
	return (e->t0);
}

inline double	intercylinder(t_env *env, t_obj *tmp, t_vec3 ray, t_vec3 pos)
{
	double disc;

	env->dist = vec3_sub(&pos, &tmp->pos);
	vec3_norm(&tmp->rot);
	env->a = vec3_dot(&ray, &ray) - pow(vec3_dot(&ray, &tmp->rot), 2);
	env->b = 2 * (vec3_dot(&ray, &env->dist) -
		(vec3_dot(&ray, &tmp->rot) * vec3_dot(&env->dist, &tmp->rot)));
	env->c = vec3_dot(&env->dist, &env->dist) -
		pow(vec3_dot(&env->dist, &tmp->rot), 2) - pow(tmp->size, 2);
	disc = env->b * env->b - 4 * env->a * env->c;
	if (disc < 0)
		return (-1);
	env->t0 = (-env->b + sqrtf(disc)) / (2 * env->a);
	env->t1 = (-env->b - sqrtf(disc)) / (2 * env->a);
	if (env->t0 > env->t1)
		env->t0 = env->t1;
	return (env->t0);
}

inline double	intercone(t_env *env, t_obj *tmp, t_vec3 ray, t_vec3 pos)
{
	double	disc;

	env->dist = vec3_sub(&pos, &tmp->pos);
	vec3_norm(&tmp->rot);
	env->a = (vec3_dot(&ray, &ray) - (1 + pow(tan(tmp->size), 2)) *
		pow(vec3_dot(&ray, &tmp->rot), 2));
	env->b = 2 * (vec3_dot(&ray, &env->dist) - (1 + pow(tan(tmp->size), 2))
		* vec3_dot(&ray, &tmp->rot) * vec3_dot(&env->dist, &tmp->rot));
	env->c = vec3_dot(&env->dist, &env->dist) - (1 +
		pow(tan(tmp->size), 2)) * pow(vec3_dot(&env->dist, &tmp->rot), 2);
	disc = env->b * env->b - 4 * env->a * env->c;
	if (disc < 0)
		return (-1);
	env->t0 = (-env->b + sqrtf(disc)) / (2 * env->a);
	env->t1 = (-env->b - sqrtf(disc)) / (2 * env->a);
	if (env->t0 > env->t1)
		env->t0 = env->t1;
	return (env->t0);
}

inline double	interplane(t_env *env, t_obj *tmp, t_vec3 ray, t_vec3 pos)
{
	env->t0 = ((vec3_dot(&tmp->rot, &tmp->pos) -
		vec3_dot(&tmp->rot, &pos)) / vec3_dot(&tmp->rot, &ray));
	if (env->t0 < 0.0001)
		return (-1);
	return (env->t0);
}

inline int intersect(t_env *env, t_vec3 ray, t_vec3 pos)
{
	int 	hit;
	double	dist;
	t_obj	*obj;
	int 	curobj;

	hit = -1;
	curobj = -1;
	env->t = 80000.0;
	while (++curobj < env->nbobj)
	{
		obj = &env->obj[curobj];
		if (obj->type == SHAPE_CONE)
			dist = intercone(env, obj, ray, pos);
		else if (obj->type == SHAPE_CYLINDER)
			dist = intercylinder(env, obj, ray, pos);
		else if (obj->type == SHAPE_PLANE)
			dist = interplane(env, obj, ray, pos);
		else if (obj->type == SHAPE_SPHERE)
			dist = intersphere(env, obj, ray, pos);
		else if (obj->type == SHAPE_LIGHT)
			continue;
		if (dist > 0.0001 && dist < env->t)
		{
			hit = curobj;
			env->t = (float)dist;
		}
	}
	return (hit);
}