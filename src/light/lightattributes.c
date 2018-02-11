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

inline float	rt_clamp(float value, float min, float max)
{
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return (value);
}

inline void		rt_reflect(t_env *env, t_obj *tmp, t_v3 *pos, float *tab)
{
	t_obj	*tmp2;
	t_v3	dist;
	double	d;
	int		curlight;

	if (env->cpt >= env->maxref || !env->nblight)
		return ;
	if ((tmp2 = rt_refinit(env, tmp, pos)) == NULL || (env->cpt++) < 0)
		return ;
	curlight = -1;
	while (++curlight != env->nblight)
	{
		LAMBERT = 0.14;
		dist = ft_v3sub(env->light[curlight].pos, *pos);
		d = rt_clamp((float)(1.0 / sqrtf(sqrtf(ft_v3dot(dist, dist)))), 0, 1);
		dist = ft_v3nor(dist);
		if (rt_shadow(env, tmp2, &env->light[curlight], *pos) == 0)
			LAMBERT += rt_clamp(ft_v3dot(dist, env->norm), 0.0, 1.0);
		rt_endlight(tmp2, &env->light[curlight], tab, (float)d);
		tab[0] += (COND1) ? rt_specular(env, dist, (float)d, tab[3]) : 0.0;
		tab[1] += (COND1) ? rt_specular(env, dist, (float)d, tab[3]) : 0.0;
		tab[2] += (COND1) ? rt_specular(env, dist, (float)d, tab[3]) : 0.0;
	}
	!PREF1 ? rt_reflect(env, tmp2, pos, tab) : 0;
}

inline float	rt_specular(t_env *mlx, t_v3 dist, float d, float lambert)
{
	float	spec;
	float	tmp;
	t_v3	ref;

	spec = 0.0;
	ref = ft_v3scale(mlx->norm, (float)(2.0 * ft_v3dot(mlx->norm, dist)));
	ref = ft_v3sub(dist, ref);
	if ((tmp = ft_v3dot(ref, mlx->raydir)) > 0.0 && lambert > 0.15)
	{
		spec = (float)(pow(tmp, 20.0) * 4 * d);
		spec = rt_clamp(spec, 0.0, 1.0);
	}
	return (spec);
}

inline void		rt_endlight(t_obj *tmp, t_obj *light, float *tab, float d)
{
	LAMBERT = rt_clamp((float)(LAMBERT * 4.0 * d), 0.0, 1.0);
	tab[0] += LAMBERT * (tmp->color.x / 255) * (light->color.x / 255);
	tab[1] += LAMBERT * (tmp->color.y / 255) * (light->color.y / 255);
	tab[2] += LAMBERT * (tmp->color.z / 255) * (light->color.z / 255);
}
