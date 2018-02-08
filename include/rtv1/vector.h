/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1/utility.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:52:16 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/13 15:38:53 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_VECTOR_H
# define RTV1_VECTOR_H

t_vec3			vec3_scale(t_vec3 *v, float n);
t_vec3			vec3_sub(t_vec3 *v1, t_vec3 *v2);
t_vec3			vec3_cross(t_vec3 *v1, t_vec3 *v2);
void			vec3_norm(t_vec3 *v);
float			vec3_dot(t_vec3 *v1, t_vec3 *v2);
extern t_vec3	normvec(t_env *env, t_obj *nb, t_vec3 pos);

#endif
