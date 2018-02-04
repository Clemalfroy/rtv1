/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:33:55 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/13 15:41:17 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline t_shape		*shape(t_env *env)
{
	t_shape	*shape;

	env->nbshape = 1; //a supprimer later quand on aura le bon nombre
	if (!(shape = (t_shape *)malloc(sizeof(t_shape))) * env->nbshape)
		exit(-1);
	return (shape);
}