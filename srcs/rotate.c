/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:33:55 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/13 15:41:17 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline t_ray			ft_rotate_ray(t_ray ray, t_mat mat)
{
	t_ray		res;

	res.dir = ft_rotate(ray.dir, mat);
	res.pos = ft_rotate(ray.pos, mat);
	return (res);
}

inline t_vec3			ft_rotate(t_vec3 vec, t_mat mat)
{
	t_vec3		res;

	res.x = mat.r1.x * vec.x + mat.r1.y * vec.y + mat.r1.z * vec.z;
	res.y = mat.r2.x * vec.x + mat.r2.y * vec.y + mat.r2.z * vec.z;
	res.z = mat.r3.x * vec.x + mat.r3.y * vec.y + mat.r3.z * vec.z;
	return (res);
}

inline t_vec3			ft_rotate_cam(t_vec3 vec, t_mat mat)
{
	t_vec3		res;

	res.x = mat.r1.x + vec.x * mat.r1.y + vec.y * mat.r1.z;
	res.y = mat.r2.x + vec.x * mat.r2.y + vec.y * mat.r2.z;
	res.z = mat.r3.x + vec.x * mat.r3.y + vec.y * mat.r3.z;
	return (res);
}

inline void			ft_translate(t_vec3 *vec, t_vec3 trs)
{
	*vec = ft_vector_add(*vec, trs);
}