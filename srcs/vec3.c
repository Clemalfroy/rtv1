/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:55:59 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/13 17:56:22 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline t_vec3	ft_vec3(float x, float y, float z)
{
	return ((t_vec3){.x = x, .y = y, .z = z});
}

inline t_vec3	ft_vec3_add(t_vec3 a, t_vec3 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

inline t_vec3	ft_vec3_sub(t_vec3 a, t_vec3 b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return (a);
}

inline t_vec3	ft_vec3_mul(t_vec3 a, t_vec3 b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return (a);
}

inline t_vec3	ft_vec3_div(t_vec3 a, t_vec3 b)
{
	a.x /= b.x;
	a.y /= b.y;
	a.z /= b.z;
	return (a);
}

inline t_vec3	ft_vec3_cross(t_vec3 a, t_vec3 b)
{
	return (ft_vec3(a.y * b.z - b.y * a.z, a.x * b.z - a.z * b.x, a.x * b.y -
				a.y * b.x));
}
