/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 13:16:31 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/13 14:14:03 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline void		ft_camera_cnstr(t_camera *self, t_vec3 cam_pos, t_vec3 view_drt,
		double screen_dst)
{
	self->cam_pos = cam_pos;
	self->view_drt = view_drt;
	self->screen_dst = screen_dst;
	self->screen_center = ft_vec3_add(cam_pos, ft_vec3_times(view_drt, screen_dst));
	self->p0 = ft_vec3_add(self->screen_center, ft_vec3(-1 , 1, 0));
	self->p1 = ft_vec3_add(self->screen_center, ft_vec3(1 , 1, 0));
	self->p2 = ft_vec3_add(self->screen_center, ft_vec3(-1 , -1, 0));
}
