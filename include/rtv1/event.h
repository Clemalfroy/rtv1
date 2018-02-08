/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1/event.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:52:16 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/13 15:38:53 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_EVENT_H
# define RTV1_EVENT_H

# include <libft.h>

# include "utility.h"

struct s_env;

extern int	e_keyrelease(int key, struct s_env *env);
extern int	e_destroy(struct s_env *env);
extern int	e_keyhook(int keycode, t_env *env);

#endif
