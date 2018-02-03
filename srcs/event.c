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

inline int		ft_loop_hook(t_env *env)
{
	if (env->redraw)
	{
		mlx_put_image_to_window(env->mlx.mlx, env->mlx.win, env->img.img, 0, 0);
		env->redraw = 0;
	}
	return (0);
}

inline int		ft_expose(t_env *env)
{
	env->redraw = 1;
	return (0);
}

inline int		ft_keyrelease(int key, t_env *env)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_window(env->mlx.mlx, env->mlx.win);
		exit(0);
	}
	return (1);
}

inline int		ft_destroy(t_env *env)
{
	mlx_destroy_window(env->mlx.mlx, env->mlx.win);
	exit(0);
	return (1);
}
