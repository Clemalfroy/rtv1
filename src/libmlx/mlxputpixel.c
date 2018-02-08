/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putpixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 15:13:46 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/17 16:36:52 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

inline void		putpixel(t_env *env, int x, int y, int color)
{
	int				i;
	unsigned int	p;

	i = 0;
	p = x * (env->img.bpp / 8) + y * (env->img.size_l);
	while (i < (env->img.bpp / 8))
	{
		env->img.addr[p + i] = color;
		color >>= 8;
		i++;
	}
}
