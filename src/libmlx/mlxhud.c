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

inline void mlx_hud(t_env *e)
{
	int y;
	char ref[20];

	if (e->hud == 1 && !(y = 0))
	{
		if ((y += 40) && e->antialias == 1)
			MSP(e->mlx.mlx, e->mlx.win, HUDX, HGT - y, WHITE, AA "off");
		else
			MSP(e->mlx.mlx, e->mlx.win, HUDX, HGT - y, WHITE, AA "on");
		if ((y += 20) &&  e->spec == 1)
			MSP(e->mlx.mlx, e->mlx.win, HUDX, HGT - y, WHITE, SPC "on");
		else
			MSP(e->mlx.mlx, e->mlx.win, HUDX, HGT - y, WHITE, SPC "off");
		y += 20;
		ft_strcat(ref,"reflections : ");
		ft_strcat(ref, ft_itoa(e->maxref, 10));
		MSP(e->mlx.mlx, e->mlx.win, HUDX, HGT - y, WHITE, ref);
		y += 20;
		MSP(e->mlx.mlx, e->mlx.win, HUDX, HGT - y, WHITE, DELIM);
	}
}