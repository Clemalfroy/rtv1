/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_nor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 15:03:21 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/12 16:45:49 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline float	ft_vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline float	ft_vec3_len(t_vec3 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

inline float	ft_vec3_ang(t_vec3 a, t_vec3 b)
{
	return (acosf(ft_vec3_dot(a, b) / (ft_vec3_len(a) * ft_vec3_len(b))));
}

inline t_vec3	ft_vec3_nor(t_vec3 v)
{
	float len;

	if ((len = ft_vec3_len(v)) > 0)
		return (ft_vec3(v.x / len, v.y / len, v.z / len));
	return (ft_vec3(0, 0, 0));
}
