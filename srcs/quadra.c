/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadra.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 15:13:46 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/17 16:36:52 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rt.h"

inline int	ft_solve_sph_quadra(t_obj obj, t_ray ray, double *t1, double *t2)
{
	t_vec3	v;
	double	a;
	double	b;
	double	c;
	double	disc;

	v = ft_vector_sub(ray.pos, obj.center);
	a = ft_vector_scale(ray.dir, ray.dir);
	b = 2.0 * ft_vector_scale(ray.dir, v);
	c = ft_vector_scale(v, v) - obj.radius;
	disc = (b * b) - (4.0 * a * c);
	if (disc < 0.0)
		return (0);
	else
	{
		*t1 = (-b - sqrt(disc)) / (2.0 * a);
		*t2 = (-b + sqrt(disc)) / (2.0 * a);
		return (1);
	}
}

inline int	ft_solve_cyl_quadra(t_obj obj, t_ray ray, double *t1, double *t2)
{
	t_vec3	v;
	double	a;
	double	b;
	double	c;
	double	disc;

	if (obj.rot.ex)
		ray = ft_rotate_ray(ray, obj.inv);
	v = ft_vector_sub(ray.pos, obj.center);
	a = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
	b = 2.0 * ray.dir.x * v.x + 2.0 * ray.dir.z * v.z;
	c = (v.x * v.x + v.z * v.z) - obj.radius;
	disc = (b * b) - (4.0 * a * c);
	if (disc < 0.0)
		return (0);
	else
	{
		*t1 = (-b - sqrt(disc)) / (2.0 * a);
		*t2 = (-b + sqrt(disc)) / (2.0 * a);
		return (1);
	}
}

inline int	ft_solve_con_quadra(t_obj obj, t_ray ray, double *t1, double *t2)
{
	t_vec3	v;
	double	a;
	double	b;
	double	c;
	double	disc;

	if (obj.rot.ex)
		ray = ft_rotate_ray(ray, obj.inv);
	v = ft_vector_sub(ray.pos, obj.center);
	a = (ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z)
		- (obj.radius * ray.dir.y * ray.dir.y);
	b = 2.0 * ((ray.dir.x * v.x + ray.dir.z * v.z)
		- (obj.radius * ray.dir.y * v.y));
	c = (v.x * v.x + v.z * v.z) - (obj.radius * v.y * v.y);
	disc = (b * b) - (4.0 * a * c);
	if (disc < 0.0)
		return (0);
	else
	{
		*t1 = (-b - sqrt(disc)) / (2.0 * a);
		*t2 = (-b + sqrt(disc)) / (2.0 * a);
		return (1);
	}
}