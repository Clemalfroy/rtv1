/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:19:35 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/16 16:41:36 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

inline int		ft_shadow(t_env *env, t_obj *tmp, t_obj *light, t_vec3 pos)
{
	t_obj	*node;
	t_vec3	dist;

	node = env->obj;
	env->curobj = -1;
	dist = vec3_sub(&light->pos, &pos);
	env->t = sqrtf(vec3_dot(&dist, &dist));
	vec3_norm(&dist);
	while (++env->curobj != env->nbobj)
	{
		if (node != tmp)
		{
			if (node->type == 1)
				env->a = intercone(env, node, dist, pos);
			else if (node->type == 2)
				env->a = intercylinder(env, node, dist, pos);
			else if (node->type == 3)
				env->a = interplane(env, node, dist, pos);
			else if (node->type == 4)
				env->a = intersphere(env, node, dist, pos);
			else if (node->type == 5)
				continue;
			if (env->a > 0.0001 && env->a < env->t)
				return (1);
		}
	}
	return (0);
}

static t_obj	*ft_ref_inter(t_env *env, t_obj *node, t_obj *tmp, t_vec3 pos)
{
	t_obj	*tmp2;
	double	dist;

	env->curobj = -1;
	tmp2 = NULL;
	while (++env->curobj != env->nbobj)
		if (node != tmp)
		{
			if (node->type == 1)
				dist = intercone(env, node, env->ref, pos);
			else if (node->type == 2)
				dist = intercylinder(env, node, env->ref, pos);
			else if (node->type == 3)
				dist = interplane(env, node, env->ref, pos);
			else if (node->type == 4)
				dist = intersphere(env, node, env->ref, pos);
			else if (node->type == 5)
				continue;
			if (dist > 0.0001 && dist < env->t)
			{
				tmp2 = node;
				env->t = dist;
			}
		}
	return (tmp2);
}

inline t_obj	*ft_ref_init(t_env *env, t_obj *tmp, t_vec3 *pos)
{
	t_obj	*tmp2;

	env->t = 8000.0;
	env->ref = vec3_scale(&env->norm,
		(2 * vec3_dot(&env->refpos, &env->norm)));
	env->ref = vec3_sub(&env->refpos, &env->ref);
	vec3_norm(&env->ref);
	tmp2 = ft_ref_inter(env, env->obj, tmp, *pos);
	if (!tmp2)
		return (NULL);
	*pos = (t_vec3){pos->x + env->t * env->ref.x, pos->y +
		env->t * env->ref.y, pos->z + env->t * env->ref.z};
	env->refpos = (t_vec3){env->ref.x, env->ref.y, env->ref.z};
	env->norm = normvec(env, tmp2, *pos);
	return (tmp2);
}

inline void		lambertlight(t_env *env, int nb, t_obj *light, float *tab)
{
	t_vec3	pos;
	t_vec3	dist;
	float	d;

	env->curlight = -1;
	pos = (t_vec3){env->cam.pos.x + env->t * env->raydir.x, env->cam.pos.y +
		env->t * env->raydir.y, env->cam.pos.z + env->t * env->raydir.z};
	env->norm = normvec(env, &env->obj[nb], pos);
	while (++env->curlight != env->nblight)
	{
		LAMBERT = 0.15;
		dist = vec3_sub(&light->pos, &pos);
		d = ft_clamp((1.0 / sqrtf(sqrtf(vec3_dot(&dist, &dist)))), 0.F, 1.F);
		vec3_norm(&dist);
		if (ft_shadow(env, &env->obj[nb], light, pos) == 0)
			LAMBERT += ft_clamp(vec3_dot(&dist, &env->norm), 0.0, 1.0);
		endlight(&env->obj[nb], light, tab, d);
		tab[0] += (COND2) ? specular(env, dist, d, tab[3]) : 0.0;
		tab[1] += (COND2) ? specular(env, dist, d, tab[3]) : 0.0;
		tab[2] += (COND2) ? specular(env, dist, d, tab[3]) : 0.0;
	}
	env->refpos = (t_vec3){env->raydir.x, env->raydir.y, env->raydir.z};
	!PREF2 ? reflect(env, &env->obj[nb], &pos, tab) : 0;
}