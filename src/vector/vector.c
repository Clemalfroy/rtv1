/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector/vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:33:55 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/13 15:41:17 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3	vec3_scale(t_vec3 *v, float n)
{
	t_vec3	res;

	res.x = v->x * n;
	res.y = v->y * n;
	res.z = v->z * n;
	return (res);
}

t_vec3	vec3_sub(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3	sub;

	sub.x = v1->x - v2->x;
	sub.y = v1->y - v2->y;
	sub.z = v1->z - v2->z;
	return (sub);
}

t_vec3	vec3_cross(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3	v;

	v.x = v1->y * v2->z - v1->z * v2->y;
	v.y = v1->z * v2->x - v1->x * v2->z;
	v.z = v1->x * v2->y - v1->y * v2->x;
	return (v);
}

void	vec3_norm(t_vec3 *v)
{
	double	n;

	n = 1.0 / sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	v->x *= n;
	v->y *= n;
	v->z *= n;
}

float	vec3_dot(t_vec3 *v1, t_vec3 *v2)
{
	float	res;

	res = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
	return (res);
}