/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:39:10 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/14 10:34:36 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

#include "../libft/includes/libft.h"
#include "mlx.h"
#include "utility.h"
#include <math.h>

# define ABS(x) ((x) < 0 ? -(x) : (x))
# define WTH 1250
# define HGT 1200

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
	double		length;
}				t_ray;

typedef struct	s_camera
{
	t_vec3		cam_pos;
	t_vec3		view_drt;
	float		screen_dst;

	t_vec3		screen_center;
	t_vec3		p0;
	t_vec3		p1;
	t_vec3		p2;
}				t_camera;

typedef struct	s_plane
{
	t_vec3		position;
	t_vec3		normal;
}				t_plane;

typedef struct	s_triangle
{
	t_vec3		a;
	t_vec3		b;
	t_vec3		c;
}				t_triangle;

typedef struct s_sphere
{
	t_vec3		center;
	double		radius;
}				t_sphere;

typedef struct	s_env
{
	void		*mlx;
	void		*win;

	t_camera	camera;
}				t_env;

extern t_vec3	ft_vec3(float x, float y, float z);
extern t_vec3	ft_vec3_add(t_vec3 a, t_vec3 b);
extern t_vec3	ft_vec3_cross(t_vec3 a, t_vec3 b);
extern t_vec3	ft_vec3_sub(t_vec3 a, t_vec3 b);
extern t_vec3	ft_vec3_mul(t_vec3 a, t_vec3 b);
extern t_vec3	ft_vec3_div(t_vec3 a, t_vec3 b);
extern t_vec3	ft_vec3_times(t_vec3 a, double nb);
extern t_vec3	ft_vec3_divnb(t_vec3 a, double nb);
extern float	ft_vec3_dot(t_vec3 a, t_vec3 b);
extern float	ft_vec3_ang(t_vec3 a, t_vec3 b);
extern float	ft_vec3_len(t_vec3 a);
extern t_vec3	ft_vec3_nor(t_vec3 a);

extern void		ft_ray_cnstr(t_ray *self, t_vec3 o, t_vec3 d, double max);
extern void		ft_camera_cnstr(t_camera *self, t_vec3 cam_pos, t_vec3 view_drt, double screen_dst);

extern void		ft_sphere_cnstr(t_sphere *sphere, t_vec3 c, double radius);
extern void		ft_plane_cnstr(t_plane *plane, t_vec3 pos, t_vec3 norm);
extern void		ft_triangle_cnstr(t_triangle *t, t_vec3 a, t_vec3 b, t_vec3 c);

int				ray_sphere_intersect(t_sphere *sphere, t_ray *ray);
int				ray_plane_intersect(t_plane *plane, t_ray *ray);
int				ray_triangle_intersect(t_triangle *triangle, t_ray *ray);

int				ft_keyrelease(int key, t_env *env);
int				ft_destroy(t_env *env);

#endif
