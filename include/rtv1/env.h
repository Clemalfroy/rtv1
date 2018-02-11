/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1/env.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:52:16 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/13 15:38:53 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_ENV_H
# define RTV1_ENV_H

# include <errno.h>
# include <pthread.h>

# include "libmlx.h"
# include "obj.h"

# define FOV 2.0
# define THREADS 32

typedef	struct	s_env
{
	t_mlx		mlx;
	t_img		img;

	t_obj		*obj;
	t_obj		*light;
	t_cam		cam;

	t_v3		raydir;
	t_v3		norm;
	t_v3		refpos;
	t_v3		ref;

	t_v3		i;
	t_v3		j;
	t_v3		k;

	t_v3		dist;

	int			nbobj;
	int			nblight;

	int			hud;
	int			pref;

	int			antialias;
	int			spec;
	int			maxref;

	int			tx;
	int			ty;

	float		t;
	float		t0;
	float		t1;

	float		a;
	float		b;
	float		c;

	int			cpt;
}				t_env;

typedef struct	s_thread
{
	int			i;
	t_env		env;
}				t_thread;

typedef int		(t_rtcb)(t_env *env);

#endif
