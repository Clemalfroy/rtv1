/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 17:24:34 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/13 17:27:06 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline void		ft_plane_cnstr(t_plane *plane, t_vec3 pos, t_vec3 norm)
{
	plane->position = pos;
	plane->normal = norm;
}
