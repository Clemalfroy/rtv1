/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 18:15:27 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/13 13:42:14 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline void		ft_ray_cnstr(t_ray *ray, t_vec3 origin, t_vec3 direction, double length)
{
	ray->origin = origin;
	ray->direction = direction;
	ray->length = length;
}
