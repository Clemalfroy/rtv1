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

static int		ft_pref_key(int keycode, t_env *env)
{
	(keycode == 15 && env->maxref < 15) ? env->maxref++ : env->maxref;
	(keycode == 3 && env->maxref > 0) ? env->maxref-- : env->maxref;
	if (keycode == 14)
		env->pref = (env->pref == 0) ? 1 : 0;
	if (keycode == 7)
	{
		if (env->antialias == 1 || env->antialias == 2 || env->antialias == 4 ||
			env->antialias == 8)
			env->antialias *= 2;
	}
	if (keycode == 6)
	{
		if (env->antialias == 2 || env->antialias == 4 || env->antialias == 8 ||
			env->antialias == 16)
			env->antialias /= 2;
	}
	return (0);
}

static int	ft_translation_add(int keycode, t_env *env)
{
	if (keycode == KEY_S)
	{
		env->cam.dir = (t_vec3){env->cam.dir.x - 10.0 * J.x,
			env->cam.dir.y - 10.0 * J.y, env->cam.dir.z - 10.0 * J.z};
		env->cam.pos = (t_vec3){env->cam.pos.x - 10.0 * J.x,
			env->cam.pos.y - 10.0 * J.y, env->cam.pos.z - 10.0 * J.z};
	}
	else if (keycode == KEY_W)
	{
		env->cam.dir = (t_vec3){env->cam.dir.x + 10.0 * J.x,
			env->cam.dir.y + 10.0 * J.y, env->cam.dir.z + 10.0 * J.z};
		env->cam.pos = (t_vec3){env->cam.pos.x + 10.0 * J.x,
			env->cam.pos.y + 10.0 * J.y, env->cam.pos.z - 10.0 * J.z};
	}
	else if (keycode == KEY_PLUS)
	{
		env->cam.dir = (t_vec3){env->cam.dir.x + 10.0 * K.x,
			env->cam.dir.y + 10.0 * K.y, env->cam.dir.z + 10.0 * K.z};
		env->cam.pos = (t_vec3){env->cam.pos.x + 10.0 * K.x,
			env->cam.pos.y + 10.0 * K.y, env->cam.pos.z + 10.0 * K.z};
	}
	if (keycode == KEY_MINUS)
	{
		env->cam.dir = (t_vec3){env->cam.dir.x - 10.0 * K.x,
			env->cam.dir.y - 10.0 * K.y, env->cam.dir.z - 10.0 * K.z};
		env->cam.pos = (t_vec3){env->cam.pos.x - 10.0 * K.x,
			env->cam.pos.y - 10.0 * K.y, env->cam.pos.z - 10.0 * K.z};
	}
	ft_pref_key(keycode, env);
	return (draw(env));
}

static int	translation(int keycode, t_env *env)
{
	K = vec3_sub(&env->cam.dir, &env->cam.pos);
	vec3_norm(&K);
	I = vec3_cross(&K, &(t_vec3){0.0, 1.0, 0.0});
	vec3_norm(&I);
	J = vec3_cross(&I, &K);
	if (keycode == KEY_A)
	{
		env->cam.dir = (t_vec3){env->cam.dir.x + 10.0 * I.x,
			env->cam.dir.y + 10.0 * I.y, env->cam.dir.z + 10.0 * I.z};
		env->cam.pos = (t_vec3){env->cam.pos.x + 10.0 * I.x,
			env->cam.pos.y + 10.0 * I.y, env->cam.pos.z + 10.0 * I.z};
	}
	else if (keycode == KEY_D)
	{
		env->cam.dir = (t_vec3){env->cam.dir.x - 10.0 * I.x,
			env->cam.dir.y - 10.0 * I.y, env->cam.dir.z - 10.0 * I.z};
		env->cam.pos = (t_vec3){env->cam.pos.x - 10.0 * I.x,
			env->cam.pos.y - 10.0 * I.y, env->cam.pos.z - 10.0 * I.z};
	}
	else if (keycode == KEY_G)
		env->spec = (env->spec == 0) ? 1 : 0;
	else if (keycode == KEY_TAB)
		env->hud = (env->hud == 0) ? 1 : 0;
	return (ft_translation_add(keycode, env));
}

inline int	e_keyhook(int keycode, t_env *env)
{
	float	tmppos;

	if (keycode == KEY_LEFT && (tmppos = POSX) < 20000)
	{
		POSX = POSX * cosf(0.05) + POSZ * sinf(0.05);
		POSZ = tmppos * (-sinf(0.05)) + POSZ * cosf(0.05);
	}
	else if (keycode == KEY_RIGHT && (tmppos = POSZ) > -20000)
	{
		POSX = POSX * cosf(-0.05) + POSZ * sinf(-0.05);
		POSZ = tmppos * (-sinf(-0.05)) + POSZ * cosf(-0.05);
	}
	else if (keycode == KEY_DOWN && (tmppos = POSY) > -20000)
	{
		POSY = POSY * cosf(-0.05) + POSZ * (-sinf(-0.05));
		POSZ = tmppos * sinf(-0.05) + POSZ * cosf(-0.05);
	}
	else if (keycode == KEY_UP && (tmppos = POSY) < 20000)
	{
		POSY = POSY * cosf(0.05) + POSZ * (-sinf(0.05));
		POSZ = tmppos * sinf(0.05) + POSZ * cosf(0.05);
	}
	return (translation(keycode, env));
}