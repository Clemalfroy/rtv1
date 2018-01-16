/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:39:10 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/13 13:14:08 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

#include "mlx.h"
#include <math.h>

# define WTH 1250
# define HGT 725
# define RAY_T_MAX 1.0e30f
# define RAY_T_MIN 0.0001f

typedef struct	s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef struct	s_ray
{
	t_vec3		origin;
	t_vec3		direction;
	double		tmax;
}				t_ray;

typedef struct s_sphere
{
	t_vec3		center;
	double		radius;
}				t_sphere;

typedef struct	s_plane
{
	t_vec3		point;
	t_vec3		normal;
}				t_plane;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
}				t_env;

extern t_vec3	ft_vec3(float x, float y, float z);
extern t_vec3	ft_vec3_add(t_vec3 a, t_vec3 b);
extern t_vec3	ft_vec3_sub(t_vec3 a, t_vec3 b);
extern t_vec3	ft_vec3_mul(t_vec3 a, t_vec3 b);
extern t_vec3	ft_vec3_div(t_vec3 a, t_vec3 b);
extern float	ft_vec3_dot(t_vec3 a, t_vec3 b);
extern float	ft_vec3_ang(t_vec3 a, t_vec3 b);
extern float	ft_vec3_len(t_vec3 a);
extern t_vec3	ft_vec3_nor(t_vec3 a);

extern t_ray	ft_ray_cnstr(t_vec3 o, t_vec3 d, double max);


#endif
