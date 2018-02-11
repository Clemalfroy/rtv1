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

#include "rtv1/vector.h"

inline t_vec3	normvec(t_env *env, t_obj *nb, t_vec3 pos)
{
	t_vec3	norm;
	t_vec3	temp;
	t_vec3	temp2;

	if (nb->type == SHAPE_CONE || nb->type == SHAPE_CYLINDER)
	{
		temp = ft_v3scale(nb->rot,
			(ft_v3dot(env->raydir, nb->rot) * env->t0
			 + ft_v3dot(env->dist, nb->rot)));
		if (nb->type == SHAPE_CONE)
			temp = ft_v3scale(temp, (1 + pow(tan(nb->size), 2)));
		temp2 = ft_v3sub(pos, nb->pos);
		norm = ft_v3sub(temp2, temp);
	}
	else if (nb->type == SHAPE_PLANE)
		norm = nb->rot;
	if (nb->type == SHAPE_SPHERE)
		norm = ft_v3sub(pos, nb->pos);
	norm = ft_v3nor(norm);
	return (norm);
}
