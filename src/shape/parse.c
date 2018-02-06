/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape/parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:33:55 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/13 15:41:17 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#define UNX "rtv1: %c: Unexpected character\n"

static inline int	atoio(char **it)
{
	int i;
	int m;

	i = 0;
	if (**it != '-')
		m = 1;
	else
	{
		++*it;
		m = -1;
	}
	while (ft_isdigit(**it) && i >= 0)
		i = i * 10 + *(*it)++ - '0';
	return (m * i);
}

static inline int	parsev3(t_vec3 *v3, char **it, char delim)
{
	char d;
	char *s;

	if (!ft_isdigit(d = *++*it) || !(d -= '0') || *++*it != ':' || !(*++*it))
		return (ft_retf(STDERR_FILENO, UNX, **it));
	s = *it;
	v3->x = atoio(it);
	if (*it - s != d || **it != ';')
		return (ft_retf(STDERR_FILENO, UNX, **it));
	if (!ft_isdigit(d = *++*it) || !(d -= '0') || *++*it != ':' || !(*++*it))
		return (ft_retf(STDERR_FILENO, UNX, **it));
	s = *it;
	v3->y = atoio(it);
	if (*it - s != d || **it != ';')
		return (ft_retf(STDERR_FILENO, UNX, **it));
	if (!ft_isdigit(d = *++*it) || !(d -= '0') || *++*it != ':' || !(*++*it))
		return (ft_retf(STDERR_FILENO, UNX, **it));
	s = *it;
	v3->z = atoio(it);
	if (*it - s != d || **it != delim)
		return (ft_retf(STDERR_FILENO, UNX, **it));
	++*it;
	return (YEP);
}

static inline int	parserad(double *pos, char **it, char delim)
{
	char d;
	char *s;

	if (!ft_isdigit(d = *++*it) || !(d -= '0') || *++*it != ':' || !(*++*it))
		return (ft_retf(STDERR_FILENO, UNX, **it));
	s = *it;
	*pos = atoio(it);
	if (*it - s != d || **it != delim)
		return (ft_retf(STDERR_FILENO, UNX, **it));
	++*it;
	return (YEP);
}

static inline int	parselight(t_light *light, char **it)
{
	++*it;
	while (**it)
		if (**it == '{' && parsev3(&light->pos, it, '}'))
			return (NOP);
		else
			break ;
	while (**it == '\n')
		++*it;
	return (YEP);
}

static inline int	parsecam(t_cam *cam, char **it)
{
	++*it;
	while (**it)
		if (**it == '{' && parsev3(&cam->pos, it, '}'))
			return (NOP);
		else if (**it == '<' && parsev3(&cam->pos, it, '>'))
			return (NOP);
		else
			break ;
	while (**it == '\n')
		++*it;
	cam->pos.x *= PI / 180;
	cam->pos.y *= PI / 180;
	cam->pos.z *= PI / 180;
	if ((cam->rot.y = ((cam->rot.x || cam->rot.y) ? 1 : 0)))
		cam->mat = matrix_cam(cam->rot);
	return (YEP);
}

static inline void	setrotation(t_vec3 *rot, t_shape *shape)
{
	double	t;

	shape->rot.ex = 0;
	t = rot->x * PI / 180;
	if (t)
		shape->rot = matrix_x(t);
	t = rot->y * PI / 180;
	if (shape->rot.ex && t)
		shape->rot = matrix_mult(shape->rot, matrix_y(t));
	else if (t)
		shape->rot = matrix_y(t);
	t = rot->z * PI / 180;
	if (shape->rot.ex && t)
		shape->rot = matrix_mult(shape->rot, matrix_z(t));
	else if (t)
		shape->rot = matrix_z(t);
	if (shape->rot.ex)
		shape->inv = matrix_inv(shape->rot);
}

static inline int	parseshape(t_shape *shape, char **it)
{
	t_vec3 rot;
	t_vec3 trs;

	while (**it == '\n')
		++*it;
	if (**it < 'a' || **it > 'd')
		return (ft_retf(STDERR_FILENO, "rtv1: %c: Unknown shape type\n", **it));
	ft_memset(shape, 0, sizeof(t_shape));
	shape->type = (uint8_t)(*(*it)++ - '`');
	while (**it)
		if (**it == '{' && parsev3(&shape->center, it, '}'))
			return (NOP);
		else if (**it == '<' && parsev3(&rot, it, '>'))
			return (NOP);
		else if (**it == '[' && parsev3(&shape->color, it, ']'))
			return (NOP);
		else if (**it == '"' && parsev3(&trs, it, '"'))
			return (NOP);
		else if (**it == '\'' && parserad(&shape->radius, it, '\''))
			return (NOP);
		else if (**it == '|' && parsev3(&shape->norm, it, '|'))
			return (NOP);
		else if (!ft_strchr("{[<\"'|", **it))
			break ;
	translate(&shape->center, trs);
	setrotation(&rot, shape);
	while (**it == '\n' || **it == ';')
		++*it;
	return (YEP);
}

static inline int	parsen(int fd, size_t *n)
{
	char	c;
	ssize_t	r;

	*n = 0;
	while ((r = read(fd, &c, 1)))
		if (r < 0)
			return (ft_retf(STDERR_FILENO, "rtv1: %e\n", errno));
		else if (ft_isdigit(c))
			*n = *n * 10 + c - '0';
		else if (c != '\n')
			return (ft_retf(STDERR_FILENO, "rtv1: Expected EOL, got '%c'\n", c));
		else
			break ;
	return (YEP);
}

inline int	shapeparse(t_env *env, int fd, t_rtcb *cb)
{
	size_t	n;
	ssize_t	r;
	int		i;
	char	*buf;

	if (parsen(fd, &n))
		return (NOP);
	if ((r = read(fd, buf = alloca(n + 1), n)) != (ssize_t)n)
		return (ft_retf(STDERR_FILENO, "rtv1: invalid map size\n"));
	buf[r] = '\0';
	while (*buf == '\n')
		++buf;
	if (*buf != 'l' || parselight(&env->light, &buf) || *buf != 'c' ||
		parsecam(&env->cam, &buf))
		return (NOP);
	if (!ft_isdigit(*buf) || (env->nbshape = atoio(&buf)) < 0 || *buf != '`')
		return (ft_retf(STDERR_FILENO, UNX, *buf));
	env->shapes = alloca(env->nbshape * sizeof(t_shape));
	i = -1;
	++buf;
	while (++i < env->nbshape)
		if (parseshape(env->shapes + i, &buf))
			return (NOP);
	return (cb(env));
}