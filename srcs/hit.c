/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 15:13:46 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/17 16:36:52 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rt.h"

inline int			rt_hitcone(t_shape obj, t_ray ray, double *t)
{
	double	t1;
	double	t2;

	if (rt_solveconquadra(obj, ray, &t1, &t2))
	{
		if (t1 > EPSILON)
			*t = t1;
		else if (t2 > EPSILON)
			*t = t2;
		else
			return (0);
		return (1);
	}
	return (0);
}

inline int			rt_hitsphere(t_shape obj, t_ray ray, double *t)
{
	double	t1;
	double	t2;

	if (rt_solvesphquadra(obj, ray, &t1, &t2))
	{
		if (t1 > EPSILON)
			*t = t1;
		else if (t2 > EPSILON)
			*t = t2;
		else
			return (0);
		return (1);
	}
	return (0);
}

inline int			rt_hitcylinder(t_shape obj, t_ray ray, double *t)
{
	double	t1;
	double	t2;

	if (rt_solvecylquadra(obj, ray, &t1, &t2))
	{
		if (t1 > EPSILON)
			*t = t1;
		else if (t2 > EPSILON)
			*t = t2;
		else
			return (0);
		return (1);
	}
	return (0);
}

inline int			rt_hitplane(t_shape obj, t_ray ray, double *t)
{
	t_vec3	v;
	double	d;
	double	res;

	if (obj.rot.ex)
	{
		ray.pos = rotate(ray.pos, obj.inv);
		ray.dir = rotate(ray.dir, obj.inv);
	}
	d = vec3_scale(ray.dir, obj.norm);
	if (d)
	{
		v = vec3_sub(obj.center, ray.pos);
		res = vec3_scale(v, obj.norm);
		res /= d;
		if (res > 0)
		{
			*t = res;
			return (1);
		}
		return (0);
	}
	return (0);
}