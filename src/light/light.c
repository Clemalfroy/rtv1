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

inline double		vec3_getdst(t_vec3 vec)
{
	t_vec3	tmp;
	double	res;

	tmp = vec;
	res = sqrt(vec3_scale(tmp, tmp));
	return (res);
}

inline static int	shadow(t_env *env)
{
	int		h;
	double	t;
	double	len;

	t = 0;
	env->current = -1;
	env->light.shd.pos = env->light.hit;
	env->light.shd.dir = vec3_sub(env->light.pos, env->light.shd.pos);
	len = vec3_getdst(env->light.shd.dir);
	env->light.shd.dir = vec3_normalize(env->light.shd.dir);
	while (++env->current < env->nbshape)
	{
		h = 0;
		if (env->shapes[env->current].type == 1 && env->current != env->last)
			h = rt_hitsphere(env->shapes[env->current], env->light.shd, &t);
		else if (env->shapes[env->current].type == 2 && env->current != env->last)
			h = rt_hitcylinder(env->shapes[env->current], env->light.shd, &t);
		else if (env->shapes[env->current].type == 3 && env->current != env->last)
			h = rt_hitcone(env->shapes[env->current], env->light.shd, &t);
		if (h && t > 0 && t < len)
			return (0);
	}
	return (1);
}

inline double			lb_light(t_env *env)
{
	t_vec3		dir;
	double		res;

	env->light.hit = vec3_add(env->ray.pos,
		vec3_dot(env->ray.dir, env->tmin));
	dir = vec3_sub(env->light.hit, env->light.pos);
	dir = vec3_normalize(dir);
	env->light.nrm = vec3_normalize(vec3_sub(env->light.hit,
		env->shapes[env->last].center));
	env->light.nrm = vec3_neg(env->light.nrm);
	if (env->shapes[env->last].rot.ex)
		env->light.nrm = rotate(env->light.nrm, env->shapes[env->last].rot);
	else if (env->shapes[env->last].type == 4)
		env->light.nrm = vec3_new(0, 0, SIGN(env->ray.dir.z));
	res = vec3_scale(dir, env->light.nrm);
	if (res < 0.2)
		res = 0.2;
	if (env->shd)
	{
		if (!shadow(env))
			res = 0.15;
	}
	if (res > 1)
		res = 1;
	return (res);
}
