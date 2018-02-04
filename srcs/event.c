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

inline int		e_loophook(t_env *env)
{
	if (env->redraw)
	{
		mlx_put_image_to_window(env->mlx.mlx, env->mlx.win, env->img.img, 0, 0);
		env->redraw = 0;
	}
	return (0);
}

inline int		e_expose(t_env *env)
{
	env->redraw = 1;
	return (0);
}

inline int		e_keyrelease(int key, t_env *env)
{
	if (key == KEY_ESC)
		mlx_exit(env, 0);
	return (1);
}

inline int		e_destroy(t_env *env)
{
	mlx_exit(env, 0);
	return (0);
}
