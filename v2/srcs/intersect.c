/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:14:11 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/14 10:34:38 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			ray_sphere_intersect(t_sphere *sphere, t_ray *ray)
{
	t_vec3 orgn_to_sph;
	double projection;
	t_vec3 dst_vec;
	double dst_sq;
	double radius_sq;
	double new_lgth;

	orgn_to_sph = ft_vec3_sub(sphere->center, ray->origin);
	projection = ft_vec3_dot(orgn_to_sph, ray->direction);
	dst_vec = ft_vec3_sub(orgn_to_sph, ft_vec3_times(ray->direction, projection));
	dst_sq = ft_vec3_dot(orgn_to_sph, dst_vec);
	radius_sq = sphere->radius * sphere->radius;
	if (dst_sq > radius_sq)
		return (0);
	new_lgth = projection - sqrtf(radius_sq - dst_sq);
	if (new_lgth < ray->length && new_lgth > 0.0f)
	{
		ray->length = new_lgth;
		return (1);
	}
	return (0);
}

int			ray_plane_intersect(t_plane *plane, t_ray *ray)
{
	double	dst_sq;
	double	new_lgth; 

	dst_sq = ft_vec3_dot(ray->direction, plane->normal);
	if (ABS(dst_sq) < 1e-6)
		return (0);
	new_lgth = ft_vec3_dot(ft_vec3_sub(plane->position, ray->origin),
			plane->normal) / dst_sq;
	ray->length = new_lgth;
	if (new_lgth >= 0)
		return (1);
	return (0);
}

int			ray_triangle_intersect(t_triangle *triangle, t_ray *ray)
{
	t_vec3 e1;
	t_vec3 e2;
	double u;
	double v;
	double new_lgth;

	e1 = ft_vec3_sub(triangle->a, triangle->b);
	e2 = ft_vec3_sub(triangle->c, triangle->a);
	u = ft_vec3_dot(ray->direction, ft_vec3_divnb(ft_vec3_cross(ray->direction, e2), ft_vec3_dot(e1, ft_vec3_cross(ray->direction, e2))));
	v = ft_vec3_dot(ray->origin, ft_vec3_divnb(ft_vec3_cross(ft_vec3_sub(ray->origin, triangle->a), e1), ft_vec3_dot(e1, ft_vec3_cross(ray->direction, e2))));
	if (u < 0 || u > 1)
		return (0);
	if (v < 0 || u + v > 1)
		return (0);
	new_lgth = ft_vec3_dot(e2, ft_vec3_divnb(ft_vec3_cross(ft_vec3_sub(ray->origin, triangle->a), e1), ft_vec3_dot(e1, ft_vec3_cross(ray->direction, e2))));
	ray->length = new_lgth;
	return (1);
}
