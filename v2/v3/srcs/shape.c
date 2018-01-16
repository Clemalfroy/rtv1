/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 14:44:53 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/16 18:12:06 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ray_shape_intersect(t_shape *s, t_vec3 ro, t_vec3 rd, double *t)
{
	if (s->kind == SHAPE_SPHERE)
		return (ray_sphere_intersect(&s->shape.s, ro, rd, t));
	else if (s->kind == SHAPE_PLANE)
		return (ray_plane_intersect(&s->shape.p, ro, rd, t));
	else if (s->kind == SHAPE_TRIANGLE)
		return (ray_triangle_intersect(&s->shape.t, ro, rd, t));
	return (0);
}

t_vec3 shape_calculate_normal(t_shape *s, t_vec3 p0, t_vec3 *spec, int *shi)
{
	if (s->kind == SHAPE_SPHERE)
		return (sphere_calculate_normal(&s->shape.s, p0, shi, spec));
	else if (s->kind == SHAPE_TRIANGLE)
		return (triangle_calculate_normal(&s->shape.t, shi, spec));
	else if (s->kind == SHAPE_PLANE)
		return (plane_calculate_normal(&s->shape.p, shi, spec, s->color));
	exit(1);
}
