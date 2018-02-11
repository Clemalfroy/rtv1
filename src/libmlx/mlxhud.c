/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:19:35 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/16 16:41:36 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#define DELIM "-----------------------------"
#define AA "anti-aliasing: "
#define SPC "specularity: "
#define RFLT "reflexion: "

inline void	rt_mlxhud(t_env *e)
{
	int y;

	y = 0;
	if (e->hud == 1)
	{
		if ((y += 40) && e->antialias == 1)
			MSP(e->mlx.mlx, e->mlx.win, HUDX, HGT - y, WHITE, AA "off");
		else
			MSP(e->mlx.mlx, e->mlx.win, HUDX, HGT - y, WHITE, AA "on");
		if ((y += 20) && e->spec == 1)
			MSP(e->mlx.mlx, e->mlx.win, HUDX, HGT - y, WHITE, SPC "on");
		else
			MSP(e->mlx.mlx, e->mlx.win, HUDX, HGT - y, WHITE, SPC "off");
		if ((y += 20) && e->maxref)
			MSP(e->mlx.mlx, e->mlx.win, HUDX, HGT - y, WHITE, RFLT "on");
		else
			MSP(e->mlx.mlx, e->mlx.win, HUDX, HGT - y, WHITE, RFLT "off");
		y += 20;
		MSP(e->mlx.mlx, e->mlx.win, HUDX, HGT - y, WHITE, DELIM);
	}
}
