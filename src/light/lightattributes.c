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

inline float	ft_clamp(float value, float min, float max)
{
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return (value);
}

inline void		reflect(t_env *env, t_obj *tmp, t_vec3 *pos, float *tab)
{
	t_obj	*tmp2;
	t_obj	*light;
	t_vec3	dist;
	double	d;

	if (env->cpt >= env->maxref || (light = env->light) == NULL)
		return ;
	if ((tmp2 = ft_ref_init(env, tmp, pos)) == NULL || (env->cpt++) < 0)
		return ;
	env->curlight = -1;
	while (++env->curlight != env->nblight)
	{
		LAMBERT = 0.14;
		dist = vec3_sub(&light->pos, pos);
		d = ft_clamp(1.0 / sqrtf(sqrtf(vec3_dot(&dist, &dist))), 0.0, 1.0);
		vec3_norm(&dist);
		if (ft_shadow(env, tmp2, light, *pos) == 0)
			LAMBERT += ft_clamp(vec3_dot(&dist, &env->norm), 0.0, 1.0);
		endlight(tmp2, light, tab, (float)d);
		tab[0] += (COND1) ? specular(env, dist, (float)d, tab[3]) : 0.0;
		tab[1] += (COND1) ? specular(env, dist, (float)d, tab[3]) : 0.0;
		tab[2] += (COND1) ? specular(env, dist, (float)d, tab[3]) : 0.0;
	}
	!PREF1 ? reflect(env, tmp2, pos, tab) : 0;
}

inline float	specular(t_env *mlx, t_vec3 dist, float d, float lambert)
{
	float	spec;
	float	tmp;
	t_vec3	ref;

	spec = 0.0;
	ref = vec3_scale(&mlx->norm, (2.0 * vec3_dot(&mlx->norm, &dist)));
	ref = vec3_sub(&dist, &ref);
	if ((tmp = vec3_dot(&ref, &mlx->raydir)) > 0.0 && lambert > 0.15)
	{
		spec = pow(tmp, 20.0) * 4 * d;
		spec = ft_clamp(spec, 0.0, 1.0);
	}
	return (spec);
}

inline void		endlight(t_obj *tmp, t_obj *light, float *tab, float d)
{
	LAMBERT = ft_clamp((float)(LAMBERT * 4.0 * d), 0.0, 1.0);
	tab[0] += LAMBERT * (tmp->color.x / 255) * (light->color.x / 255);
	tab[1] += LAMBERT * (tmp->color.y / 255) * (light->color.y / 255);
	tab[2] += LAMBERT * (tmp->color.z / 255) * (light->color.z / 255);
}