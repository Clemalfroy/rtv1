/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:39:10 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/17 13:35:33 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

#include "../libft/includes/libft.h"
#include "mlx.h"
#include "utility.h"
#include <math.h>
#include <limits.h>
#include <float.h>

# define ABS(x) ((x) < 0 ? -(x) : (x))
# define WTH 1450
# define HGT 1450
# define MAX(x, y) ((x) < (y) ? (y) : (x))

typedef struct	s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
}				t_mlx;

typedef struct	s_img
{
	void		*img;
	char 		*i_img;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_env
{
	t_mlx		mlx;
	t_img		img;
}				t_env;

extern int		ft_keyrelease(int key, t_env *env);
extern int		ft_destroy(t_env *env);


#endif
