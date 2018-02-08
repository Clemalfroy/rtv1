/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 10:41:04 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/math/v3.h"

inline t_vec3		ft_v3(float x, float y, float z)
{
	return ((t_vec3){.x = x, .y = y, .z = z});
}

inline t_vec3		ft_v3add(t_vec3 a, t_vec3 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

inline t_vec3		ft_v3sub(t_vec3 a, t_vec3 b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return (a);
}

inline t_vec3		ft_v3mul(t_vec3 a, t_vec3 b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return (a);
}

inline t_vec3		ft_v3div(t_vec3 a, t_vec3 b)
{
	a.x /= b.x;
	a.y /= b.y;
	a.z /= b.z;
	return (a);
}
