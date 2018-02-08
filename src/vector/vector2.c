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

inline t_vec3	normvec(t_env *env, t_obj *nb, t_vec3 pos)
{
	t_vec3	norm;
	t_vec3	temp;
	t_vec3	temp2;

	if (nb->type == 1 || nb->type == 2)
	{
		temp = vec3_scale(&nb->rot,
			(vec3_dot(&env->raydir, &nb->rot) * env->t0
				+ vec3_dot(&env->dist, &nb->rot)));
		if (nb->type == 1)
			temp = vec3_scale(&temp, (1 + pow(tan(nb->size), 2)));
		temp2 = vec3_sub(&pos, &nb->pos);
		norm = vec3_sub(&temp2, &temp);
	}
	else if (nb->type == 3)
		norm = nb->rot;
	if (nb->type == 4)
		norm = vec3_sub(&pos, &nb->pos);
	vec3_norm(&norm);
	return (norm);
}