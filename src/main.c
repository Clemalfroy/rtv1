/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 15:13:46 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/17 16:36:52 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	rtv1(t_env *e)
{
	e->mlx.mlx = mlx_init();
	e->mlx.win = mlx_new_window(e->mlx.mlx, WTH + 250, HGT, "RTv1");
	e->img.img = mlx_new_image(e->mlx.mlx, WTH, HGT);
	e->img.addr = mlx_get_data_addr(e->img.img, &e->img.bpp,
		&e->img.size_l, &e->img.endian);
	e->hud = 1;
	e->antialias = 1;
	mlx_hud(e);
	draw(e);
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->img.img, 0, 0);
	mlx_hook(e->mlx.win, KEYRELEASE, KEYRELEASEMASK, e_keyrelease, e);
	mlx_hook(e->mlx.win, DESTROYNOTIFY, 0, e_destroy, e);
	mlx_loop(e->mlx.mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_env	*env;

	if (argc != 2)
		return (ft_retf(EXIT_FAILURE, "rtv1: %e\n", EINVAL));
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (ft_retf(EXIT_FAILURE, "%s: %e\n", argv[1], errno));
	ft_memset(env = alloca(sizeof(t_env)), 0, sizeof(t_env));
	return (shapeparse(env, fd, rtv1));
}