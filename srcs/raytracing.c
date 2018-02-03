/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:33:55 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/13 15:41:17 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline static void	ft_init_ray(t_env *env, int x, int y)
{
	t_vec3	v;

	env->ray.pos = env->cam.pos;
	v.x = (x + 0.5) / WTH;
	v.y = (y + 0.5) / HGT;
	v.x = (2 * v.x) - 1;
	v.y = 1 - (2 * v.y);
	v.x *= (WTH / (double)HGT) * tan((env->fov / 2) * PI / 180);
	v.y *= tan((env->fov / 2) * PI / 180);
	v.z = 1;
	if (env->cam.mat.ex)
		env->ray.dir = ft_rotate_cam(v, env->cam.mat);
	else
		env->ray.dir = v;
}

inline void			ft_raytracing(t_env *env)
{
	int		y;
	int		x;

	y = -1;
	while (++y < HGT && (x = -1))
		while (++x < WTH)
		{
			env->tmin = 1 / EPSILON;
			ft_init_ray(env, x, y);
		}
}