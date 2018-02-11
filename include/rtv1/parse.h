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

extern int	rt_parsev3(t_v3 *v3, char **it, char delim);
extern int	rt_parseobj(t_env *env, int fd, t_rtcb *cb);
extern int	rt_parsecam(t_cam *cam, char **it);
extern int	rt_parselgt(t_env *e);
extern int	rt_atoio(char **it);

#endif
