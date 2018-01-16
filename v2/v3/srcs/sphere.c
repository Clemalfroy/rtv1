/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:10:52 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/16 18:51:16 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline void		ft_sphere_cnstr(t_sphere *self, t_vec3 center, double radius)
{
	self->center = center;
	self->radius = radius;
}

t_vec3			sphere_calculate_normal(t_sphere *s, t_vec3 p0, int* shininess,
		t_vec3 *specularcolor)
{
	*shininess = 128;
	*specularcolor = ft_vec3(0.7, 0.7, 0.7);
	return (ft_vec3_sub(p0, s->center));
}

void			shape_assoc_sphere(t_shape *shape, t_sphere sphere, t_vec3 color)
{
	shape->shape.s = sphere;
	shape->kind = SHAPE_SPHERE;
	shape->color = color;
}

int			ray_sphere_intersect(t_sphere *sphere, t_vec3 ray_origin, t_vec3 ray_direction, double *t)
{
	t_vec3 l = ft_vec3_sub(sphere->center, ray_origin);
	double tca = ft_vec3_dot(l, ray_direction);
	if (tca < 0)
		return (0);
	else
	{
		double s2 = (ft_vec3_dot(l ,l) - (tca * tca));
		double s = sqrt(s2);
		if (s > sphere->radius)
			return (0);
		else
		{
			double thc = sqrt((sphere->radius * sphere->radius) - s2);
			double t0 = tca - thc;
			*t = t0;
			return (1);
		}
	}
}

