/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:19:35 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/16 16:41:36 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

inline void mlx_hud(t_env *e)
{
	int y;

	if (e->hud == 1 && (y = 10))
	{
		if (e->antialias == 1)
			MSP(e->mlx.mlx, e->mlx.win, WTH, y, WHITE, "anti-aliasing: off");
		else
			MSP(e->mlx.mlx, e->mlx.win, WTH, y, WHITE, "anti-aliasing: on");
		if ((y += 20) &&  e->spec == 1)
			MSP(e->mlx.mlx, e->mlx.win, WTH, y, WHITE, "specularity: on");
		else
			MSP(e->mlx.mlx, e->mlx.win, WTH, y, WHITE, "specularity: off");
	}
}