/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1/parse.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:52:16 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/13 15:38:53 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_PARSE_H
# define RTV1_PARSE_H

# include "env.h"

extern int	parsev3(t_vec3 *v3, char **it, char delim);
extern int	shapeparse(t_env *env, int fd, t_rtcb *cb);
extern int	parsecam(t_cam *cam, char **it);
extern int	lightparse(t_env *e);
extern int	atoio(char **it);

#endif
