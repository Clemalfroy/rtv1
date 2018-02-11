/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1/light.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:52:16 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/13 15:38:53 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_LIGHT_H
# define RTV1_LIGHT_H

# include <libft.h>

# include "rtv1.h"

# define PREF1 (env->pref == 1 && tmp2->type != 3)
# define PREF2 (env->pref == 1 && env->obj[nb].type != 3)
# define COND1 (env->spec == 1 && tmp2->type != 3)
# define COND2 (env->spec == 1 && env->obj[nb].type != 3)
# define LAMBERT tab[3]

extern float	rt_specular(t_env *mlx, t_v3 dist, float d, float lambert);
extern void		rt_endlight(t_obj *tmp, t_obj *light, float *tab, float d);
extern void		rt_lambertlight(t_env *env, int nb, float *tab);
extern void		rt_reflect(t_env *env, t_obj *tmp, t_v3 *pos, float *tab);
extern t_obj	*rt_refinit(t_env *env, t_obj *tmp, t_v3 *pos);
extern int		rt_shadow(t_env *env, t_obj *tmp, t_obj *light, t_v3 pos);
extern float	rt_clamp(float value, float min, float max);

#endif
