/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1/intersect.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:52:16 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/13 15:38:53 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_INTERSECT_H
# define RTV1_INTERSECT_H

# include <libft.h>

# include "utility.h"

struct s_env;
struct t_obj;

extern int		intersect(struct s_env *env, t_vec3 ray, t_vec3 pos);
extern double	intercylinder(struct s_env *env, struct s_obj *obj, t_vec3 ray,
	t_vec3 pos);
extern double	intercone(struct s_env *env, struct s_obj *obj, t_vec3 ray,
	t_vec3 pos);
extern double	intersphere(struct s_env *env, struct s_obj *obj, t_vec3 ray,
	t_vec3 pos);
extern double	interplane(struct s_env *env, struct s_obj *obj, t_vec3 ray,
	t_vec3 pos);

#endif
