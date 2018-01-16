/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 17:24:34 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/16 16:21:01 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline void		ft_plane_cnstr(t_plane *plane, t_vec3 pos, t_vec3 norm)
{
	plane->position = pos;
	plane->normal = norm;
}

t_vec3			plane_calculate_normal(t_plane *plane, int *shininess,
		t_vec3 *specularcolor, t_vec3 color)
{
	*shininess = 0;
	*specularcolor = color;
	return (plane->normal);
}

void			shape_assoc_plane(t_shape *shape, t_plane plane, t_vec3 color)
{
	shape->shape.p = plane;
	shape->kind = SHAPE_PLANE;
	shape->color = color;
}

int			ray_plane_intersect(t_plane *plane, t_vec3 ray_origin, t_vec3 ray_direction, double *t)
{
	double	dst_sq;
	double	new_lgth; 

	dst_sq = ft_vec3_dot(ray_direction, plane->normal);
	if (ABS(dst_sq) < 1e-6)
		return (0);
	new_lgth = ft_vec3_dot(ft_vec3_sub(plane->position, ray_origin),
			plane->normal) / dst_sq;
	*t = new_lgth;
	if (new_lgth >= 0)
		return (1);
	return (0);
}

