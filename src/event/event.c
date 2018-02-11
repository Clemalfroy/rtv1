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

#include "rtv1.h"

inline int		rt_onkeyrelease(int key, t_env *env)
{
	if (key == KEY_ESC)
		rt_mlxexit(env, 0);
	return (1);
}

inline int		rt_ondestroy(t_env *env)
{
	rt_mlxexit(env, 0);
	return (0);
}
