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

#define POSY env->cam.pos.y
#define POSX env->cam.pos.x
#define POSZ env->cam.pos.z

#define I env->i
#define J env->j
#define K env->k

#define DIR env->cam.dir

static int		ft_pref_key(int keycode, t_env *env)
{
	(keycode == KEY_R && env->maxref < 15) ? env->maxref++ : env->maxref;
	(keycode == KEY_F && env->maxref > 0) ? env->maxref-- : env->maxref;
	if (keycode == KEY_E)
		env->pref = (env->pref == 0) ? 1 : 0;
	if (keycode == KEY_X)
	{
		if (env->antialias == 1 || env->antialias == 2 || env->antialias == 4 ||
			env->antialias == 8)
			env->antialias *= 2;
	}
	if (keycode == KEY_C)
	{
		if (env->antialias == 2 || env->antialias == 4 || env->antialias == 8 ||
			env->antialias == 16)
			env->antialias /= 2;
	}
	return (0);
}

static int		ft_translation_add(int keycode, t_env *env)
{
	if (keycode == KEY_S)
	{
		DIR = (t_vec3){DIR.x - 3 * J.x, DIR.y - 3 * J.y, DIR.z - 3 * J.z};
		env->cam.pos = (t_vec3){env->cam.pos.x - 3 * J.x,
			env->cam.pos.y - 3 * J.y, env->cam.pos.z - 3 * J.z};
	}
	else if (keycode == KEY_W)
	{
		DIR = (t_vec3){DIR.x + 3 * J.x, DIR.y + 3 * J.y, DIR.z + 3 * J.z};
		env->cam.pos = (t_vec3){env->cam.pos.x + 3 * J.x,
			env->cam.pos.y + 3 * J.y, env->cam.pos.z - 3 * J.z};
	}
	else if (keycode == KEY_PLUS)
	{
		DIR = (t_vec3){DIR.x + 3 * K.x, DIR.y + 3 * K.y, DIR.z + 3 * K.z};
		env->cam.pos = (t_vec3){POSX + 3 * K.x, POSY + 3 * K.y, POSZ + 3 * K.z};
	}
	if (keycode == KEY_MINUS)
	{
		DIR = (t_vec3){DIR.x - 3 * K.x, DIR.y - 3 * K.y, DIR.z - 3 * K.z};
		env->cam.pos = (t_vec3){env->cam.pos.x - 3 * K.x,
			env->cam.pos.y - 3 * K.y, env->cam.pos.z - 3 * K.z};
	}
	ft_pref_key(keycode, env);
	return (draw(env));
}

static int		translation(int keycode, t_env *env)
{
	K = vec3_sub(&DIR, &env->cam.pos);
	vec3_norm(&K);
	I = vec3_cross(&K, &(t_vec3){0.0, 1.0, 0.0});
	vec3_norm(&I);
	J = vec3_cross(&I, &K);
	if (keycode == KEY_A)
	{
		DIR = (t_vec3){DIR.x + 3 * I.x,
			DIR.y + 3 * I.y, DIR.z + 3 * I.z};
		env->cam.pos = (t_vec3){env->cam.pos.x + 3 * I.x,
			env->cam.pos.y + 3 * I.y, env->cam.pos.z + 3 * I.z};
	}
	else if (keycode == KEY_D)
	{
		DIR = (t_vec3){DIR.x - 3 * I.x,
			DIR.y - 3 * I.y, DIR.z - 3 * I.z};
		env->cam.pos = (t_vec3){env->cam.pos.x - 3 * I.x,
			env->cam.pos.y - 3 * I.y, env->cam.pos.z - 3 * I.z};
	}
	else if (keycode == KEY_G)
		env->spec = (env->spec == 0) ? 1 : 0;
	else if (keycode == KEY_TAB)
		env->hud = (env->hud == 0) ? 1 : 0;
	return (ft_translation_add(keycode, env));
}

inline int		e_keyhook(int keycode, t_env *env)
{
	float	tmppos;

	if (keycode == KEY_LEFT && (tmppos = POSX) < 20000)
	{
		POSX = POSX * cosf(0.03) + POSZ * sinf(0.03);
		POSZ = tmppos * (-sinf(0.03)) + POSZ * cosf(0.03);
	}
	else if (keycode == KEY_RIGHT && (tmppos = POSX) > -20000)
	{
		POSX = POSX * cosf(-0.03) + POSZ * sinf(-0.03);
		POSZ = tmppos * (-sinf(-0.03)) + POSZ * cosf(-0.03);
	}
	else if (keycode == KEY_DOWN && (tmppos = POSY) > -20000)
	{
		POSY = POSY * cosf(-0.03) + POSZ * (-sinf(-0.03));
		POSZ = tmppos * sinf(-0.03) + POSZ * cosf(-0.03);
	}
	else if (keycode == KEY_UP && (tmppos = POSY) < 20000)
	{
		POSY = POSY * cosf(0.03) + POSZ * (-sinf(0.03));
		POSZ = tmppos * sinf(0.03) + POSZ * cosf(0.03);
	}
	return (translation(keycode, env));
}
