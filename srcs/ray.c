/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 18:15:27 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/12 18:51:05 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline t_ray		ft_ray_cnstr(t_vec3 origin, t_vec3 direction, double tmax)
{
	t_ray		ray;

	ray.origin = origin;
	ray.direction = direction;
	ray.tmax = tmax;
	return (ray);
}
