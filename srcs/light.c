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

double		ft_get_len(t_vec3 vec)
{
	t_vec3	tmp;
	double	res;

	tmp = vec;
	res = sqrt(ft_vector_scale(tmp, tmp));
	return (res);
}

inline int			ft_shadow(t_env *env)
{
	int		h;
	double	t;
	double	len;

	t = 0;
	env->current = -1;
	env->light.shd.pos = env->light.hit;
	env->light.shd.dir = ft_vector_sub(env->light.pos, env->light.shd.pos);
	len = ft_get_len(env->light.shd.dir);
	env->light.shd.dir = ft_vector_normalize(env->light.shd.dir);
	while (++env->current < env->nbobj)
	{
		h = 0;
		if (env->obj[env->current].type == 1 && env->current != env->last)
			h = ft_hit_sphere(env->obj[env->current], env->light.shd, &t);
		else if (env->obj[env->current].type == 2 && env->current != env->last)
			h = ft_hit_cylinder(env->obj[env->current], env->light.shd, &t);
		else if (env->obj[env->current].type == 3 && env->current != env->last)
			h = ft_hit_cone(env->obj[env->current], env->light.shd, &t);
		if (h && t > 0 && t < len)
			return (0);
	}
	return (1);
}

inline double			ft_lambert(t_env *env)
{
	t_vec3		dir;
	double		res;

	env->light.hit = ft_vector_add(env->ray.pos,
		ft_vector_dot(env->ray.dir, env->tmin));
	dir = ft_vector_sub(env->light.hit, env->light.pos);
	dir = ft_vector_normalize(dir);
	env->light.nrm = ft_vector_normalize(ft_vector_sub(env->light.hit,
		env->obj[env->last].center));
	env->light.nrm = ft_neg_vector(env->light.nrm);
	if (env->obj[env->last].rot.ex)
		env->light.nrm = ft_rotate(env->light.nrm, env->obj[env->last].rot);
	else if (env->obj[env->last].type == 4)
		env->light.nrm = ft_vector_new(0, 0, SIGN(env->ray.dir.z));
	res = ft_vector_scale(dir, env->light.nrm);
	if (res < 0.2)
		res = 0.2;
	if (env->shd)
	{
		if (!ft_shadow(env))
			res = 0.15;
	}
	if (res > 1)
		res = 1;
	return (res);
}
