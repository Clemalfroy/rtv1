/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 15:13:46 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/17 16:36:52 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			ft_lambert(t_env *env)
{
	t_vec3		dir;
	double		res;

	env->lgt.hit = ft_vector_add(env->ray.pos,
		ft_vector_dot(env->ray.dir, env->tmin));
	dir = ft_vector_sub(env->lgt.hit, env->lgt.pos);
	dir = ft_vector_normalize(dir);
	env->lgt.nrm = ft_vector_normalize(ft_vector_sub(env->lgt.hit,
		env->obj[env->last].center));
	env->lgt.nrm = ft_neg_vector(env->lgt.nrm);
	if (env->obj[env->last].rot.ex)
		env->lgt.nrm = ft_rotate(env->lgt.nrm, env->obj[env->last].rot);
	else if (env->obj[env->last].type == 4)
		env->lgt.nrm = ft_vector_new(0, 0, SIGN(env->ray.dir.z));
	res = ft_vector_scale(dir, env->lgt.nrm);
	if (res < 0.2)
		res = 0.2;
	if (env->shd)
	{
		//if (!ft_shadow(env))
			//res = 0.15;
	}
	if (res > 1)
		res = 1;
	return (res);
}
