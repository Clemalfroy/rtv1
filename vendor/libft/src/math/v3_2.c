/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v3_nor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 10:43:47 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/math/v3.h"

inline float	ft_v3dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline float	ft_v3ang(t_vec3 a, t_vec3 b)
{
	return (acosf(ft_v3dot(a, b) / (ft_v3len(a) * ft_v3len(b))));
}

inline float	ft_v3len(t_vec3 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

inline t_vec3		ft_v3nor(t_vec3 v)
{
	float len;

	if ((len = ft_v3len(v)) > 0)
		return (ft_v3(v.x / len, v.y / len, v.z / len));
	return (ft_v3(0, 0, 0));
}
