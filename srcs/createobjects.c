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

inline t_obj		*ft_create_tabobjects(t_env *env)
{
	t_obj	*obj;

	env->nbobj = 1; //a supprimer later quand on aura le bon nombre
	if (!(obj = (t_obj *)malloc(sizeof(t_obj))) * env->nbobj)
		exit(-1);
	return (obj);
}