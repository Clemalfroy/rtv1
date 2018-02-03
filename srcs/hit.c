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

inline int			ft_hit_cone(t_obj obj, t_ray ray, double *t)
{
	double	t1;
	double	t2;

	if (ft_solve_con_quadra(obj, ray, &t1, &t2))
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

inline int			ft_hit_sphere(t_obj obj, t_ray ray, double *t)
{
	double	t1;
	double	t2;

	if (ft_solve_sph_quadra(obj, ray, &t1, &t2))
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

inline int			ft_hit_cylinder(t_obj obj, t_ray ray, double *t)
{
	double	t1;
	double	t2;

	if (ft_solve_cyl_quadra(obj, ray, &t1, &t2))
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

inline int			ft_hit_plane(t_obj obj, t_ray ray, double *t)
{
	t_vec3	v;
	double	d;
	double	res;

	if (obj.rot.ex)
	{
		ray.pos = ft_rotate(ray.pos, obj.inv);
		ray.dir = ft_rotate(ray.dir, obj.inv);
	}
	d = ft_vector_scale(ray.dir, obj.norm);
	if (d)
	{
		v = ft_vector_sub(obj.center, ray.pos);
		res = ft_vector_scale(v, obj.norm);
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