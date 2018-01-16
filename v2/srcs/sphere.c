/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:10:52 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/13 17:26:33 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline void		ft_sphere_cnstr(t_sphere *self, t_vec3 center, double radius)
{
	self->center = center;
	self->radius = radius;
}
