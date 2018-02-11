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
#define NB env->nblight

inline int			rt_atoio(char **it)
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

static inline int	parserad(float *pos, char **it, char delim)
{
	char d;
	char *s;

	if (!ft_isdigit(d = *++*it) || !(d -= '0') || *++*it != ':' || !(*++*it))
		return (ft_retf(STDERR_FILENO, UNX, **it));
	s = *it;
	*pos = rt_atoio(it);
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
		if (**it == '{' && rt_parsev3(&shape->pos, it, '}'))
			return (NOP);
		else if (**it == '<' && rt_parsev3(&shape->rot, it, '>'))
			return (NOP);
		else if (**it == '[' && rt_parsev3(&shape->color, it, ']'))
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
			return (ft_retf(STDERR_FILENO, "rtv1: Expected EOL\n"));
		else
			break ;
	if (*n == 0)
		return (ft_retf(STDERR_FILENO, "rtv1: empty scene\n"));
	return (YEP);
}

inline int			rt_parseobj(t_env *env, int fd, t_rtcb *cb)
{
	size_t	n;
	ssize_t	r;
	int		i;
	char	*buf;

	if (parsen(fd, &n))
		return (NOP);
	if ((r = read(fd,
		buf = alloca(n + 1), n)) != (ssize_t)n)
		return (ft_retf(STDERR_FILENO, "rtv1: invalid map size\n"));
	buf[r] = '\0';
	while (*buf == '\n')
		++buf;
	if ((i = -1) && (*buf != 'c' || rt_parsecam(&env->cam, &buf)))
		return (NOP);
	if (!ft_isdigit(*buf) || (env->nbobj = rt_atoio(&buf)) < 0 || *buf != '`')
		return (ft_retf(STDERR_FILENO, UNX, *buf));
	(void)((env->obj = alloca(env->nbobj * sizeof(t_obj))) && ++buf);
	while (++i < env->nbobj)
		if (parseshape(env->obj + i, &buf) ||
			(env->nblight += env->obj[i].type == 5 ? 1 : 0) < 0)
			return (NOP);
	if (NB && (env->light = alloca(NB * sizeof(t_obj))) && rt_parselgt(env))
		return (ft_retf(STDERR_FILENO, "Invalid light informations\n"));
	return (cb(env));
}
