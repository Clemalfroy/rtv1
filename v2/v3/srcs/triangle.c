/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 17:27:38 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/16 18:15:11 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline void		ft_triangle_cnstr(t_triangle *t, t_vec3 a, t_vec3 b, t_vec3 c)
{
	t->a = a;
	t->b = b;
	t->c = c;
}

t_vec3			triangle_calculate_normal(t_triangle *t, int *shininess,
		t_vec3 *specularcolor)
{
	*shininess = 128;
	*specularcolor = ft_vec3(0.7, 0.7, 0.7);
	return (ft_vec3_add(ft_vec3_add(ft_vec3_times(ft_vec3_nor(t->a), t->w),
					ft_vec3_times(ft_vec3_nor(t->b), t->u)),
				ft_vec3_times(ft_vec3_nor(t->c), t->v)));
}

void			shape_assoc_triangle(t_shape *shape, t_triangle triangle, t_vec3 color)
{
	shape->shape.t = triangle;
	shape->kind = SHAPE_TRIANGLE;
	shape->color = color;
}

int			ray_triangle_intersect(t_triangle *triangle, t_vec3 ray_direction, t_vec3 ray_origin, double *t)
{
	t_vec3 e1;
	t_vec3 e2;
	double new_lgth;

	e1 = ft_vec3_sub(triangle->b, triangle->a);
	e2 = ft_vec3_sub(triangle->c, triangle->a);
	triangle->u = ft_vec3_dot(ft_vec3_sub(ray_origin, triangle->a),
	ft_vec3_divnb(ft_vec3_cross(ray_direction, e2),
	ft_vec3_dot(e1, ft_vec3_cross(ray_direction, e2))));
	triangle->v = ft_vec3_dot(ray_direction, ft_vec3_divnb(ft_vec3_cross(ft_vec3_sub
	(ray_origin, triangle->a), e1), ft_vec3_dot(e1, ft_vec3_cross
	(ray_direction, e2))));
	triangle->w = 1 - triangle->u - triangle->v;
	if (triangle->u < 0 || triangle->u > 1)
		return (0);
	if (triangle->v < 0 || triangle->u + triangle->v > 1)
		return (0);
	new_lgth = ft_vec3_dot(e2, ft_vec3_divnb(ft_vec3_cross(ft_vec3_sub
	(ray_origin, triangle->a), e1), ft_vec3_dot
	(e1, ft_vec3_cross(ray_direction, e2))));
	*t = new_lgth;
	return (1);
}
