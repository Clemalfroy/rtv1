/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:33:55 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/13 15:41:17 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline t_vec3			ft_vector_normalize(t_vec3 vec)
{
	t_vec3		res;
	double		len;

	len = sqrt(ft_vector_scale(vec, vec));
	len = 1 / len;
	res.x *= len;
	res.y *= len;
	res.z *= len;
	return (res);
}

inline t_vec3			ft_neg_vector(t_vec3 vec)
{
	t_vec3		res;

	res.x = -vec.x;
	res.y = -vec.y;
	res.z = -vec.z;
	return (res);
}

inline t_vec3			ft_vector_div_norm(t_vec3 vec, double k)
{
	t_vec3		res;

	res.x = vec.x / k;
	res.y = vec.y / k;
	res.z = vec.z / k;
	return (res);
}