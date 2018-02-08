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

inline int	parsev3(t_vec3 *v3, char **it, char delim)
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

inline int	parsecam(t_cam *cam, char **it)
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

inline int	lightparse(t_env *e)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < e->nbobj)
		if (e->obj[i].type == 5)
			e->light[++j] = e->obj[i];
	return (YEP);
}
