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

inline int			rt_shadow(t_env *env, t_obj *tmp, t_obj *light,
	t_v3 pos)
{
	t_obj	*obj;
	t_v3	dist;
	int		curobj;

	curobj = -1;
	dist = ft_v3sub(light->pos, pos);
	env->t = sqrtf(ft_v3dot(dist, dist));
	dist = ft_v3nor(dist);
	while (++curobj != env->nbobj)
		if ((obj = env->obj + curobj) != tmp)
		{
			if (obj->type == 1)
				env->a = (float)rt_intercone(env, obj, dist, pos);
			else if (obj->type == 2)
				env->a = (float)rt_intercyl(env, obj, dist, pos);
			else if (obj->type == 3)
				env->a = (float)rt_interplane(env, obj, dist, pos);
			else if (obj->type == 4)
				env->a = (float)rt_interspher(env, obj, dist, pos);
			else if (obj->type == 5)
				continue;
			if (env->a > 0.0001 && env->a < env->t)
				return (1);
		}
	return (0);
}

static t_obj		*rt_refinter(t_env *env, t_obj *tmp, t_v3 pos)
{
	t_obj	*obj;
	t_obj	*tmp2;
	double	dist;
	int		curobj;

	curobj = -1;
	tmp2 = NULL;
	dist = 0;
	while (++curobj != env->nbobj)
		if ((obj = env->obj + curobj) != tmp)
		{
			if (obj->type == 1)
				dist = rt_intercone(env, obj, env->ref, pos);
			else if (obj->type == 2)
				dist = rt_intercyl(env, obj, env->ref, pos);
			else if (obj->type == 3)
				dist = rt_interplane(env, obj, env->ref, pos);
			else if (obj->type == 4)
				dist = rt_interspher(env, obj, env->ref, pos);
			else if (obj->type == 5)
				continue;
			if (dist > 0.0001 && dist < env->t && (env->t = (float)dist))
				tmp2 = obj;
		}
	return (tmp2);
}

inline t_obj		*rt_refinit(t_env *env, t_obj *tmp, t_v3 *pos)
{
	t_obj	*tmp2;

	env->t = 8000.0;
	env->ref = ft_v3scale(env->norm, (2 * ft_v3dot(env->refpos, env->norm)));
	env->ref = ft_v3sub(env->refpos, env->ref);
	env->ref = ft_v3nor(env->ref);
	tmp2 = rt_refinter(env, tmp, *pos);
	if (!tmp2)
		return (NULL);
	*pos = (t_v3){pos->x + env->t * env->ref.x, pos->y +
		env->t * env->ref.y, pos->z + env->t * env->ref.z};
	env->refpos = (t_v3){env->ref.x, env->ref.y, env->ref.z};
	env->norm = normvec(env, tmp2, *pos);
	return (tmp2);
}

inline void			rt_lambertlight(t_env *env, int nb, float *tab)
{
	t_v3	pos;
	t_v3	dist;
	float	d;
	int		curlight;

	curlight = -1;
	pos = (t_v3){env->cam.pos.x + env->t * env->raydir.x, env->cam.pos.y +
		env->t * env->raydir.y, env->cam.pos.z + env->t * env->raydir.z};
	env->norm = normvec(env, &env->obj[nb], pos);
	while (++curlight != env->nblight)
	{
		LAMBERT = 0.15;
		dist = ft_v3sub(env->light[curlight].pos, pos);
		d = rt_clamp((float)(1.0 / sqrtf(sqrtf(ft_v3dot(dist, dist)))), 0, 1);
		dist = ft_v3nor(dist);
		if (rt_shadow(env, &env->obj[nb], &env->light[curlight], pos) == 0)
			LAMBERT += rt_clamp(ft_v3dot(dist, env->norm), 0.0, 1.0);
		rt_endlight(&env->obj[nb], &env->light[curlight], tab, d);
		tab[0] += (COND2) ? rt_specular(env, dist, d, tab[3]) : 0.0;
		tab[1] += (COND2) ? rt_specular(env, dist, d, tab[3]) : 0.0;
		tab[2] += (COND2) ? rt_specular(env, dist, d, tab[3]) : 0.0;
	}
	env->refpos = (t_v3){env->raydir.x, env->raydir.y, env->raydir.z};
	!PREF2 ? rt_reflect(env, &env->obj[nb], &pos, tab) : 0;
}
