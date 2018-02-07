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

#include "rtv1.h"

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

static inline int	parserad(float *pos, char **it, char delim)
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

static inline int	parseshape(t_obj *shape, char **it)
{
	while (**it == '\n')
		++*it;
	if (**it < 'a' || **it > 'e')
		return (ft_retf(STDERR_FILENO, "rtv1: %c: Unknown shape type\n", **it));
	ft_memset(shape, 0, sizeof(t_obj));
	shape->type = (uint8_t)(*(*it)++ - '`');
	while (**it)
		if (**it == '{' && parsev3(&shape->pos, it, '}'))
			return (NOP);
		else if (**it == '<' && parsev3(&shape->rot, it, '>'))
			return (NOP);
		else if (**it == '[' && parsev3(&shape->color, it, ']'))
			return (NOP);
		else if (**it == '\'' && parserad(&shape->size, it, '\''))
			return (NOP);
		else if (!ft_strchr("{[<'", **it))
			break ;
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

static inline int	parsecam(t_cam *cam, char **it)
{
	++*it;
	while (**it)
		if (**it == '{' && parsev3(&cam->pos, it, '}'))
			return (NOP);
		else if (**it == '<' && parsev3(&cam->dir, it, '>'))
			return (NOP);
		else
			break ;
	while (**it == '\n')
		++*it;
	return (YEP);
}

inline static int lightparse(t_env *e)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < e->nbobj)
		if(e->obj[i].type == 5)
			e->light[++j] = e->obj[i];
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
	if ((i = -1) && (*buf != 'c' || parsecam(&env->cam, &buf)))
		return (NOP);
	if (!ft_isdigit(*buf) || (env->nbobj = atoio(&buf)) < 0 || *buf != '`')
		return (ft_retf(STDERR_FILENO, UNX, *buf));
	env->obj = alloca(env->nbobj * sizeof(t_obj));
	++buf;
	while (++i < env->nbobj)
		if (parseshape(env->obj + i, &buf) ||
			(env->nblight += env->obj[i].type == 5 ? 1 : 0) < 0)
			return (NOP);
	if (env->nblight && (env->light = alloca(env->nblight * sizeof(t_obj))) &&
		lightparse(env))
		return (ft_retf(STDERR_FILENO, "Invalid light informations\n"));
	return (cb(env));
}