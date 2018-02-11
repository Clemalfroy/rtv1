/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1/intersect.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:52:16 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/13 15:38:53 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_INTERSECT_H
# define RTV1_INTERSECT_H

# include <libft.h>

# include "utility.h"

struct s_env;
struct s_obj;

extern int		rt_intersect(struct s_env *e, t_v3 r, t_v3 p);
extern double	rt_intercyl(struct s_env *e, struct s_obj *a, t_v3 r, t_v3 p);
extern double	rt_intercone(struct s_env *e, struct s_obj *a, t_v3 r, t_v3 p);
extern double	rt_interspher(struct s_env *e, struct s_obj *a, t_v3 r, t_v3 p);
extern double	rt_interplane(struct s_env *e, struct s_obj *a, t_v3 r, t_v3 p);

#endif
