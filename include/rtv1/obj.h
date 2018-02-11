/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1/obj.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:52:16 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/13 15:38:53 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_OBJ_H
# define RTV1_OBJ_H

# include "env.h"

# define POSX env->cam.pos.x
# define POSY env->cam.pos.y
# define POSZ env->cam.pos.z

enum				e_shape
{
	SHAPE_NONE = 0,
	SHAPE_CONE,
	SHAPE_CYLINDER,
	SHAPE_PLANE,
	SHAPE_SPHERE,
	SHAPE_LIGHT
};

typedef struct		s_cam
{
	t_v3			pos;
	t_v3			dir;
}					t_cam;

typedef struct		s_obj
{
	int				type;
	float			size;
	t_v3			rot;
	t_v3			pos;
	t_v3			color;
}					t_obj;

#endif
